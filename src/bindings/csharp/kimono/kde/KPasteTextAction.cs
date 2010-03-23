//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  An action for pasting text from the clipboard.
    ///  It's useful for text handling applications as
    ///  when plugged into a toolbar it provides a menu
    ///  with the clipboard history if klipper is running.
    ///  If klipper is not running, the menu has only one
    ///  item: the current clipboard content.
    ///  </remarks>        <short>    An action for pasting text from the clipboard.</short>
    [SmokeClass("KPasteTextAction")]
    public class KPasteTextAction : KAction, IDisposable {
        protected KPasteTextAction(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KPasteTextAction), this);
        }
        /// <remarks>
        ///  Constructs an action with the specified parent.
        /// <param> name="parent" The parent of this action.
        ///      </param></remarks>        <short>    Constructs an action with the specified parent.</short>
        public KPasteTextAction(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KPasteTextAction#", "KPasteTextAction(QObject*)", typeof(void), typeof(QObject), parent);
        }
        /// <remarks>
        ///  Constructs an action with text; a shortcut may be specified by
        ///  the ampersand character (e.g. "&amp;Option" creates a shortcut with key \e O )
        ///  This is the most common KAction used when you do not have a
        ///  corresponding icon (note that it won't appear in the current version
        ///  of the "Edit ToolBar" dialog, because an action needs an icon to be
        ///  plugged in a toolbar...).
        /// <param> name="text" The text that will be displayed.
        /// </param><param> name="parent" The parent of this action.
        ///      </param></remarks>        <short>    Constructs an action with text; a shortcut may be specified by  the ampersand character (e.</short>
        public KPasteTextAction(string text, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KPasteTextAction$#", "KPasteTextAction(const QString&, QObject*)", typeof(void), typeof(string), text, typeof(QObject), parent);
        }
        /// <remarks>
        ///  Constructs an action with text and an icon; a shortcut may be specified by
        ///  the ampersand character (e.g. "&amp;Option" creates a shortcut with key \e O )
        ///  This is the other common KAction used.  Use it when you
        ///  \e do have a corresponding icon.
        /// <param> name="icon" The icon to display.
        /// </param><param> name="text" The text that will be displayed.
        /// </param><param> name="parent" The parent of this action.
        ///      </param></remarks>        <short>    Constructs an action with text and an icon; a shortcut may be specified by  the ampersand character (e.</short>
        public KPasteTextAction(KIcon icon, string text, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KPasteTextAction#$#", "KPasteTextAction(const KIcon&, const QString&, QObject*)", typeof(void), typeof(KIcon), icon, typeof(string), text, typeof(QObject), parent);
        }
        /// <remarks>
        ///  Controls the behavior of the clipboard history menu popup.
        /// <param> name="mode" If false and the clipboard contains a non-text object
        ///              the popup menu with the clipboard history will appear
        ///              immediately as the user clicks the toolbar action; if
        ///              true, the action works like the standard paste action
        ///              even if the current clipboard object is not text.
        ///              Default value is true.
        ///     </param></remarks>        <short>    Controls the behavior of the clipboard history menu popup.</short>
        public void SetMixedMode(bool mode) {
            interceptor.Invoke("setMixedMode$", "setMixedMode(bool)", typeof(void), typeof(bool), mode);
        }
        ~KPasteTextAction() {
            interceptor.Invoke("~KPasteTextAction", "~KPasteTextAction()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KPasteTextAction", "~KPasteTextAction()", typeof(void));
        }
        protected new IKPasteTextActionSignals Emit {
            get { return (IKPasteTextActionSignals) Q_EMIT; }
        }
    }

    public interface IKPasteTextActionSignals : IKActionSignals {
    }
}
