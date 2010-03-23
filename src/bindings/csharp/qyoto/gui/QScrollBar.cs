//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QScrollBar")]
    public class QScrollBar : QAbstractSlider, IDisposable {
        protected QScrollBar(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QScrollBar), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QScrollBar() {
            staticInterceptor = new SmokeInvocation(typeof(QScrollBar), null);
        }
        public QScrollBar(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QScrollBar#", "QScrollBar(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public QScrollBar() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QScrollBar", "QScrollBar()", typeof(void));
        }
        public QScrollBar(Qt.Orientation arg1, QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QScrollBar$#", "QScrollBar(Qt::Orientation, QWidget*)", typeof(void), typeof(Qt.Orientation), arg1, typeof(QWidget), parent);
        }
        public QScrollBar(Qt.Orientation arg1) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QScrollBar$", "QScrollBar(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), arg1);
        }
        [SmokeMethod("sizeHint() const")]
        public override QSize SizeHint() {
            return (QSize) interceptor.Invoke("sizeHint", "sizeHint() const", typeof(QSize));
        }
        [SmokeMethod("event(QEvent*)")]
        public new virtual bool Event(QEvent arg1) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), arg1);
        }
        [SmokeMethod("paintEvent(QPaintEvent*)")]
        protected override void PaintEvent(QPaintEvent arg1) {
            interceptor.Invoke("paintEvent#", "paintEvent(QPaintEvent*)", typeof(void), typeof(QPaintEvent), arg1);
        }
        [SmokeMethod("mousePressEvent(QMouseEvent*)")]
        protected override void MousePressEvent(QMouseEvent arg1) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mouseReleaseEvent(QMouseEvent*)")]
        protected override void MouseReleaseEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseReleaseEvent#", "mouseReleaseEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mouseMoveEvent(QMouseEvent*)")]
        protected override void MouseMoveEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseMoveEvent#", "mouseMoveEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("hideEvent(QHideEvent*)")]
        protected override void HideEvent(QHideEvent arg1) {
            interceptor.Invoke("hideEvent#", "hideEvent(QHideEvent*)", typeof(void), typeof(QHideEvent), arg1);
        }
        [SmokeMethod("sliderChange(QAbstractSlider::SliderChange)")]
        protected override void sliderChange(QAbstractSlider.SliderChange change) {
            interceptor.Invoke("sliderChange$", "sliderChange(QAbstractSlider::SliderChange)", typeof(void), typeof(QAbstractSlider.SliderChange), change);
        }
        [SmokeMethod("contextMenuEvent(QContextMenuEvent*)")]
        protected override void ContextMenuEvent(QContextMenuEvent arg1) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QContextMenuEvent*)", typeof(void), typeof(QContextMenuEvent), arg1);
        }
        protected void InitStyleOption(QStyleOptionSlider option) {
            interceptor.Invoke("initStyleOption#", "initStyleOption(QStyleOptionSlider*) const", typeof(void), typeof(QStyleOptionSlider), option);
        }
        ~QScrollBar() {
            interceptor.Invoke("~QScrollBar", "~QScrollBar()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QScrollBar", "~QScrollBar()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQScrollBarSignals Emit {
            get { return (IQScrollBarSignals) Q_EMIT; }
        }
    }

    public interface IQScrollBarSignals : IQAbstractSliderSignals {
    }
}
