#ifndef _gtkxbrowserextension_h__
#define _gtkxbrowserextension_h__

#include <dcopc/dcopobject.h>
#include <dcopc/dcopc.h>
#include <dcopc/marshal.h>
#include <dcopc/util.h>

#include <gtk/gtk.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GTK_TYPE_XBROWSEREXTENSION             (gtk_xbrowserextension_get_type())
#define GTK_XBROWSEREXTENSION(obj)             GTK_CHECK_CAST((obj), GTK_TYPE_XBROWSEREXTENSION, GtkXBrowserExtension)
#define GTK_XBROWSEREXTENSION_CLASS(klass)     GTK_CHECK_CLASS_CAST((klass), GTK_TYPE_XBROWSEREXTENSION, GtkXBrowserExtensionClass)
#define GTK_IS_XBROWSEREXTENSION(obj)          GTK_CHECK_TYPE((obj), GTK_TYPE_XBROWSEREXTENSION)
#define GTK_IS_XBROWSEREXTENSION_CLASS(klass)  GTK_CHECK_CLASS_TYPE((klass), GTK_TYPE_XBROWSEREXTENSION)

#define GTK_XBROWSEREXTENSION_WIDGET(part)  (gtk_xbrowserextension_get_widget(part))
#define GTK_XBROWSEREXTENSION_DCOP(part) (gtk_xbrowserextension_get_dcop(part))

typedef struct _GtkXBrowserExtension GtkXBrowserExtension;
typedef struct _GtkXBrowserExtensionClass GtkXBrowserExtensionClass;

struct _GtkXBrowserExtension
{
    DcopObject obj;
    void *data;
};

struct _GtkXBrowserExtensionClass
{
    DcopObjectClass parent_class;

    const char * ( *save_state)( GtkXBrowserExtension *ext );
    void (* restore_state) ( GtkXBrowserExtension *ext, const char *state, unsigned int size );
};

extern GtkType gtk_xbrowserextension_get_type (void);
extern GtkXBrowserExtension *gtk_xbrowserextension_new (void);

gboolean gtk_browserextension_open_url_request( GtkXBrowserExtension *ext, const char *url );

/* "virtual" functions from DcopObject */
void gtk_xbrowserextension_set_dcop_client( GtkXBrowserExtension *part, DcopClient *client );
gboolean gtk_xbrowserextension_register( GtkXBrowserExtension *part, const gchar *host_app_id, const gchar *host_obj_id);

#ifdef __cplusplus
}
#endif

#endif
