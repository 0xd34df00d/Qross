//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QDomCDATASection")]
    public class QDomCDATASection : QDomText, IDisposable {
        protected QDomCDATASection(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QDomCDATASection), this);
        }
        public QDomCDATASection() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDomCDATASection", "QDomCDATASection()", typeof(void));
        }
        public QDomCDATASection(QDomCDATASection x) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDomCDATASection#", "QDomCDATASection(const QDomCDATASection&)", typeof(void), typeof(QDomCDATASection), x);
        }
        public new QDomNode.NodeType NodeType() {
            return (QDomNode.NodeType) interceptor.Invoke("nodeType", "nodeType() const", typeof(QDomNode.NodeType));
        }
        ~QDomCDATASection() {
            interceptor.Invoke("~QDomCDATASection", "~QDomCDATASection()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QDomCDATASection", "~QDomCDATASection()", typeof(void));
        }
    }
}
