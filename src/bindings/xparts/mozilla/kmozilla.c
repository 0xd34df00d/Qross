#include "kmozilla.h"
#include "kmozilla_ext.h"
#include <gtkmozembed.h>
#include <gtkbrowserextension.h>
#include <assert.h>

typedef struct _GtkKmozillaPrivate GtkKmozillaPrivate;

struct _GtkKmozillaPrivate {
    GtkMozEmbed *mozilla;
    GtkKmozillaExtension *ext;
};

#define P ((GtkKmozillaPrivate *)(((GtkKmozilla *)part)->data))
#define CLASS(obj) GTK_KMOZILLA_CLASS(GTK_OBJECT(obj)->klass)


/* class and instance initialization */

static void
gtk_kmozilla_class_init(GtkKmozillaClass *klass);

static void
gtk_kmozilla_init(GtkKmozilla *part);

static void 
gtk_kmozilla_destroy( GtkObject *obj );

static GtkXPartClass *parent_class = 0;
static gboolean openUrlRequested = FALSE;
static GtkKmozilla *mozilla = 0;

/* virtual functions */
static gboolean open_url( GtkXPart *part, const char * url );
static gboolean close_url ( GtkXPart *part );
static char * query_extension ( GtkXPart *part, const char *name );


/* signals */
static void handle_reload(GtkObject *obj, gpointer user_data);

/* signal handlers for gtkmozembed signals */
static gboolean open_url_request(GtkObject *obj, const char *url);

/* --------------------------- implementations --------------------------------------- */

/* type information */
GtkType
gtk_kmozilla_get_type(void)
{
  static GtkType part_type = 0;
  if (!part_type)
  {
    static const GtkTypeInfo part_info =
    {
      "GtkKmozilla",
      sizeof(GtkKmozilla),
      sizeof(GtkKmozillaClass),
      (GtkClassInitFunc)gtk_kmozilla_class_init,
      (GtkObjectInitFunc)gtk_kmozilla_init,
      0,
      0,
      0
    };
    part_type = gtk_type_unique(GTK_TYPE_XPART, &part_info);
  }
  return part_type;
}

/* class and instance initialization */
static void
gtk_kmozilla_class_init(GtkKmozillaClass *klass)
{
    GtkObjectClass     *object_class = (GtkObjectClass *)klass;
    GtkXPartClass *xpart_class = GTK_XPART_CLASS(klass);
    
    parent_class = (GtkXPartClass *)gtk_type_class(gtk_xpart_get_type());

    object_class->destroy = gtk_kmozilla_destroy;

    xpart_class->open_url = open_url;
    xpart_class->close_url = close_url;
    xpart_class->query_extension = query_extension;

    g_message( "gtk_kmozilla_class_init\n" );
}

static void
gtk_kmozilla_init(GtkKmozilla *part)
{
    GtkWidget *w;
    GtkWidget *moz;
    GtkKmozillaExtension *ext;

    GtkKmozillaPrivate *d;
    d = g_new( GtkKmozillaPrivate, 1 );
    part->data = d;

    ext = gtk_kmozilla_extension_new();
    g_message( "gtk_kmozilla_init\n" );
    kmozilla_extension_set_mozilla( ext, part );
    d->ext = ext;

    dcop_object_set_id( DCOP_OBJECT(part), "KmozillaClient" );

    w = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    moz = gtk_moz_embed_new();
    d->mozilla = GTK_MOZ_EMBED( moz );
    gtk_container_add( GTK_CONTAINER( w ), moz );
    gtk_widget_realize( w );

    /*    g_warning( "winid %x\n", GDK_WINDOW_XWINDOW( w->window ) );*/

    gtk_xpart_set_widget( (GtkXPart *)part, w );

    gtk_signal_connect(GTK_OBJECT(part), "reload",
		     GTK_SIGNAL_FUNC(handle_reload), NULL);
    gtk_signal_connect(GTK_OBJECT(moz), "open_uri",
		     GTK_SIGNAL_FUNC(open_url_request), NULL);
    
    mozilla = part;
    g_message( "gtk_kmozilla_init\n" );
}

GtkKmozilla *gtk_kmozilla_new (void)
{
    return (GtkKmozilla *) gtk_type_new(gtk_kmozilla_get_type());
}

void gtk_kmozilla_destroy( GtkObject *obj )
{
    GtkKmozilla *part = GTK_KMOZILLA(obj);
    GtkKmozillaPrivate *d = (GtkKmozillaPrivate *) part->data;
    
    gtk_object_destroy( GTK_OBJECT( d->mozilla ) );
    
    GTK_OBJECT_CLASS(parent_class)->destroy(obj);
}

void gtk_kmozilla_set_dcop_client( GtkKmozilla *part, DcopClient *client )
{
    gtk_xpart_set_dcop_client(part, client);
    gtk_xbrowserextension_set_dcop_client(P->ext, client);
}

/* ----------------------------------------------------------------------- */

static gboolean open_url( GtkXPart *part, const char * url )
{
    g_message( "open_url %s", url );
    openUrlRequested = FALSE;
    gtk_moz_embed_load_url( P->mozilla, url );
    return TRUE;
}

static gboolean close_url( GtkXPart *part )
{
    g_message( "close_url" );
    gtk_moz_embed_stop_load( P->mozilla );
    return TRUE;
}

static char * query_extension ( GtkXPart *part, const char *name )
{
    g_warning("KMozilla::query_extension");
    if( !strcmp(name, "browserextension") )
	return dcop_object_get_id((DcopObject *)P->ext);
    return NULL;
}

static void
handle_reload(GtkObject *obj, gpointer user_data)
{
    GtkKmozilla *part = GTK_KMOZILLA(obj);
    g_message( "reload called" );
    gtk_moz_embed_reload(P->mozilla, 0);
}

/* ----------------- signal handlers for gtkmozembed ------------------ */

/* return true if we don't want mozilla to load it, false if mozilla should load the page. */
static gboolean open_url_request(GtkObject *obj, const char * url)
{
    gboolean req;
    g_message("==================>>>>>>> kmozilla::openUrlRequest %s", url);
    req = openUrlRequested;
    if( req == TRUE ) {
	gtk_browserextension_open_url_request( ((GtkKmozillaPrivate *)mozilla->data)->ext, url );
    }
    openUrlRequested = TRUE;
    return req;
}

