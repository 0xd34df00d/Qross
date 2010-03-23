#ifndef _gtk_kmozilla_h_
#define _gtk_kmozilla_h_

#include "gtkpart.h"

#define GTK_TYPE_KMOZILLA             (gtk_kmozilla_get_type())
#define GTK_KMOZILLA(obj)             GTK_CHECK_CAST((obj), GTK_TYPE_KMOZILLA, GtkKmozilla)
#define GTK_KMOZILLA_CLASS(klass)     GTK_CHECK_CLASS_CAST((klass), GTK_TYPE_KMOZILLA, GtkKmozillaClass)
#define GTK_IS_KMOZILLA(obj)          GTK_CHECK_TYPE((obj), GTK_TYPE_KMOZILLA)
#define GTK_IS_KMOZILLA_CLASS(klass)  GTK_CHECK_CLASS_TYPE((klass), GTK_TYPE_KMOZILLA)

#define GTK_KMOZILLA_WIDGET(part)  (gtk_kmozilla_get_widget(part))
#define GTK_KMOZILLA_DCOP(part) (gtk_kmozilla_get_dcop(part))

typedef struct _GtkKmozilla GtkKmozilla;
typedef struct _GtkKmozillaClass GtkKmozillaClass;

struct _GtkKmozilla
{
    GtkXPart part;
    void *data;
};

struct _GtkKmozillaClass
{
    GtkXPartClass parent_class;
};

extern GtkType gtk_kmozilla_get_type (void);
extern GtkKmozilla *gtk_kmozilla_new (void);

void gtk_kmozilla_set_dcop_client( GtkKmozilla *part, DcopClient *client );

#endif
