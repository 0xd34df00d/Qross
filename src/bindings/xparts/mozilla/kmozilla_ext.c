#include "kmozilla_ext.h"

#include <gdk/gdkx.h>

#include <dcopc/util.h>
#include <dcopc/marshal.h>
#include <dcopc/dcopc.h>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct _GtkKmozillaExtensionPrivate GtkKmozillaExtensionPrivate;

struct _GtkKmozillaExtensionPrivate {
    GtkKmozilla *moz;
};

#define P ((GtkKmozillaExtensionPrivate *)(ext->data))
#define CLASS(obj) GTK_KMOZILLAEXTENSION_CLASS(GTK_OBJECT(obj)->klass)


/* class and instance initialization */

static void
gtk_kmozilla_extension_class_init(GtkKmozillaExtensionClass *klass);

static void
gtk_kmozilla_extension_init(GtkKmozillaExtension *part);

static void 
gtk_kmozilla_extension_destroy( GtkObject *obj );

/* virtual functions */
static const char * save_state( GtkXBrowserExtension *ext );
static void restore_state ( GtkXBrowserExtension *ext, const char *state, unsigned int size );

static GtkXBrowserExtensionClass *parent_class = 0;

/* --------------------------- implementations --------------------------------------- */

/* type information */
GtkType
gtk_kmozilla_extension_get_type(void)
{
  static GtkType part_type = 0;
  if (!part_type)
  {
    static const GtkTypeInfo part_info =
    {
      "GtkKmozillaExtension",
      sizeof(GtkKmozillaExtension),
      sizeof(GtkKmozillaExtensionClass),
      (GtkClassInitFunc)gtk_kmozilla_extension_class_init,
      (GtkObjectInitFunc)gtk_kmozilla_extension_init,
      0,
      0,
      0
    };
    part_type = gtk_type_unique(GTK_TYPE_XBROWSEREXTENSION, &part_info);
  }
  return part_type;
}

/* class and instance initialization */
static void
gtk_kmozilla_extension_class_init(GtkKmozillaExtensionClass *klass)
{
    GtkObjectClass     *object_class = (GtkObjectClass *)klass;
    DcopObjectClass *dcop_class = DCOP_OBJECT_CLASS(klass);
    GtkXBrowserExtensionClass *be_class = GTK_XBROWSEREXTENSION_CLASS(klass);
    
    parent_class = (GtkXBrowserExtensionClass *)gtk_type_class(gtk_xbrowserextension_get_type());

    object_class->destroy = gtk_kmozilla_extension_destroy;

    be_class->save_state = save_state;
    be_class->restore_state = restore_state;

    g_message( "gtk_kmozillaextension_class_init\n" );
}

static void
gtk_kmozilla_extension_init(GtkKmozillaExtension *part)
{
    GtkKmozillaExtensionPrivate *d;
    d = g_new( GtkKmozillaExtensionPrivate, 1 );
    part->data = d;

    dcop_object_set_id( DCOP_OBJECT(part), "KmozillaExtensionClient" );

    g_message( "gtk_kmozillaextension_init\n" );
}

GtkKmozillaExtension *gtk_kmozilla_extension_new (void)
{
    return (GtkKmozillaExtension *) gtk_type_new(gtk_kmozilla_extension_get_type());
}


void gtk_kmozilla_extension_destroy( GtkObject *obj )
{
    GtkKmozillaExtension *part = GTK_KMOZILLA_EXTENSION(obj);
    GtkKmozillaExtensionPrivate *d = (GtkKmozillaExtensionPrivate *) part->data;
    g_free( d );
    
    GTK_OBJECT_CLASS(parent_class)->destroy(obj);
}

void kmozilla_extension_set_mozilla( GtkKmozillaExtension *ext, GtkKmozilla *moz )
{
    P->moz = moz;
}

static const char * save_state( GtkXBrowserExtension *ext )
{
    g_warning("Extension::save_state!");
    return 0;
}

static void restore_state ( GtkXBrowserExtension *ext, const char *state, unsigned int size )
{
    g_warning("Extension::restore_state!");
}
