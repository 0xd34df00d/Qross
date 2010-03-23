
#include "gtkbrowserextension.h"

#include <gdk/gdkx.h>

#include <dcopc/util.h>
#include <dcopc/marshal.h>
#include <dcopc/dcopc.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _GtkXBrowserExtensionPrivate GtkXBrowserExtensionPrivate;

struct _GtkXBrowserExtensionPrivate {
    gchar *host_app_id;
    gchar *host_obj_id;
    DcopClient *client;
};

#define P ((GtkXBrowserExtensionPrivate *)(part->data))
#define CLASS(obj) GTK_XBROWSEREXTENSION_CLASS(GTK_OBJECT(obj)->klass)


/* class and instance initialization */

static void
gtk_xbrowserextension_class_init(GtkXBrowserExtensionClass *klass);

static void
gtk_xbrowserextension_init(GtkXBrowserExtension *part);

static void 
gtk_xbrowserextension_destroy( GtkObject *obj );


/* dcop handlers */

gboolean gtk_xbrowserextension_dcop_process( DcopObject *obj, const char *fun, dcop_data *data,
                      char **reply_type, dcop_data **reply_data );

GList *gtk_xbrowserextension_dcop_functions( DcopObject *obj );

GList *gtk_xbrowserextension_dcop_interfaces( DcopObject *obj );

static DcopObjectClass *parent_class = 0;

/* --------------------------- implementations --------------------------------------- */

/* type information */
GtkType
gtk_xbrowserextension_get_type(void)
{
  static GtkType part_type = 0;
  if (!part_type)
  {
    static const GtkTypeInfo part_info =
    {
      "GtkXBrowserExtension",
      sizeof(GtkXBrowserExtension),
      sizeof(GtkXBrowserExtensionClass),
      (GtkClassInitFunc)gtk_xbrowserextension_class_init,
      (GtkObjectInitFunc)gtk_xbrowserextension_init,
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
gtk_xbrowserextension_class_init(GtkXBrowserExtensionClass *klass)
{
    GtkObjectClass     *object_class = (GtkObjectClass *)klass;
    DcopObjectClass *dcop_class = DCOP_OBJECT_CLASS(klass);
    g_message( "gtk_xbrowserextension_class_init\n" );
    
    parent_class = (DcopObjectClass *)gtk_type_class(dcop_object_get_type());

    object_class->destroy = gtk_xbrowserextension_destroy;

    dcop_class->process = gtk_xbrowserextension_dcop_process;
    dcop_class->functions = gtk_xbrowserextension_dcop_functions;
    dcop_class->interfaces = gtk_xbrowserextension_dcop_interfaces;

    klass->save_state = 0;
    klass->restore_state = 0;
    
    g_message( "gtk_xbrowserextension_class_init\n" );
}

static void
gtk_xbrowserextension_init(GtkXBrowserExtension *part)
{
    GtkXBrowserExtensionPrivate *d;
    d = g_new( GtkXBrowserExtensionPrivate, 1 );
    part->data = d;

    dcop_object_set_id( DCOP_OBJECT(part), "XBrowserExtensionClient" );

    d->client = 0;
    d->host_app_id = 0;
    d->host_obj_id = 0;
    
    g_message( "gtk_xbrowserextension_init\n" );
}

GtkXBrowserExtension *gtk_xbrowserextension_new (void)
{
    return (GtkXBrowserExtension *) gtk_type_new(gtk_xbrowserextension_get_type());
}


gboolean gtk_xbrowserextension_dcop_process( DcopObject *obj, const char *fun, dcop_data *data,
				char **reply_type, dcop_data **reply_data )
{
    GtkXBrowserExtension *part = GTK_XBROWSEREXTENSION(obj);
    GtkXBrowserExtensionPrivate *d = (GtkXBrowserExtensionPrivate *)part->data;
    GtkXBrowserExtensionClass *klass = GTK_XBROWSEREXTENSION_CLASS(GTK_OBJECT(part)->klass);

    if ( strcmp( fun, "saveState()" ) == 0 )
    {
	const char *state = 0;
	if( klass->save_state) {
	    state = klass->save_state( part );
	    
	    dcop_marshal_bytearray( *reply_data, state, strlen( state ) );
	}
	return True;
    }
    else if ( strcmp( fun, "restoreState(QByteArray)" ) == 0 )
    {
	if( klass->restore_state ) {
	    size_t len;
	    char *state;
	    dcop_demarshal_bytearray( data, &state, &len );
	    klass->restore_state( part, state, len );
	}
	return True;
    }
    else if ( strcmp( fun, "setBrowserSignals(DCOPRef)" ) == 0 )
    {
	dcop_demarshal_string( data, &d->host_app_id );
	dcop_demarshal_string( data, &d->host_obj_id );
	return True;
    }

    return parent_class->process( obj, fun, data, reply_type, reply_data );
}

GList *gtk_xbrowserextension_dcop_functions( DcopObject *obj )
{
    GList *res = parent_class->functions( obj );
    res = g_list_append( res, g_strdup( "saveState()" ) );
    res = g_list_append( res, g_strdup( "restoreState(QByteArray)" ) );
    return res;
}

GList *gtk_xbrowserextension_dcop_interfaces( DcopObject *obj )
{
    GList *res = parent_class->interfaces( obj );
    res = g_list_append( res, g_strdup( "XBrowserExtension" ) );
    return res;
}

void gtk_xbrowserextension_destroy( GtkObject *obj )
{
    GtkXBrowserExtension *part = GTK_XBROWSEREXTENSION(obj);
    GtkXBrowserExtensionPrivate *d = (GtkXBrowserExtensionPrivate *) part->data;
    g_free( d->host_app_id );
    g_free( d->host_obj_id );
    g_free( d );
    
    GTK_OBJECT_CLASS(parent_class)->destroy(obj);
}

void gtk_xbrowserextension_set_dcop_client( GtkXBrowserExtension *part, DcopClient *client )
{
    P->client = client;
}


gboolean gtk_xbrowserextension_register( GtkXBrowserExtension *part, const gchar *host_app_id, const gchar *host_obj_id)
{
    dcop_data *reply_data;
    char *reply_type;
    dcop_data *data = dcop_data_ref( dcop_data_new() );
    GtkXBrowserExtensionPrivate *d = (GtkXBrowserExtensionPrivate *)part->data;
    
    if(!P->client)
	fprintf(stderr, "register a dcop client first!\n");
    
    dcop_marshal_string( data, dcop_client_app_id( P->client ) );
    dcop_marshal_string( data, DCOP_ID(DCOP_OBJECT(part)) );
    
    if ( !dcop_client_call( P->client, host_app_id, host_obj_id, "registerXBrowserExtension(DCOPRef)", data,
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
    g_message( "returning from gtk_xbrowserextension_register" );
    return TRUE;
}

gboolean gtk_browserextension_open_url_request( GtkXBrowserExtension *part, const char *url )
{
    dcop_data *reply_data;
    char *reply_type;
    dcop_data *data = dcop_data_ref( dcop_data_new() );
    
    if(!P->client)
	fprintf(stderr, "register a dcop client first!\n");
    
    dcop_marshal_string( data, url );
    
    if ( !dcop_client_call( P->client, P->host_app_id, P->host_obj_id, "openURLRequest(QCString)", data,
			    &reply_type, &reply_data ) ) {
	g_warning(" openURLRequest failed");
	return FALSE;
    }
    return TRUE;
}
