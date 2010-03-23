#ifndef shell_xparthost_h
#define shell_xparthost_h

#include <kmainwindow.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>

class KProcess;

class ShellWindow : public KParts::MainWindow
{
    Q_OBJECT

public:
    ShellWindow();
    virtual ~ShellWindow();

public slots:
    void hop();

    void slotOpenUrl( const QString &url );
    void mergeGUI();

private:
    XPartHost_KPart *m_host;
    KProcess *m_partProcess;
};

#endif
