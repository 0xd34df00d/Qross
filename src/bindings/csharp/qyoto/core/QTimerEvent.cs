//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QTimerEvent")]
    public class QTimerEvent : QEvent, IDisposable {
        protected QTimerEvent(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QTimerEvent), this);
        }
        public QTimerEvent(int timerId) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTimerEvent$", "QTimerEvent(int)", typeof(void), typeof(int), timerId);
        }
        public int TimerId() {
            return (int) interceptor.Invoke("timerId", "timerId() const", typeof(int));
        }
        ~QTimerEvent() {
            interceptor.Invoke("~QTimerEvent", "~QTimerEvent()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QTimerEvent", "~QTimerEvent()", typeof(void));
        }
    }
}
