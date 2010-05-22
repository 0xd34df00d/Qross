// #!/usr/bin/env qross

/*
    This function does print some general information about
    Qross to stdout.
*/
function printInfos()
{
    function inspect(v) {
        var items = new Array();
        for(i in v)
            items.push(i);
        return items;
    }

    // print the items the Qross object provides
    print(Qross + " [" + inspect(Qross) + "]\n");

    // print the items the Qross.self object provides
    //print(Qross.self + " [" + inspect(Qross.self) + "]\n");

    // print the list of supported interpreters
    print("interpreters=" + Qross.interpreters() + "\n");
}

/*
    This function does execute Python scripting code using
    the Qross Scripting Framework.
*/
function executePythonCode(PythonScriptCode)
{
    // create an action-instance which is our script
    var action = Qross.action("MyPythonScript");
    // publish our action instance as "MyAction"
    action.addQObject(action, "MyAction");
    // set the name of the used interpreter.
    action.setInterpreter("python");

    // set the python scripting code we like to execute.
    //action.setCode( Qross.QByteArray(PythonScriptCode) );
    action.setCode( PythonScriptCode );

    // finally execute the script
    action.trigger();
}

/*
    This function does execute a Python scripting file using
    the Qross Scripting Framework.
*/
function executePythonFile(PythonFileName)
{
    // create an action-instance which is our script
    var action = Qross.action(PythonFileName);
    // publish our action instance as "MyAction"
    action.addQObject(action, "MyAction");
    // set the scripting file that should be executed
    action.setFile(PythonFileName);
    // finally execute the script
    action.trigger();
}

/*
    This function does show a dialog using the Qross forms-module
    shipped together with qross in kdelibs. The forms module does
    provide us some high-level functionality like KPageDialog,
    KFileWidget and the UI-loader. All the functionality provided
    within that module is accessible from within all supported
    scripting languages.
*/
function showQrossForms()
{
    var qrossforms = Qross.module("forms");
    var dialog = qrossforms.createDialog("My Dialog");
    dialog.setButtons("Ok|Cancel");
    dialog.setFaceType("List"); //Auto Plain List Tree Tabbed
    var mypage = dialog.addPage("My Page","This is my page","document-save");
    var lst = new QListWidget(mypage);
    var btn = new QPushButton(mypage);
    dialog.exec_loop();
}

/*
    This function does show a dialog using the QtScript
    functionality.
*/
function showDialog()
{
    var dialog = new QDialog();
    layout = new QVBoxLayout(dialog);

    var otherlayout = new QHBoxLayout();
    var brw = new QTextBrowser(dialog);
    brw.html = "Some <b>HTML</b> text";
    otherlayout.addWidget(brw);
    var lst = new QListWidget(dialog);
    otherlayout.addWidget(lst);
    layout.addLayout(otherlayout);

    var gridlayout = new QGridLayout();
    var lbl = new QLabel(dialog);
    lbl.text = "First Label";
    gridlayout.addWidget(lbl, 0, 0);
    var btn = new QPushButton(dialog);
    btn.text = "First Button";
    gridlayout.addWidget(btn, 0, 1);
    var lbl = new QLabel(dialog);
    lbl.text = "Second Label";
    gridlayout.addWidget(lbl, 1, 0);
    var btn = new QPushButton(dialog);
    btn.text = "Second Button";
    gridlayout.addWidget(btn, 1, 1);
    layout.addLayout(gridlayout);

    dialog.exec();
}

printInfos();
//executePythonCode("import MyAction ; print 'This is Python. name=>',MyAction.name()");
//executePythonFile("/home/kde4/svn/_src/kdelibs/qross/ext/test.py");
//showQrossForms();
//showDialog();
