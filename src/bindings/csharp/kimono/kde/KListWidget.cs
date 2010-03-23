//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  Extends the functionality of QListWidget to honor the system
    ///  wide settings for Single Click/Double Click mode, Auto Selection and
    ///  Change Cursor over Link.
    ///  There is a new signal executed(). It gets connected to either
    ///  QListWidget.ItemClicked() or QListWidget.ItemDoubleClicked()
    ///  depending on the KDE wide Single Click/Double Click settings. It is
    ///  strongly recommended that you use this signal instead of the above
    ///  mentioned. This way you don't need to care about the current
    ///  settings.  If you want to get informed when the user selects
    ///  something connect to the QListWidget.ItemSelectionChanged() signal.
    ///  See <see cref="IKListWidgetSignals"></see> for signals emitted by KListWidget
    /// </remarks>        <short> A variant of QListWidget that honors KDE's system-wide settings. </short>
    [SmokeClass("KListWidget")]
    public class KListWidget : QListWidget, IDisposable {
        protected KListWidget(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KListWidget), this);
        }
        public KListWidget(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KListWidget#", "KListWidget(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KListWidget() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KListWidget", "KListWidget()", typeof(void));
        }
        [SmokeMethod("keyPressEvent(QKeyEvent*)")]
        protected override void KeyPressEvent(QKeyEvent e) {
            interceptor.Invoke("keyPressEvent#", "keyPressEvent(QKeyEvent*)", typeof(void), typeof(QKeyEvent), e);
        }
        [SmokeMethod("focusOutEvent(QFocusEvent*)")]
        protected override void FocusOutEvent(QFocusEvent e) {
            interceptor.Invoke("focusOutEvent#", "focusOutEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), e);
        }
        [SmokeMethod("leaveEvent(QEvent*)")]
        protected override void LeaveEvent(QEvent e) {
            interceptor.Invoke("leaveEvent#", "leaveEvent(QEvent*)", typeof(void), typeof(QEvent), e);
        }
        [SmokeMethod("mousePressEvent(QMouseEvent*)")]
        protected override void MousePressEvent(QMouseEvent e) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), e);
        }
        [SmokeMethod("mouseDoubleClickEvent(QMouseEvent*)")]
        protected override void MouseDoubleClickEvent(QMouseEvent e) {
            interceptor.Invoke("mouseDoubleClickEvent#", "mouseDoubleClickEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), e);
        }
        ~KListWidget() {
            interceptor.Invoke("~KListWidget", "~KListWidget()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KListWidget", "~KListWidget()", typeof(void));
        }
        protected new IKListWidgetSignals Emit {
            get { return (IKListWidgetSignals) Q_EMIT; }
        }
    }

    public interface IKListWidgetSignals : IQListWidgetSignals {
        /// <remarks>
        ///  Emitted whenever the user executes an listbox item.
        ///  That means depending on the KDE wide Single Click/Double Click
        ///  setting the user clicked or double clicked on that item.
        /// <param> name="item" is the pointer to the executed listbox item.
        /// </param> Note that you may not delete any QListWidgetItem objects in slots
        ///  connected to this signal.
        ///    </remarks>        <short>    Emitted whenever the user executes an listbox item.</short>
        [Q_SIGNAL("void executed(QListWidgetItem*)")]
        void Executed(QListWidgetItem item);
        /// <remarks>
        ///  Emitted whenever the user executes an listbox item.
        ///  That means depending on the KDE wide Single Click/Double Click
        ///  setting the user clicked or double clicked on that item.
        /// <param> name="item" is the pointer to the executed listbox item.
        /// </param><param> name="pos" is the position where the user has clicked
        /// </param> Note that you may not delete any QListWidgetItem objects in slots
        ///  connected to this signal.
        ///    </remarks>        <short>    Emitted whenever the user executes an listbox item.</short>
        [Q_SIGNAL("void executed(QListWidgetItem*, QPoint)")]
        void Executed(QListWidgetItem item, QPoint pos);
        /// <remarks>
        ///  This signal gets emitted whenever the user double clicks into the
        ///  listbox.
        /// <param> name="item" The pointer to the clicked listbox item.
        /// </param><param> name="pos" The position where the user has clicked.
        /// </param> Note that you may not delete any QListWidgetItem objects in slots
        ///  connected to this signal.
        ///  This signal is more or less here for the sake of completeness.
        ///  You should normally not need to use this. In most cases it's better
        ///  to use executed() instead.
        ///    </remarks>        <short>    This signal gets emitted whenever the user double clicks into the  listbox.</short>
        [Q_SIGNAL("void doubleClicked(QListWidgetItem*, QPoint)")]
        void DoubleClicked(QListWidgetItem item, QPoint pos);
    }
}
