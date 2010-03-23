//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  KToolBarLabelAction is a convenience class for displaying a label in a
    ///  toolbar.
    ///  It provides easy access to the label's #setBuddy(QAction) and #buddy()
    ///  methods and can be used as follows:
    ///  <pre>
    ///  KHistoryCombo findCombo = new KHistoryCombo( true, this );
    ///  KWidgetAction action = new KWidgetAction( findCombo, i18n("Find Combo"),
    ///                                             Qt.Key_F6, this, SLOT("slotFocus()"),
    ///                                             actionCollection(), "find_combo");
    ///  KAction action = new KToolBarLabelAction( action, i18n( "Find "), "find_label" );
    ///  action.SetShortcut( Qt.Key_F6 );
    ///  connect( action, SIGNAL("triggered()"), this, SLOT("slotFocus()") );
    ///  </pre>
    ///  See <see cref="IKToolBarLabelActionSignals"></see> for signals emitted by KToolBarLabelAction
    /// </remarks>        <author> Felix Berger <felixberger@beldesign.de>
    ///  </author>
    ///         <short> Class to display a label in a toolbar. </short>
    [SmokeClass("KToolBarLabelAction")]
    public class KToolBarLabelAction : KAction, IDisposable {
        protected KToolBarLabelAction(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KToolBarLabelAction), this);
        }
        /// <remarks>
        ///  Creates a toolbar label.
        /// <param> name="text" The label's and the action's text.
        /// </param><param> name="parent" This action's parent.
        ///      </param></remarks>        <short>    Creates a toolbar label.</short>
        public KToolBarLabelAction(string text, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBarLabelAction$#", "KToolBarLabelAction(const QString&, QObject*)", typeof(void), typeof(string), text, typeof(QObject), parent);
        }
        /// <remarks>
        ///  Creates a toolbar label setting a buddy for the label.
        /// <param> name="buddy" The action whose widget which is focused when the label's accelerator is
        ///  typed.
        /// </param><param> name="text" The label's and the action's text.
        /// </param><param> name="parent" This action's parent.
        ///      </param></remarks>        <short>    Creates a toolbar label setting a buddy for the label.</short>
        public KToolBarLabelAction(QAction buddy, string text, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KToolBarLabelAction#$#", "KToolBarLabelAction(QAction*, const QString&, QObject*)", typeof(void), typeof(QAction), buddy, typeof(string), text, typeof(QObject), parent);
        }
        /// <remarks>
        ///  Sets the label's buddy to buddy.
        ///  See QLabel#setBuddy() for details.
        ///      </remarks>        <short>    Sets the label's buddy to buddy.</short>
        public void SetBuddy(QAction buddy) {
            interceptor.Invoke("setBuddy#", "setBuddy(QAction*)", typeof(void), typeof(QAction), buddy);
        }
        /// <remarks>
        ///  Returns the label's buddy or 0 if no buddy is currently set.
        ///  See QLabel#buddy() and QLabel#setBuddy() for more information.
        ///      </remarks>        <short>    Returns the label's buddy or 0 if no buddy is currently set.</short>
        public QAction Buddy() {
            return (QAction) interceptor.Invoke("buddy", "buddy() const", typeof(QAction));
        }
        /// <remarks>
        ///  Reimplemented from @see QActionWidgetFactory.
        ///      </remarks>        <short>    Reimplemented from @see QActionWidgetFactory.</short>
        [SmokeMethod("createWidget(QWidget*)")]
        public new virtual QWidget CreateWidget(QWidget parent) {
            return (QWidget) interceptor.Invoke("createWidget#", "createWidget(QWidget*)", typeof(QWidget), typeof(QWidget), parent);
        }
        [SmokeMethod("event(QEvent*)")]
        protected override bool Event(QEvent arg1) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), arg1);
        }
        [SmokeMethod("eventFilter(QObject*, QEvent*)")]
        protected override bool EventFilter(QObject watched, QEvent arg2) {
            return (bool) interceptor.Invoke("eventFilter##", "eventFilter(QObject*, QEvent*)", typeof(bool), typeof(QObject), watched, typeof(QEvent), arg2);
        }
        ~KToolBarLabelAction() {
            interceptor.Invoke("~KToolBarLabelAction", "~KToolBarLabelAction()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KToolBarLabelAction", "~KToolBarLabelAction()", typeof(void));
        }
        protected new IKToolBarLabelActionSignals Emit {
            get { return (IKToolBarLabelActionSignals) Q_EMIT; }
        }
    }

    public interface IKToolBarLabelActionSignals : IKActionSignals {
        /// <remarks>
        ///  This signal is emmitted whenever the text of this action
        ///  is changed.
        ///      </remarks>        <short>    This signal is emmitted whenever the text of this action  is changed.</short>
        [Q_SIGNAL("void textChanged(QString)")]
        void TextChanged(string newText);
    }
}
