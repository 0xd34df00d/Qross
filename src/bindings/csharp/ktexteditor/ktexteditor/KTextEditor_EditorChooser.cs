//Auto-generated by kalyptus. DO NOT EDIT.
namespace KTextEditor {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///  \brief Editor Component Chooser.
    ///  Topics:
    ///   - \ref chooser_intro
    ///   - \ref chooser_gui
    ///   - \ref chooser_editor
    ///  \section chooser_intro Introduction
    ///  The EditorChooser is responsible for two different tasks: It provides
    ///   - a GUI, with which the user can choose the preferred editor part
    ///   - a static accessor, with which the current selected editor part can be
    ///     obtained.
    ///  \section chooser_gui The GUI Editor Chooser
    ///  The EditorChooser is a simple widget with a group box containing an
    ///  information label and a combo box which lists all available KTextEditor
    ///  implementations. To give the user the possibility to choose a text editor
    ///  implementation, create an instance of this class and put it into the GUI:
    ///  <pre>
    ///  KTextEditor.EditorChooser ec = new KTextEditor.EditorChooser(parent);
    ///  // read the settings from the application's KConfig object
    ///  ec.ReadAppSetting();
    ///  // optionally connect the signal changed()
    ///  // plug the widget into a layout
    ///  layout.AddWidget(ec);
    ///  </pre>
    ///  Later, for example when the user clicks the Apply-button:
    ///  <pre>
    ///  // save the user's choice
    ///  ec.WriteAppSetting();
    ///  </pre>
    ///  After this, the static accessor editor() will return the new editor part
    ///  object. Now, either the application has to be restarted, or you need code
    ///  that closes all current documents so that you can safely switch and use the
    ///  new editor part. Restarting is probably much easier.
    ///  <b>Note:<> If you do not put the EditorChooser into the GUI, the default editor
    ///        component will be used. The default editor is configurable in KDE's
    ///        control center in
    ///        "KDE Components > Component Chooser > Embedded Text Editor".
    ///  \section chooser_editor Accessing the Editor Part
    ///  The call of editor() will return the currently used editor part, either the
    ///  KDE default or the one configured with the EditorChooser's GUI
    ///  (see \ref chooser_gui). Example:
    ///  <pre>
    ///  KTextEditor.Editor editor = KTextEditor.EditorChooser.Editor();
    ///  </pre>
    ///  \see KTextEditor.Editor
    ///  \author Joseph Wenninger \<jowenn@kde.org\>
    ///   See <see cref="IEditorChooserSignals"></see> for signals emitted by EditorChooser
    /// </remarks>        <short>    \brief Editor Component Chooser.</short>
    [SmokeClass("KTextEditor::EditorChooser")]
    public class EditorChooser : QWidget, IDisposable {
        protected EditorChooser(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(EditorChooser), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static EditorChooser() {
            staticInterceptor = new SmokeInvocation(typeof(EditorChooser), null);
        }
        /// <remarks>
        ///  Constructor.
        ///  Create an editor chooser widget.
        ///  \param parent the parent widget
        ///      </remarks>        <short>    Constructor.</short>
        public EditorChooser(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("EditorChooser#", "EditorChooser(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public EditorChooser() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("EditorChooser", "EditorChooser()", typeof(void));
        }
        /// <remarks>
        ///  Read the configuration from the application's config file. The group
        ///  is handeled internally (it is called "KTEXTEDITOR:", but it is possible
        ///  to add a string to extend the group name with <pre>postfix</pre>.
        ///  \param postfix config group postfix string
        ///  \see writeAppSetting()
        ///      </remarks>        <short>    Read the configuration from the application's config file.</short>
        public void ReadAppSetting(string postfix) {
            interceptor.Invoke("readAppSetting$", "readAppSetting(const QString&)", typeof(void), typeof(string), postfix);
        }
        public void ReadAppSetting() {
            interceptor.Invoke("readAppSetting", "readAppSetting()", typeof(void));
        }
        /// <remarks>
        ///  Write the configuration to the application's config file.
        ///  \param postfix config group postfix string
        ///  \see readAppSetting()
        ///      </remarks>        <short>    Write the configuration to the application's config file.</short>
        public void WriteAppSetting(string postfix) {
            interceptor.Invoke("writeAppSetting$", "writeAppSetting(const QString&)", typeof(void), typeof(string), postfix);
        }
        public void WriteAppSetting() {
            interceptor.Invoke("writeAppSetting", "writeAppSetting()", typeof(void));
        }
        ~EditorChooser() {
            interceptor.Invoke("~EditorChooser", "~EditorChooser()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~EditorChooser", "~EditorChooser()", typeof(void));
        }
        /// <remarks>
        ///  Static accessor to get the Editor instance of the currently used
        ///  KTextEditor component.
        ///  That Editor instance can be qobject-cast to specific extensions.
        ///  If the result of the cast is not NULL, that extension is supported:
        ///  \param postfix config group postfix string
        ///  \param fallBackToKatePart if \e true, the returned Editor component
        ///         will be a katepart if no other implementation can be found
        ///  \return Editor controller or NULL, if no editor component could be
        ///         found
        ///      </remarks>        <short>    Static accessor to get the Editor instance of the currently used  KTextEditor component.</short>
        public static KTextEditor.Editor Editor(string postfix, bool fallBackToKatePart) {
            return (KTextEditor.Editor) staticInterceptor.Invoke("editor$$", "editor(const QString&, bool)", typeof(KTextEditor.Editor), typeof(string), postfix, typeof(bool), fallBackToKatePart);
        }
        public static KTextEditor.Editor Editor(string postfix) {
            return (KTextEditor.Editor) staticInterceptor.Invoke("editor$", "editor(const QString&)", typeof(KTextEditor.Editor), typeof(string), postfix);
        }
        public static KTextEditor.Editor Editor() {
            return (KTextEditor.Editor) staticInterceptor.Invoke("editor", "editor()", typeof(KTextEditor.Editor));
        }
        protected new IEditorChooserSignals Emit {
            get { return (IEditorChooserSignals) Q_EMIT; }
        }
    }

    public interface IEditorChooserSignals : IQWidgetSignals {
        /// <remarks>
        ///  This signal is emitted whenever the selected item in the combo box
        ///  changed.
        ///      </remarks>        <short>    This signal is emitted whenever the selected item in the combo box  changed.</short>
        [Q_SIGNAL("void changed()")]
        void Changed();
    }
}
