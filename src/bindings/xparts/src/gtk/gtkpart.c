
#include "gtkpart.h"

#include <gdk/gdkx.h>

#include <dcopc/util.h>
#include <dcopc/marshal.h>
#include <dcopc/dcopc.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _GtkXPartPrivate GtkXPartPrivate;

struct _GtkXPartPrivate {
    GtkWidget *widget;
    gchar *host_app_id;
    gchar *host_obj_id;
    DcopClient *client;
};

#define P ((GtkXPartPrivate *)(part->data))
#define CLASS(obj) GTK_XPART_CLASS(GTK_OBJECT(obj)->klass)


/* class and instance initialization */

static void
gtk_xpart_class_init(GtkXPartClass *klass);

static void
gtk_xpart_init(GtkXPart *part);

static void 
gtk_xpart_destroy( GtkObject *obj );

/* dcop handlers */

gboolean gtk_xpart_dcop_process( DcopObject *obj, const char *fun, dcop_data *data,
                      char **reply_type, dcop_data **reply_data );

GList *gtk_xpart_dcop_functions( DcopObject *obj );

GList *gtk_xpart_dcop_interfaces( DcopObject *obj );

static DcopObjectClass *parent_class = 0;

/* --------------------------- implementations --------------------------------------- */

/* type information */
GtkType
gtk_xpart_get_type(void)
{
  static GtkType part_type = 0;
  if (!part_type)
  {
    static const GtkTypeInfo part_info =
    {
      "GtkXPart",
      sizeof(GtkXPart),
      sizeof(GtkXPartClass),
      (GtkClassInitFunc)gtk_xpart_class_init,
      (GtkObjectInitFunc)gtk_xpart_init,
      0,
      0,
      0
    };
    part_type = gtk_type_unique(DCOP_TYPE_OBJECT, &part_info);
  }
  return part_type;
}

/* class and instance initialization */
static void
gtk_xpart_class_init(GtkXPartClass *klass)
{
    GtkObjectClass     *object_class = (GtkObjectClass *)klass;
    DcopObjectClass *dcop_class = DCOP_OBJECT_CLASS(klass);
    
    parent_class = (DcopObjectClass *)gtk_type_class(dcop_object_get_type());

    object_class->destroy = gtk_xpart_destroy;

    dcop_class->process = gtk_xpart_dcop_process;
    dcop_class->functions = gtk_xpart_dcop_functions;
    dcop_class->interfaces = gtk_xpart_dcop_interfaces;
    
    klass->open_url = 0;
    klass->close_url = 0;
    klass->query_extension = 0;

    g_message( "gtk_xpart_class_init\n" );
}

static void
gtk_xpart_init(GtkXPart *part)
{
    GtkXPartPrivate *d;
    d = g_new( GtkXPartPrivate, 1 );
    part->data = d;

    dcop_object_set_id( DCOP_OBJECT(part), "XPartClient" );

    d->widget = 0;
    d->client = 0;
    d->host_app_id = 0;
    d->host_obj_id = 0;
    
    g_message( "gtk_xpart_init\n" );
}

GtkXPart *gtk_xpart_new (void)
{
    return (GtkXPart *) gtk_type_new(gtk_xpart_get_type());
}


void gtk_xpart_set_widget( GtkXPart *part, GtkWidget *widget )
{
    GtkXPartPrivate *d = (GtkXPartPrivate *)part->data;
    d->widget = widget;
    gtk_object_ref( GTK_OBJECT( widget ) );
}



gboolean gtk_xpart_dcop_process( DcopObject *obj, const char *fun, dcop_data *data,
				char **reply_type, dcop_data **reply_data )
{
    GtkXPart *part = GTK_XPART(obj);
    GtkXPartPrivate *d = (GtkXPartPrivate *)part->data;
    GtkXPartClass *klass = GTK_XPART_CLASS(GTK_OBJECT(part)->klass);
    gboolean b;

    if ( strcmp( fun, "windowId()" ) == 0 )
    {
	*reply_type = strdup( "Q_UINT32" );
	*reply_data = dcop_data_ref( dcop_data_new() );

	fprintf( stderr, "returning window id %ld\n", GDK_WINDOW_XWINDOW( d->widget->window ) );
	dcop_marshal_uint32( *reply_data, GDK_WINDOW_XWINDOW( d->widget->window ) );

	return True;
    }
    else if ( strcmp( fun, "show()" ) == 0 )
    {
	fprintf( stderr, "show %p!\n", d->widget );
	gtk_widget_show_all( d->widget );
	return True;
    }
    else if ( strcmp( fun, "openURL(QCString)" ) == 0 )
    {
	char *url;
	fprintf( stderr, "openURL!\n" );
	dcop_demarshal_string( data, &url );
	b = FALSE;
	if ( klass->open_url )
	    b = klass->open_url( part, url );
	*reply_type = strdup( "bool" );
	*reply_data = dcop_data_ref( dcop_data_new() );
	dcop_marshal_boolean( *reply_data, b );
	return True;
    }
    else if ( strcmp( fun, "closeURL()" ) == 0 )
    {
	fprintf( stderr, "closeURL!\n" );
	b = FALSE;
	if ( klass->close_url )
	    b = klass->close_url( part );
	*reply_type = strdup( "bool" );
	*reply_data = dcop_data_ref( dcop_data_new() );
	dcop_marshal_boolean( *reply_data, b );
	return True;
    }
    else if ( strcmp( fun, "activateAction(QCString,int)" ) == 0 )
    {
	char *name;
	uint state;
	dcop_demarshal_string( data, &name );
	dcop_demarshal_uint32( data, &state );
	fprintf( stderr, "activateAction %s state=%d\n", name, state );
	gtk_signal_emit_by_name( GTK_OBJECT(part), name, state);
	return True;
    }
    else if ( strcmp( fun, "queryExtension(QCString)" ) == 0 ) {
	char *name;
	char *extension = NULL;
	dcop_demarshal_string( data, &name );
	if ( klass->query_extension )
	    extension = klass->query_extension( part, name );
	*reply_type = strdup( "DCOPRef" );
	*reply_data = dcop_data_ref( dcop_data_new() );
	dcop_marshal_string( *reply_data, dcop_client_app_id( P->client ) );
	dcop_marshal_string( *reply_data, extension );
	return True;
    }

    return parent_class->process( obj, fun, data, reply_type, reply_data );
}

GList *gtk_xpart_dcop_functions( DcopObject *obj )
{
    GList *res = parent_class->functions( obj );
    res = g_list_append( res, g_strdup( "windowId()" ) );
    res = g_list_append( res, g_strdup( "show()" ) );
    res = g_list_append( res, g_strdup( "bool openURL(QString url)" ) );
    res = g_list_append( res, g_strdup( "bool closeURL()" ) );
    res = g_list_append( res, g_strdup( "queryExtension(QCString)" ) );
    return res;
}

GList *gtk_xpart_dcop_interfaces( DcopObject *obj )
{
    GList *res = parent_class->interfaces( obj );
    res = g_list_append( res, g_strdup( "XPart" ) );
    return res;
}

void gtk_xpart_destroy( GtkObject *obj )
{
    GtkXPart *part = GTK_XPART(obj);
    GtkXPartPrivate *d = (GtkXPartPrivate *) part->data;
    g_free( d->host_app_id );
    g_free( d->host_obj_id );
    
    gtk_object_destroy( GTK_OBJECT( d->widget ) );
    
    GTK_OBJECT_CLASS(parent_class)->destroy(obj);
}

void gtk_xpart_set_dcop_client( GtkXPart *part, DcopClient *client )
{
    P->client = client;
}


gboolean gtk_xpart_register( GtkXPart *part, const gchar *host_app_id, const gchar *host_obj_id)
{
    dcop_data *reply_data;
    char *reply_type;
    dcop_data *data = dcop_data_ref( dcop_data_new() );
    GtkXPartPrivate *d = (GtkXPartPrivate *)part->data;
    
    if(!P->client)
	fprintf(stderr, "register a dcop client first!\n");
    
    dcop_marshal_string( data, dcop_client_app_id( P->client ) );
    dcop_marshal_string( data, DCOP_ID(DCOP_OBJECT(part)) );
    
    if ( !dcop_client_call( P->client, host_app_id, host_obj_id, "registerXPart(DCOPRef)", data,
			    &reply_type, &reply_data ) ) {
	fprintf( stderr, "cannot register with shell %s / %s\n", host_app_id, host_obj_id );
	gtk_exit( 1 );
    }
    g_message( "back from registration call!" );
    
    /*assert( strcmp( reply_type, "DCOPRef" ) == 0 );*/

#if 0
    /* this is wrong. but as we have the ref anyway, let's ignore the return value*/
    dcop_demarshal_string( data, &d->host_app_id );
    dcop_demarshal_string( data, &d->host_obj_id );
    
    printf("appid=%s, objid=%s\n", d->host_app_id, d->host_obj_id);
#endif
    d->host_obj_id = g_strdup( host_obj_id );
    d->host_app_id = g_strdup( host_app_id );
    
    dcop_data_reset( reply_data );
    
    dcop_data_deref( data );
    g_message( "returning from gtk_xpart_register" );
    return TRUE;
}


gboolean gtk_xpart_initialize_actions( GtkXPart *part, const char * actions )
{
    GtkXPartPrivate *d = (GtkXPartPrivate *) part->data;
    dcop_data *data = 0;

    g_message( "gtk_xpart_initialize_actions\n" );
    
    if(!P->client)
	g_message( "register a dcop client first!\n" );

    data = dcop_data_ref( dcop_data_new() );
    dcop_marshal_string( data, actions );

    if( !dcop_client_send( d->client, d->host_app_id, d->host_obj_id, "createActions(QCString)", data ) ) {
	fprintf( stderr, "could not create actions\n" );
	dcop_data_deref( data );
	return FALSE;
    }
    dcop_data_deref( data );
    return TRUE;
}
