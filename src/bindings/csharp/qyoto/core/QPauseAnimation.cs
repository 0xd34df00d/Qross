//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QPauseAnimation")]
    public class QPauseAnimation : QAbstractAnimation, IDisposable {
        protected QPauseAnimation(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QPauseAnimation), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QPauseAnimation() {
            staticInterceptor = new SmokeInvocation(typeof(QPauseAnimation), null);
        }
        [Q_PROPERTY("int", "duration")]
        public new int Duration {
            get { return (int) interceptor.Invoke("duration", "duration()", typeof(int)); }
            set { interceptor.Invoke("setDuration$", "setDuration(int)", typeof(void), typeof(int), value); }
        }
        public QPauseAnimation(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QPauseAnimation#", "QPauseAnimation(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QPauseAnimation() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QPauseAnimation", "QPauseAnimation()", typeof(void));
        }
        public QPauseAnimation(int msecs, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QPauseAnimation$#", "QPauseAnimation(int, QObject*)", typeof(void), typeof(int), msecs, typeof(QObject), parent);
        }
        public QPauseAnimation(int msecs) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QPauseAnimation$", "QPauseAnimation(int)", typeof(void), typeof(int), msecs);
        }
        [SmokeMethod("event(QEvent*)")]
        protected override bool Event(QEvent e) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), e);
        }
        [SmokeMethod("updateCurrentTime(int)")]
        protected override void UpdateCurrentTime(int arg1) {
            interceptor.Invoke("updateCurrentTime$", "updateCurrentTime(int)", typeof(void), typeof(int), arg1);
        }
        // WARNING: Unimplemented C++ pure virtual - DO NOT CALL
        [SmokeMethod("duration() const")]
        public override int duration() {
            return (int) interceptor.Invoke("duration", "duration() const", typeof(int));
        }
        ~QPauseAnimation() {
            interceptor.Invoke("~QPauseAnimation", "~QPauseAnimation()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QPauseAnimation", "~QPauseAnimation()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQPauseAnimationSignals Emit {
            get { return (IQPauseAnimationSignals) Q_EMIT; }
        }
    }

    public interface IQPauseAnimationSignals : IQAbstractAnimationSignals {
    }
}
