//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QInputMethodEvent")]
    public class QInputMethodEvent : QEvent, IDisposable {
        protected QInputMethodEvent(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QInputMethodEvent), this);
        }
        public enum AttributeType {
            TextFormat = 0,
            Cursor = 1,
            Language = 2,
            Ruby = 3,
            Selection = 4,
        }
        // QInputMethodEvent* QInputMethodEvent(const QString& arg1,const QList<QInputMethodEvent::Attribute>& arg2); >>>> NOT CONVERTED
        // const QList<QInputMethodEvent::Attribute>& attributes(); >>>> NOT CONVERTED
        public QInputMethodEvent() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QInputMethodEvent", "QInputMethodEvent()", typeof(void));
        }
        public void SetCommitString(string commitString, int replaceFrom, int replaceLength) {
            interceptor.Invoke("setCommitString$$$", "setCommitString(const QString&, int, int)", typeof(void), typeof(string), commitString, typeof(int), replaceFrom, typeof(int), replaceLength);
        }
        public void SetCommitString(string commitString, int replaceFrom) {
            interceptor.Invoke("setCommitString$$", "setCommitString(const QString&, int)", typeof(void), typeof(string), commitString, typeof(int), replaceFrom);
        }
        public void SetCommitString(string commitString) {
            interceptor.Invoke("setCommitString$", "setCommitString(const QString&)", typeof(void), typeof(string), commitString);
        }
        public string PreeditString() {
            return (string) interceptor.Invoke("preeditString", "preeditString() const", typeof(string));
        }
        public string CommitString() {
            return (string) interceptor.Invoke("commitString", "commitString() const", typeof(string));
        }
        public int ReplacementStart() {
            return (int) interceptor.Invoke("replacementStart", "replacementStart() const", typeof(int));
        }
        public int ReplacementLength() {
            return (int) interceptor.Invoke("replacementLength", "replacementLength() const", typeof(int));
        }
        public QInputMethodEvent(QInputMethodEvent other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QInputMethodEvent#", "QInputMethodEvent(const QInputMethodEvent&)", typeof(void), typeof(QInputMethodEvent), other);
        }
        ~QInputMethodEvent() {
            interceptor.Invoke("~QInputMethodEvent", "~QInputMethodEvent()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QInputMethodEvent", "~QInputMethodEvent()", typeof(void));
        }
    }
}
