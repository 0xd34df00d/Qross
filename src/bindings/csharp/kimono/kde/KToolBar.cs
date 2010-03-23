//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  A KDE-style toolbar.
    ///  KToolBar can be used as a standalone widget, but KMainWindow
    ///  provides easy factories and management of one or more toolbars.
    ///  KToolBar uses a global config group to load toolbar settings on
    ///  construction. It will reread this config group on a
    ///  KApplication.AppearanceChanged() signal.
    /// </remarks>        <author> Reginald Stadlbauer <reggie@kde.org>, Stephan Kulow <coolo@kde.org>, Sven Radej <radej@kde.org>, Hamish Rodda <rodda@kde.org>.
    ///   </author>
    ///         <short> Floatable toolbar with auto resize. </short>
    [SmokeClass("KToolBar")]
    public class KToolBar : QToolBar, IDisposable {
        protected KToolBar(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KToolBar), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static KToolBar() {
            staticInterceptor = new SmokeInvocation(typeof(KToolBar), null);
        }
        /// <remarks>
        ///  Normal constructor.
        ///  This constructor is used by the XML-GUI. If you use it, you need
        ///  to call QMainWindow.AddToolBar to specify the position of the toolbar.
        ///  So it's simpler to use the other constructor.
        ///  The toolbar will read in various global config settings for
        ///  things like icon size and text position, etc.  However, some of
        ///  the settings will be honored only if <code>honorStyle</code> is set to
        ///  true.  All other toolbars will be IconOnly and use Medium icons.
        /// <param> name="parent" The standard toolbar parent (usually a KMainWindow)
        /// </param><param> name="honorStyle" If true, then global settings for IconSize and IconText will be honored
        /// </param><param> name="readConfig" whether to apply the configuration (global and application-specific)
        ///      </param></remarks>        <short>    Normal constructor.</short>
        public KToolBar(QWidget parent, bool honorStyle, bool readConfig) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar#$$", "KToolBar(QWidget*, bool, bool)", typeof(void), typeof(QWidget), parent, typeof(bool), honorStyle, typeof(bool), readConfig);
        }
        public KToolBar(QWidget parent, bool honorStyle) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar#$", "KToolBar(QWidget*, bool)", typeof(void), typeof(QWidget), parent, typeof(bool), honorStyle);
        }
        public KToolBar(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar#", "KToolBar(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        /// <remarks>
        ///  Constructor for non-XML-GUI applications.
        ///  The toolbar will read in various global config settings for
        ///  things like icon size and text position, etc.  However, some of
        ///  the settings will be honored only if <code>honorStyle</code> is set to
        ///  true.  All other toolbars will be IconOnly and use Medium icons.
        /// <param> name="objectName" The QObject name of this toolbar, required so that QMainWindow can save and load the toolbar position
        /// </param><param> name="parentWindow" The window that should be the parent of this toolbar
        /// </param><param> name="area" The position of the toolbar. Usually Qt.TopToolBarArea.
        /// </param><param> name="newLine" If true, start a new line in the dock for this toolbar.
        /// </param><param> name="honorStyle" If true, then global settings for IconSize and IconText will be honored
        /// </param><param> name="readConfig" whether to apply the configuration (global and application-specific)
        ///      </param></remarks>        <short>    Constructor for non-XML-GUI applications.</short>
        public KToolBar(string objectName, QMainWindow parentWindow, Qt.ToolBarArea area, bool newLine, bool honorStyle, bool readConfig) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar$#$$$$", "KToolBar(const QString&, QMainWindow*, Qt::ToolBarArea, bool, bool, bool)", typeof(void), typeof(string), objectName, typeof(QMainWindow), parentWindow, typeof(Qt.ToolBarArea), area, typeof(bool), newLine, typeof(bool), honorStyle, typeof(bool), readConfig);
        }
        public KToolBar(string objectName, QMainWindow parentWindow, Qt.ToolBarArea area, bool newLine, bool honorStyle) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar$#$$$", "KToolBar(const QString&, QMainWindow*, Qt::ToolBarArea, bool, bool)", typeof(void), typeof(string), objectName, typeof(QMainWindow), parentWindow, typeof(Qt.ToolBarArea), area, typeof(bool), newLine, typeof(bool), honorStyle);
        }
        public KToolBar(string objectName, QMainWindow parentWindow, Qt.ToolBarArea area, bool newLine) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar$#$$", "KToolBar(const QString&, QMainWindow*, Qt::ToolBarArea, bool)", typeof(void), typeof(string), objectName, typeof(QMainWindow), parentWindow, typeof(Qt.ToolBarArea), area, typeof(bool), newLine);
        }
        public KToolBar(string objectName, QMainWindow parentWindow, Qt.ToolBarArea area) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBar$#$", "KToolBar(const QString&, QMainWindow*, Qt::ToolBarArea)", typeof(void), typeof(string), objectName, typeof(QMainWindow), parentWindow, typeof(Qt.ToolBarArea), area);
        }
        /// <remarks>
        ///  Returns the main window that this toolbar is docked with.
        ///      </remarks>        <short>    Returns the main window that this toolbar is docked with.</short>
        public KMainWindow MainWindow() {
            return (KMainWindow) interceptor.Invoke("mainWindow", "mainWindow() const", typeof(KMainWindow));
        }
        /// <remarks>
        ///  Convenience function to set icon size
        ///      </remarks>        <short>    Convenience function to set icon size      </short>
        public void SetIconDimensions(int size) {
            interceptor.Invoke("setIconDimensions$", "setIconDimensions(int)", typeof(void), typeof(int), size);
        }
        /// <remarks>
        ///  Returns the default size for this type of toolbar.
        /// </remarks>        <return> the default size for this type of toolbar.
        ///      </return>
        ///         <short>    Returns the default size for this type of toolbar.</short>
        public int IconSizeDefault() {
            return (int) interceptor.Invoke("iconSizeDefault", "iconSizeDefault() const", typeof(int));
        }
        /// <remarks>
        ///  Save the toolbar settings to group <code>configGroup</code> in <code>config.</code>
        ///      </remarks>        <short>    Save the toolbar settings to group <code>configGroup</code> in <code>config.</code></short>
        public void SaveSettings(KConfigGroup cg) {
            interceptor.Invoke("saveSettings#", "saveSettings(KConfigGroup&)", typeof(void), typeof(KConfigGroup), cg);
        }
        /// <remarks>
        ///  Read the toolbar settings from group <code>configGroup</code> in <code>config</code>
        ///  and apply them. Even default settings are re-applied if <code>force</code> is set.
        ///      </remarks>        <short>    Read the toolbar settings from group <code>configGroup</code> in <code>config</code>  and apply them.</short>
        public void ApplySettings(KConfigGroup cg, bool force) {
            interceptor.Invoke("applySettings#$", "applySettings(const KConfigGroup&, bool)", typeof(void), typeof(KConfigGroup), cg, typeof(bool), force);
        }
        public void ApplySettings(KConfigGroup cg) {
            interceptor.Invoke("applySettings#", "applySettings(const KConfigGroup&)", typeof(void), typeof(KConfigGroup), cg);
        }
        /// <remarks>
        ///  Sets the XML gui client.
        ///      </remarks>        <short>    Sets the XML gui client.</short>
        public void SetXMLGUIClient(IKXMLGUIClient client) {
            interceptor.Invoke("setXMLGUIClient#", "setXMLGUIClient(KXMLGUIClient*)", typeof(void), typeof(IKXMLGUIClient), client);
        }
        /// <remarks>
        ///  Load state from an XML @param element, called by KXMLGUIBuilder.
        ///      </remarks>        <short>    Load state from an XML @param element, called by KXMLGUIBuilder.</short>
        public void LoadState(QDomElement element) {
            interceptor.Invoke("loadState#", "loadState(const QDomElement&)", typeof(void), typeof(QDomElement), element);
        }
        /// <remarks>
        ///  Save state into an XML @param element, called by KXMLGUIBuilder.
        ///      </remarks>        <short>    Save state into an XML @param element, called by KXMLGUIBuilder.</short>
        public void SaveState(QDomElement element) {
            interceptor.Invoke("saveState#", "saveState(QDomElement&) const", typeof(void), typeof(QDomElement), element);
        }
        /// <remarks>
        ///  Reimplemented to support context menu activation on disabled tool buttons.
        ///      </remarks>        <short>    Reimplemented to support context menu activation on disabled tool buttons.</short>
        [SmokeMethod("eventFilter(QObject*, QEvent*)")]
        public override bool EventFilter(QObject watched, QEvent arg2) {
            return (bool) interceptor.Invoke("eventFilter##", "eventFilter(QObject*, QEvent*)", typeof(bool), typeof(QObject), watched, typeof(QEvent), arg2);
        }
        [SmokeMethod("contextMenuEvent(QContextMenuEvent*)")]
        protected override void ContextMenuEvent(QContextMenuEvent arg1) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QContextMenuEvent*)", typeof(void), typeof(QContextMenuEvent), arg1);
        }
        [SmokeMethod("actionEvent(QActionEvent*)")]
        protected override void ActionEvent(QActionEvent arg1) {
            interceptor.Invoke("actionEvent#", "actionEvent(QActionEvent*)", typeof(void), typeof(QActionEvent), arg1);
        }
        [SmokeMethod("dragEnterEvent(QDragEnterEvent*)")]
        protected override void DragEnterEvent(QDragEnterEvent arg1) {
            interceptor.Invoke("dragEnterEvent#", "dragEnterEvent(QDragEnterEvent*)", typeof(void), typeof(QDragEnterEvent), arg1);
        }
        [SmokeMethod("dragMoveEvent(QDragMoveEvent*)")]
        protected override void DragMoveEvent(QDragMoveEvent arg1) {
            interceptor.Invoke("dragMoveEvent#", "dragMoveEvent(QDragMoveEvent*)", typeof(void), typeof(QDragMoveEvent), arg1);
        }
        [SmokeMethod("dragLeaveEvent(QDragLeaveEvent*)")]
        protected override void DragLeaveEvent(QDragLeaveEvent arg1) {
            interceptor.Invoke("dragLeaveEvent#", "dragLeaveEvent(QDragLeaveEvent*)", typeof(void), typeof(QDragLeaveEvent), arg1);
        }
        [SmokeMethod("dropEvent(QDropEvent*)")]
        protected override void DropEvent(QDropEvent arg1) {
            interceptor.Invoke("dropEvent#", "dropEvent(QDropEvent*)", typeof(void), typeof(QDropEvent), arg1);
        }
        [SmokeMethod("mousePressEvent(QMouseEvent*)")]
        protected override void MousePressEvent(QMouseEvent arg1) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mouseMoveEvent(QMouseEvent*)")]
        protected override void MouseMoveEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseMoveEvent#", "mouseMoveEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mouseReleaseEvent(QMouseEvent*)")]
        protected override void MouseReleaseEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseReleaseEvent#", "mouseReleaseEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [Q_SLOT("void slotMovableChanged(bool)")]
        [SmokeMethod("slotMovableChanged(bool)")]
        protected virtual void SlotMovableChanged(bool movable) {
            interceptor.Invoke("slotMovableChanged$", "slotMovableChanged(bool)", typeof(void), typeof(bool), movable);
        }
        ~KToolBar() {
            interceptor.Invoke("~KToolBar", "~KToolBar()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KToolBar", "~KToolBar()", typeof(void));
        }
        /// <remarks>
        ///  Returns the global setting for "Icon Text"
        /// </remarks>        <return> global setting for "Icon Text"
        ///      </return>
        ///         <short>    Returns the global setting for "Icon Text" </short>
        public static Qt.ToolButtonStyle ToolButtonStyleSetting() {
            return (Qt.ToolButtonStyle) staticInterceptor.Invoke("toolButtonStyleSetting", "toolButtonStyleSetting()", typeof(Qt.ToolButtonStyle));
        }
        /// <remarks>
        ///  Returns whether the toolbars are currently editable (drag & drop of actions).
        ///      </remarks>        <short>    Returns whether the toolbars are currently editable (drag & drop of actions).</short>
        public static bool ToolBarsEditable() {
            return (bool) staticInterceptor.Invoke("toolBarsEditable", "toolBarsEditable()", typeof(bool));
        }
        /// <remarks>
        ///  Enable or disable toolbar editing via drag & drop of actions.  This is
        ///  called by KEditToolbar and should generally be set to disabled whenever
        ///  KEditToolbar is not active.
        ///      </remarks>        <short>    Enable or disable toolbar editing via drag & drop of actions.</short>
        public static void SetToolBarsEditable(bool editable) {
            staticInterceptor.Invoke("setToolBarsEditable$", "setToolBarsEditable(bool)", typeof(void), typeof(bool), editable);
        }
        /// <remarks>
        ///  Returns whether the toolbars are locked (i.e., moving of the toobars disallowed).
        ///      </remarks>        <short>    Returns whether the toolbars are locked (i.</short>
        public static bool ToolBarsLocked() {
            return (bool) staticInterceptor.Invoke("toolBarsLocked", "toolBarsLocked()", typeof(bool));
        }
        /// <remarks>
        ///  Allows you to lock and unlock all toolbars (i.e., disallow/allow moving of the toobars).
        ///      </remarks>        <short>    Allows you to lock and unlock all toolbars (i.</short>
        public static void SetToolBarsLocked(bool locked) {
            staticInterceptor.Invoke("setToolBarsLocked$", "setToolBarsLocked(bool)", typeof(void), typeof(bool), locked);
        }
        protected new IKToolBarSignals Emit {
            get { return (IKToolBarSignals) Q_EMIT; }
        }
    }

    public interface IKToolBarSignals : IQToolBarSignals {
    }
}
