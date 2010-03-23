#ifndef _gtkxpart_h__
#define _gtkxpart_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <dcopc/dcopobject.h>
#include <dcopc/dcopc.h>
#include <dcopc/marshal.h>
#include <dcopc/util.h>

#include <gtk/gtk.h>

#include "gtkbrowserextension.h"
    
#define GTK_TYPE_XPART             (gtk_xpart_get_type())
#define GTK_XPART(obj)             GTK_CHECK_CAST((obj), GTK_TYPE_XPART, GtkXPart)
#define GTK_XPART_CLASS(klass)     GTK_CHECK_CLASS_CAST((klass), GTK_TYPE_XPART, GtkXPartClass)
#define GTK_IS_XPART(obj)          GTK_CHECK_TYPE((obj), GTK_TYPE_XPART)
#define GTK_IS_XPART_CLASS(klass)  GTK_CHECK_CLASS_TYPE((klass), GTK_TYPE_XPART)

#define GTK_XPART_WIDGET(part)  (gtk_xpart_get_widget(part))
#define GTK_XPART_DCOP(part) (gtk_xpart_get_dcop(part))

typedef struct _GtkXPart GtkXPart;
typedef struct _GtkXPartClass GtkXPartClass;

struct _GtkXPart
{
    DcopObject obj;
    void *data;
};

struct _GtkXPartClass
{
    DcopObjectClass parent_class;

    gboolean (* open_url) ( GtkXPart *part, const char * url );
    gboolean (* close_url) ( GtkXPart *part );

    /* virtual function, returns the dcop object id of the extension, or NULL if it
       doesn't exist */
    char * (*query_extension) ( GtkXPart *part, const char *name );
};

extern GtkType gtk_xpart_get_type (void);
extern GtkXPart *gtk_xpart_new (void);

/* "virtual" functions from DcopObject */
void gtk_xpart_set_dcop_client( GtkXPart *part, DcopClient *client );
gboolean gtk_xpart_register( GtkXPart *part, const gchar *host_app_id, const gchar *host_obj_id);
gboolean gtk_xpart_initialize_actions( GtkXPart *part, const char * actions );

void gtk_xpart_set_widget( GtkXPart *part, GtkWidget *widget );

#ifdef __cplusplus
}
#endif

#endif
