#include "kmozilla.h"
#include <dcopc/dcopc.h>
#include "gtkpart.h"

#include <stdio.h>

gboolean dcop_socket_notify( GIOChannel *chan, GIOCondition condition, gpointer data )
{
    DcopClient *client = (DcopClient *)data;
    g_warning( "dcop_socket_notify\n" );
    dcop_client_process_socket_data( client );
    return TRUE;
}

void gtktest_exit()
{
    g_warning( "EXIT!\n" );
    gtk_main_quit();
}


int main( int argc, char **argv )
{
    GtkKmozilla *moz;
    GtkXPart *part;
    DcopClient *client;
    GIOChannel *socket_chan;

    gtk_init( &argc, &argv );

    moz = gtk_kmozilla_new( );
    part = (GtkXPart *)moz;
    client = dcop_client_new();
/*    dcop_client_attach( client );*/
    /* for debugging*/
    dcop_client_register_as( client, "kmozilla", TRUE );

    socket_chan = g_io_channel_unix_new( dcop_client_socket( client ) );
    g_io_channel_ref( socket_chan );
    g_io_add_watch( socket_chan, G_IO_IN, dcop_socket_notify, client );

    fprintf(stderr, "client initialized!\n");

    gtk_kmozilla_set_dcop_client(part, client);
    if(!gtk_xpart_register(part, argv[1], argv[2]))
	fprintf(stderr, "could not register part\n");
    
    {
	/* initialize actions */
	const char * actions = "<!DOCTYPE actionList SYSTEM \"actionlist.dtd\">\n"
			       "<Actionlist>\n"
			       "    <Action name=\"stop\" />\n"
			       "    <Action name=\"reload\" />\n"
			       "    <Action name=\"nonexistant\" />\n"
			       "    <XMLFile location=\"./kmozilla.rc\" />\n"
			       "</Actionlist>\n";
	gtk_xpart_initialize_actions( part, actions );
	fprintf(stderr, "hopfully initialized actions\n");
    }
    fprintf(stderr, "done!\n");

    gtk_main();

    g_io_channel_unref( socket_chan );

    gtk_object_destroy( GTK_OBJECT(client) );

    return 0;
}
