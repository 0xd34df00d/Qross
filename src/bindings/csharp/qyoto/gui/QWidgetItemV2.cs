//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QWidgetItemV2")]
    public class QWidgetItemV2 : QWidgetItem, IDisposable {
        protected QWidgetItemV2(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QWidgetItemV2), this);
        }
        public const int Dirty = -123;
        public const int HfwCacheMaxSize = 3;
        public QWidgetItemV2(QWidget widget) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QWidgetItemV2#", "QWidgetItemV2(QWidget*)", typeof(void), typeof(QWidget), widget);
        }
        [SmokeMethod("sizeHint() const")]
        public override QSize SizeHint() {
            return (QSize) interceptor.Invoke("sizeHint", "sizeHint() const", typeof(QSize));
        }
        [SmokeMethod("minimumSize() const")]
        public override QSize MinimumSize() {
            return (QSize) interceptor.Invoke("minimumSize", "minimumSize() const", typeof(QSize));
        }
        [SmokeMethod("maximumSize() const")]
        public override QSize MaximumSize() {
            return (QSize) interceptor.Invoke("maximumSize", "maximumSize() const", typeof(QSize));
        }
        [SmokeMethod("heightForWidth(int) const")]
        public override int HeightForWidth(int width) {
            return (int) interceptor.Invoke("heightForWidth$", "heightForWidth(int) const", typeof(int), typeof(int), width);
        }
        ~QWidgetItemV2() {
            interceptor.Invoke("~QWidgetItemV2", "~QWidgetItemV2()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QWidgetItemV2", "~QWidgetItemV2()", typeof(void));
        }
    }
}
