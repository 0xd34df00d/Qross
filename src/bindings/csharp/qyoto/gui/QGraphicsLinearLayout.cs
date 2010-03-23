//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QGraphicsLinearLayout")]
    public class QGraphicsLinearLayout : QGraphicsLayout, IDisposable {
        protected QGraphicsLinearLayout(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QGraphicsLinearLayout), this);
        }
        public QGraphicsLinearLayout(IQGraphicsLayoutItem parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsLinearLayout#", "QGraphicsLinearLayout(QGraphicsLayoutItem*)", typeof(void), typeof(IQGraphicsLayoutItem), parent);
        }
        public QGraphicsLinearLayout() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsLinearLayout", "QGraphicsLinearLayout()", typeof(void));
        }
        public QGraphicsLinearLayout(Qt.Orientation orientation, IQGraphicsLayoutItem parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsLinearLayout$#", "QGraphicsLinearLayout(Qt::Orientation, QGraphicsLayoutItem*)", typeof(void), typeof(Qt.Orientation), orientation, typeof(IQGraphicsLayoutItem), parent);
        }
        public QGraphicsLinearLayout(Qt.Orientation orientation) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsLinearLayout$", "QGraphicsLinearLayout(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), orientation);
        }
        public void SetOrientation(Qt.Orientation orientation) {
            interceptor.Invoke("setOrientation$", "setOrientation(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), orientation);
        }
        public Qt.Orientation Orientation() {
            return (Qt.Orientation) interceptor.Invoke("orientation", "orientation() const", typeof(Qt.Orientation));
        }
        public void AddItem(IQGraphicsLayoutItem item) {
            interceptor.Invoke("addItem#", "addItem(QGraphicsLayoutItem*)", typeof(void), typeof(IQGraphicsLayoutItem), item);
        }
        public void AddStretch(int stretch) {
            interceptor.Invoke("addStretch$", "addStretch(int)", typeof(void), typeof(int), stretch);
        }
        public void AddStretch() {
            interceptor.Invoke("addStretch", "addStretch()", typeof(void));
        }
        public void InsertItem(int index, IQGraphicsLayoutItem item) {
            interceptor.Invoke("insertItem$#", "insertItem(int, QGraphicsLayoutItem*)", typeof(void), typeof(int), index, typeof(IQGraphicsLayoutItem), item);
        }
        public void InsertStretch(int index, int stretch) {
            interceptor.Invoke("insertStretch$$", "insertStretch(int, int)", typeof(void), typeof(int), index, typeof(int), stretch);
        }
        public void InsertStretch(int index) {
            interceptor.Invoke("insertStretch$", "insertStretch(int)", typeof(void), typeof(int), index);
        }
        public void RemoveItem(IQGraphicsLayoutItem item) {
            interceptor.Invoke("removeItem#", "removeItem(QGraphicsLayoutItem*)", typeof(void), typeof(IQGraphicsLayoutItem), item);
        }
        [SmokeMethod("removeAt(int)")]
        public override void RemoveAt(int index) {
            interceptor.Invoke("removeAt$", "removeAt(int)", typeof(void), typeof(int), index);
        }
        public void SetSpacing(double spacing) {
            interceptor.Invoke("setSpacing$", "setSpacing(qreal)", typeof(void), typeof(double), spacing);
        }
        public double Spacing() {
            return (double) interceptor.Invoke("spacing", "spacing() const", typeof(double));
        }
        public void SetItemSpacing(int index, double spacing) {
            interceptor.Invoke("setItemSpacing$$", "setItemSpacing(int, qreal)", typeof(void), typeof(int), index, typeof(double), spacing);
        }
        public double ItemSpacing(int index) {
            return (double) interceptor.Invoke("itemSpacing$", "itemSpacing(int) const", typeof(double), typeof(int), index);
        }
        public void SetStretchFactor(IQGraphicsLayoutItem item, int stretch) {
            interceptor.Invoke("setStretchFactor#$", "setStretchFactor(QGraphicsLayoutItem*, int)", typeof(void), typeof(IQGraphicsLayoutItem), item, typeof(int), stretch);
        }
        public int StretchFactor(IQGraphicsLayoutItem item) {
            return (int) interceptor.Invoke("stretchFactor#", "stretchFactor(QGraphicsLayoutItem*) const", typeof(int), typeof(IQGraphicsLayoutItem), item);
        }
        public void SetAlignment(IQGraphicsLayoutItem item, uint alignment) {
            interceptor.Invoke("setAlignment#$", "setAlignment(QGraphicsLayoutItem*, Qt::Alignment)", typeof(void), typeof(IQGraphicsLayoutItem), item, typeof(uint), alignment);
        }
        public uint Alignment(IQGraphicsLayoutItem item) {
            return (uint) interceptor.Invoke("alignment#", "alignment(QGraphicsLayoutItem*) const", typeof(uint), typeof(IQGraphicsLayoutItem), item);
        }
        [SmokeMethod("setGeometry(const QRectF&)")]
        public override void SetGeometry(QRectF rect) {
            interceptor.Invoke("setGeometry#", "setGeometry(const QRectF&)", typeof(void), typeof(QRectF), rect);
        }
        [SmokeMethod("count() const")]
        public override int Count() {
            return (int) interceptor.Invoke("count", "count() const", typeof(int));
        }
        [SmokeMethod("itemAt(int) const")]
        public override IQGraphicsLayoutItem ItemAt(int index) {
            return (IQGraphicsLayoutItem) interceptor.Invoke("itemAt$", "itemAt(int) const", typeof(IQGraphicsLayoutItem), typeof(int), index);
        }
        [SmokeMethod("invalidate()")]
        public override void Invalidate() {
            interceptor.Invoke("invalidate", "invalidate()", typeof(void));
        }
        [SmokeMethod("sizeHint(Qt::SizeHint, const QSizeF&) const")]
        public override QSizeF SizeHint(Qt.SizeHint which, QSizeF constraint) {
            return (QSizeF) interceptor.Invoke("sizeHint$#", "sizeHint(Qt::SizeHint, const QSizeF&) const", typeof(QSizeF), typeof(Qt.SizeHint), which, typeof(QSizeF), constraint);
        }
        [SmokeMethod("sizeHint(Qt::SizeHint) const")]
        public virtual QSizeF SizeHint(Qt.SizeHint which) {
            return (QSizeF) interceptor.Invoke("sizeHint$", "sizeHint(Qt::SizeHint) const", typeof(QSizeF), typeof(Qt.SizeHint), which);
        }
        public void Dump(int indent) {
            interceptor.Invoke("dump$", "dump(int) const", typeof(void), typeof(int), indent);
        }
        public void Dump() {
            interceptor.Invoke("dump", "dump() const", typeof(void));
        }
        ~QGraphicsLinearLayout() {
            interceptor.Invoke("~QGraphicsLinearLayout", "~QGraphicsLinearLayout()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QGraphicsLinearLayout", "~QGraphicsLinearLayout()", typeof(void));
        }
    }
}
