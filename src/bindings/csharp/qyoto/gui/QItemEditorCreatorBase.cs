//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QItemEditorCreatorBase")]
    public abstract class QItemEditorCreatorBase : Object {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QItemEditorCreatorBase(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QItemEditorCreatorBase), this);
        }
        [SmokeMethod("createWidget(QWidget*) const")]
        public abstract QWidget CreateWidget(QWidget parent);
        [SmokeMethod("valuePropertyName() const")]
        public abstract QByteArray ValuePropertyName();
        public QItemEditorCreatorBase() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QItemEditorCreatorBase", "QItemEditorCreatorBase()", typeof(void));
        }
    }
}
