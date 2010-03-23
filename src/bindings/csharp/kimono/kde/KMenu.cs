//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  KMenu is a class for menus with  keyboard
    ///  accessibility for popups with many options and/or varying options. It acts
    ///  identically to QMenu, with the addition of setKeyboardShortcutsEnabled() and
    ///  setKeyboardShortcutsExecute() methods.
    ///  The keyboard search algorithm is incremental with additional underlining
    ///  for user feedback.
    ///  See <see cref="IKMenuSignals"></see> for signals emitted by KMenu
    /// </remarks>        <author> Hamish Rodda <rodda@kde.org>
    ///  </author>
    ///         <short> A menu with keyboard searching.</short>
    [SmokeClass("KMenu")]
    public class KMenu : QMenu, IDisposable {
        protected KMenu(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KMenu), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static KMenu() {
            staticInterceptor = new SmokeInvocation(typeof(KMenu), null);
        }
        /// <remarks>
        ///  Constructs a KMenu.
        ///      </remarks>        <short>    Constructs a KMenu.</short>
        public KMenu(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMenu#", "KMenu(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KMenu() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMenu", "KMenu()", typeof(void));
        }
        /// <remarks>
        ///  Constructs a KMenu.
        ///  \param title The text displayed in a parent menu when it is inserted
        ///               into another menu as a submenu.
        ///  \param parent the parent QWidget object
        ///      </remarks>        <short>    Constructs a KMenu.</short>
        public KMenu(string title, QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMenu$#", "KMenu(const QString&, QWidget*)", typeof(void), typeof(string), title, typeof(QWidget), parent);
        }
        public KMenu(string title) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMenu$", "KMenu(const QString&)", typeof(void), typeof(string), title);
        }
        /// <remarks>
        ///  Inserts a title item with no icon.
        ///      </remarks>        <short>    Inserts a title item with no icon.</short>
        public QAction AddTitle(string text, QAction before) {
            return (QAction) interceptor.Invoke("addTitle$#", "addTitle(const QString&, QAction*)", typeof(QAction), typeof(string), text, typeof(QAction), before);
        }
        public QAction AddTitle(string text) {
            return (QAction) interceptor.Invoke("addTitle$", "addTitle(const QString&)", typeof(QAction), typeof(string), text);
        }
        /// <remarks>
        ///  Inserts a title item with the given icon and title.
        ///      </remarks>        <short>    Inserts a title item with the given icon and title.</short>
        public QAction AddTitle(QIcon icon, string text, QAction before) {
            return (QAction) interceptor.Invoke("addTitle#$#", "addTitle(const QIcon&, const QString&, QAction*)", typeof(QAction), typeof(QIcon), icon, typeof(string), text, typeof(QAction), before);
        }
        public QAction AddTitle(QIcon icon, string text) {
            return (QAction) interceptor.Invoke("addTitle#$", "addTitle(const QIcon&, const QString&)", typeof(QAction), typeof(QIcon), icon, typeof(string), text);
        }
        /// <remarks>
        ///  Enables keyboard navigation by searching for the entered key sequence.
        ///  Also underlines the currently selected item, providing feedback on the search.
        ///  Defaults to off.
        ///  \warning calls to text() of currently keyboard-selected items will
        ///  contain additional ampersand characters.
        ///  \warning though pre-existing keyboard shortcuts will not interfere with the
        ///  operation of this feature, they may be confusing to the user as the existing
        ///  shortcuts will not work.  In addition, where text already contains ampersands,
        ///  the underline produced is likely to confuse the user (as this feature uses
        ///  underlining of text to indicate the current key selection sequence).
        ///      </remarks>        <short>    Enables keyboard navigation by searching for the entered key sequence.</short>
        public void SetKeyboardShortcutsEnabled(bool enable) {
            interceptor.Invoke("setKeyboardShortcutsEnabled$", "setKeyboardShortcutsEnabled(bool)", typeof(void), typeof(bool), enable);
        }
        /// <remarks>
        ///  Enables execution of the menu item once it is uniquely specified.
        ///  Defaults to off.
        ///      </remarks>        <short>    Enables execution of the menu item once it is uniquely specified.</short>
        public void SetKeyboardShortcutsExecute(bool enable) {
            interceptor.Invoke("setKeyboardShortcutsExecute$", "setKeyboardShortcutsExecute(bool)", typeof(void), typeof(bool), enable);
        }
        /// <remarks>
        ///  Returns the context menu associated with this menu
        ///  The data property of all actions inserted into the context menu is modified
        ///  all the time to point to the action and menu it has been shown for
        ///      </remarks>        <short>    Returns the context menu associated with this menu  The data property of all actions inserted into the context menu is modified  all the time to point to the action and menu it has been shown for      </short>
        public QMenu ContextMenu() {
            return (QMenu) interceptor.Invoke("contextMenu", "contextMenu()", typeof(QMenu));
        }
        /// <remarks>
        ///  Hides the context menu if shown
        ///      </remarks>        <short>    Hides the context menu if shown      </short>
        public void HideContextMenu() {
            interceptor.Invoke("hideContextMenu", "hideContextMenu()", typeof(void));
        }
        /// <remarks>
        ///  Return the state of the mouse buttons when the last menuitem was activated.
        ///      </remarks>        <short>    Return the state of the mouse buttons when the last menuitem was activated.</short>
        public uint MouseButtons() {
            return (uint) interceptor.Invoke("mouseButtons", "mouseButtons() const", typeof(uint));
        }
        /// <remarks>
        ///  Return the state of the keyboard modifiers when the last menuitem was activated.
        ///      </remarks>        <short>    Return the state of the keyboard modifiers when the last menuitem was activated.</short>
        public uint KeyboardModifiers() {
            return (uint) interceptor.Invoke("keyboardModifiers", "keyboardModifiers() const", typeof(uint));
        }
        [SmokeMethod("closeEvent(QCloseEvent*)")]
        protected override void CloseEvent(QCloseEvent arg1) {
            interceptor.Invoke("closeEvent#", "closeEvent(QCloseEvent*)", typeof(void), typeof(QCloseEvent), arg1);
        }
        [SmokeMethod("keyPressEvent(QKeyEvent*)")]
        protected override void KeyPressEvent(QKeyEvent e) {
            interceptor.Invoke("keyPressEvent#", "keyPressEvent(QKeyEvent*)", typeof(void), typeof(QKeyEvent), e);
        }
        [SmokeMethod("mouseReleaseEvent(QMouseEvent*)")]
        protected override void MouseReleaseEvent(QMouseEvent e) {
            interceptor.Invoke("mouseReleaseEvent#", "mouseReleaseEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), e);
        }
        [SmokeMethod("mousePressEvent(QMouseEvent*)")]
        protected override void MousePressEvent(QMouseEvent e) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), e);
        }
        [SmokeMethod("focusNextPrevChild(bool)")]
        protected override bool FocusNextPrevChild(bool next) {
            return (bool) interceptor.Invoke("focusNextPrevChild$", "focusNextPrevChild(bool)", typeof(bool), typeof(bool), next);
        }
        [SmokeMethod("contextMenuEvent(QContextMenuEvent*)")]
        protected override void ContextMenuEvent(QContextMenuEvent e) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QContextMenuEvent*)", typeof(void), typeof(QContextMenuEvent), e);
        }
        [SmokeMethod("hideEvent(QHideEvent*)")]
        protected override void HideEvent(QHideEvent arg1) {
            interceptor.Invoke("hideEvent#", "hideEvent(QHideEvent*)", typeof(void), typeof(QHideEvent), arg1);
        }
        ~KMenu() {
            interceptor.Invoke("~KMenu", "~KMenu()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KMenu", "~KMenu()", typeof(void));
        }
        /// <remarks>
        ///  Returns the KMenu associated with the current context menu
        ///      </remarks>        <short>    Returns the KMenu associated with the current context menu      </short>
        public static KMenu ContextMenuFocus() {
            return (KMenu) staticInterceptor.Invoke("contextMenuFocus", "contextMenuFocus()", typeof(KMenu));
        }
        /// <remarks>
        ///  returns the QAction associated with the current context menu
        ///      </remarks>        <short>    returns the QAction associated with the current context menu      </short>
        public static QAction ContextMenuFocusAction() {
            return (QAction) staticInterceptor.Invoke("contextMenuFocusAction", "contextMenuFocusAction()", typeof(QAction));
        }
        protected new IKMenuSignals Emit {
            get { return (IKMenuSignals) Q_EMIT; }
        }
    }

    public interface IKMenuSignals : IQMenuSignals {
        /// <remarks>
        ///  connect to this signal to be notified when a context menu is about to be shown
        /// <param> name="menu" The menu that the context menu is about to be shown for
        /// </param><param> name="menuAction" The action that the context menu is currently on
        /// </param><param> name="ctxMenu" The context menu itself
        ///      </param></remarks>        <short>    connect to this signal to be notified when a context menu is about to be shown </short>
        [Q_SIGNAL("void aboutToShowContextMenu(KMenu*, QAction*, QMenu*)")]
        void AboutToShowContextMenu(KMenu menu, QAction menuAction, QMenu ctxMenu);
    }
}
