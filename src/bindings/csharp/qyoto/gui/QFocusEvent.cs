//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QFocusEvent")]
    public class QFocusEvent : QEvent, IDisposable {
        protected QFocusEvent(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QFocusEvent), this);
        }
        public QFocusEvent(QEvent.TypeOf type, Qt.FocusReason reason) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QFocusEvent$$", "QFocusEvent(QEvent::Type, Qt::FocusReason)", typeof(void), typeof(QEvent.TypeOf), type, typeof(Qt.FocusReason), reason);
        }
        public QFocusEvent(QEvent.TypeOf type) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QFocusEvent$", "QFocusEvent(QEvent::Type)", typeof(void), typeof(QEvent.TypeOf), type);
        }
        public bool GotFocus() {
            return (bool) interceptor.Invoke("gotFocus", "gotFocus() const", typeof(bool));
        }
        public bool LostFocus() {
            return (bool) interceptor.Invoke("lostFocus", "lostFocus() const", typeof(bool));
        }
        public Qt.FocusReason Reason() {
            return (Qt.FocusReason) interceptor.Invoke("reason", "reason()", typeof(Qt.FocusReason));
        }
        ~QFocusEvent() {
            interceptor.Invoke("~QFocusEvent", "~QFocusEvent()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QFocusEvent", "~QFocusEvent()", typeof(void));
        }
    }
}
