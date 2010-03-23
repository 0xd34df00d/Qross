//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    /// <remarks> See <see cref="IQStackedWidgetSignals"></see> for signals emitted by QStackedWidget
    /// </remarks>
    [SmokeClass("QStackedWidget")]
    public class QStackedWidget : QFrame, IDisposable {
        protected QStackedWidget(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QStackedWidget), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QStackedWidget() {
            staticInterceptor = new SmokeInvocation(typeof(QStackedWidget), null);
        }
        [Q_PROPERTY("int", "currentIndex")]
        public int CurrentIndex {
            get { return (int) interceptor.Invoke("currentIndex", "currentIndex()", typeof(int)); }
            set { interceptor.Invoke("setCurrentIndex$", "setCurrentIndex(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("int", "count")]
        public int Count {
            get { return (int) interceptor.Invoke("count", "count()", typeof(int)); }
        }
        public QStackedWidget(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStackedWidget#", "QStackedWidget(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public QStackedWidget() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStackedWidget", "QStackedWidget()", typeof(void));
        }
        public int AddWidget(QWidget w) {
            return (int) interceptor.Invoke("addWidget#", "addWidget(QWidget*)", typeof(int), typeof(QWidget), w);
        }
        public int InsertWidget(int index, QWidget w) {
            return (int) interceptor.Invoke("insertWidget$#", "insertWidget(int, QWidget*)", typeof(int), typeof(int), index, typeof(QWidget), w);
        }
        public void RemoveWidget(QWidget w) {
            interceptor.Invoke("removeWidget#", "removeWidget(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        public QWidget CurrentWidget() {
            return (QWidget) interceptor.Invoke("currentWidget", "currentWidget() const", typeof(QWidget));
        }
        public int IndexOf(QWidget arg1) {
            return (int) interceptor.Invoke("indexOf#", "indexOf(QWidget*) const", typeof(int), typeof(QWidget), arg1);
        }
        public QWidget Widget(int arg1) {
            return (QWidget) interceptor.Invoke("widget$", "widget(int) const", typeof(QWidget), typeof(int), arg1);
        }
        [Q_SLOT("void setCurrentIndex(int)")]
        public void SetCurrentIndex(int index) {
            interceptor.Invoke("setCurrentIndex$", "setCurrentIndex(int)", typeof(void), typeof(int), index);
        }
        [Q_SLOT("void setCurrentWidget(QWidget*)")]
        public void SetCurrentWidget(QWidget w) {
            interceptor.Invoke("setCurrentWidget#", "setCurrentWidget(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        [SmokeMethod("event(QEvent*)")]
        protected override bool Event(QEvent e) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), e);
        }
        ~QStackedWidget() {
            interceptor.Invoke("~QStackedWidget", "~QStackedWidget()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QStackedWidget", "~QStackedWidget()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQStackedWidgetSignals Emit {
            get { return (IQStackedWidgetSignals) Q_EMIT; }
        }
    }

    public interface IQStackedWidgetSignals : IQFrameSignals {
        [Q_SIGNAL("void currentChanged(int)")]
        void CurrentChanged(int arg1);
        [Q_SIGNAL("void widgetRemoved(int)")]
        void WidgetRemoved(int index);
    }
}
