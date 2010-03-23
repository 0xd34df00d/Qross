#include <dcopclient.h>
#include <kapplication.h>
#include <qmultilineedit.h>
#include <qfile.h>
#include <qtextstream.h>
#include <stdio.h>
#include <iostream.h>
#include <xpart.h>
#include <kdebug.h>

#include "xparthost_stub.h"

class XPartNotepad :  public QMultiLineEdit, virtual public XPart
{

public:
	XPartNotepad(char *)
	{
		setText("This is a xpart component editor");
		setReadOnly( false );
		resize( 200, 200 );
		QMultiLineEdit::setFocus();
	}

	/** needed by XPartManager to embed the part */
	Q_UINT32 windowId()
	{ return winId(); }

	/** used by XPartManager to show the part */
	void show()
	{ printf("show()\n"); QWidget::show(); }

	/** sent by the XPartHost to query an url */
	bool openURL( const QCString& url )
	{ printf("openURL %s\n", (const char *) url ); 
		QFile f(url);
		QString s;
		if ( ! f.open(IO_ReadOnly) ) {
			return false;
		}
		QTextStream t( &f );
		while ( !t.eof() ) {
			s += t.readLine() + "\n";
		}
		f.close();
		setText(s);
		return true;
	}

	/** sent by the XPartHost to close an url */
	bool closeURL()
	{ printf("closeURL\n"); setText(""); return true; } 

	/** called when an action has been activated. name is
	* the name of the
	*      * action, state is used with Toggle actions to
	*      precise the current state.
	*           */
	void activateAction( const QString &name, int state )
	{ printf("activateAction: %s, %d\n", name.latin1(), state ); }	

	/** are extentions available -> browser extension
	 * / TextEditor ? */
	DCOPRef queryExtension( const QCString& extension )
	{ printf("query Extension : %s\n", (const char * ) extension ); return DCOPRef(); } 


protected:
	void focusInEvent( QFocusEvent * ) 
		{ kdDebug() << "Focus in" << endl; QMultiLineEdit::setFocus(); }
	void focusOutEvent( QFocusEvent * ) 
		{ kdDebug() << "Focus Out" << endl;QMultiLineEdit::setFocus(); }
};

int main( int argc, char **argv )
{
	if (argc < 3) {
		printf("application need arguments");
		return 1;
	}
	printf("args: XPartHost appId = %s , XPartHost_KPart objId = %s\n", argv[1], argv[2] );

    KApplication app( argc, argv, "xp_notepad" );
	XPartNotepad * xpn = new XPartNotepad("xp_notepad");
	app.setMainWidget( xpn );
	app.dcopClient()->attach();	
    QCString appId = app.dcopClient()->registerAs("xp_notepad", true);

	XPartHost_stub xph_stub( argv[1], argv[2] );
	DCOPRef xpn_dcopref( xpn );

	DCOPRef xph_dcopref = xph_stub.registerXPart(xpn_dcopref);
	if ( xph_dcopref.isNull() ) {
		printf("could not register\n");
		return 2;
	}
	printf("XPart registered!\n");

	// Initializing actions:
	const char * actions = 
"<!DOCTYPE actionList SYSTEM \"actionlist.dtd\">\n"
"<Actionlist>\n"
"    <Action name=\"open_url\" />\n"
"    <Action name=\"close_url\" />\n"
"    <Action name=\"nonexistant\" />\n"
"    <XMLFile location=\"./xp_notepad.rc\" />\n"
"</Actionlist>\n";
	xph_stub.createActions( actions );

    return app.exec();
}



