#ifndef _kmozillaextension_h__
#define _kmozillaextension_h__

#include "gtkbrowserextension.h"    
#include "kmozilla.h"

#ifdef __cplusplus
extern "C" {
#endif


#define GTK_TYPE_KMOZILLA_EXTENSION             (gtk_kmozilla_extension_get_type())
#define GTK_KMOZILLA_EXTENSION(obj)             GTK_CHECK_CAST((obj), GTK_TYPE_KMOZILLA_EXTENSION, GtkKmozillaExtension)
#define GTK_KMOZILLAEXTENSION_CLASS(klass)     GTK_CHECK_CLASS_CAST((klass), GTK_TYPE_KMOZILLA_EXTENSION, GtkKmozillaExtensionClass)
#define GTK_IS_KMOZILLA_EXTENSION(obj)          GTK_CHECK_TYPE((obj), GTK_TYPE_KMOZILLA_EXTENSION)
#define GTK_IS_KMOZILLA_EXTENSION_CLASS(klass)  GTK_CHECK_CLASS_TYPE((klass), GTK_TYPE_KMOZILLA_EXTENSION)

typedef struct _GtkKmozillaExtension GtkKmozillaExtension;
typedef struct _GtkKmozillaExtensionClass GtkKmozillaExtensionClass;

struct _GtkKmozillaExtension
{
    GtkXBrowserExtension obj;
    void *data;
};

struct _GtkKmozillaExtensionClass
{
    GtkXBrowserExtensionClass parent_class;
};

extern GtkType gtk_kmozilla_extension_get_type (void);
extern GtkKmozillaExtension *gtk_kmozilla_extension_new (void);

extern void kmozilla_extension_set_mozilla( GtkKmozillaExtension *ext, GtkKmozilla *moz );

#ifdef __cplusplus
}
#endif

#endif
