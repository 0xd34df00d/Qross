//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QEventLoop")]
    public class QEventLoop : QObject, IDisposable {
        protected QEventLoop(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QEventLoop), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QEventLoop() {
            staticInterceptor = new SmokeInvocation(typeof(QEventLoop), null);
        }
        public enum ProcessEventsFlag {
            AllEvents = 0x00,
            ExcludeUserInputEvents = 0x01,
            ExcludeSocketNotifiers = 0x02,
            WaitForMoreEvents = 0x04,
            X11ExcludeTimers = 0x08,
            DeferredDeletion = 0x10,
            EventLoopExec = 0x20,
            DialogExec = 0x40,
        }
        public QEventLoop(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QEventLoop#", "QEventLoop(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QEventLoop() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QEventLoop", "QEventLoop()", typeof(void));
        }
        public bool ProcessEvents(uint flags) {
            return (bool) interceptor.Invoke("processEvents$", "processEvents(QEventLoop::ProcessEventsFlags)", typeof(bool), typeof(uint), flags);
        }
        public bool ProcessEvents() {
            return (bool) interceptor.Invoke("processEvents", "processEvents()", typeof(bool));
        }
        public void ProcessEvents(uint flags, int maximumTime) {
            interceptor.Invoke("processEvents$$", "processEvents(QEventLoop::ProcessEventsFlags, int)", typeof(void), typeof(uint), flags, typeof(int), maximumTime);
        }
        public int Exec(uint flags) {
            return (int) interceptor.Invoke("exec$", "exec(QEventLoop::ProcessEventsFlags)", typeof(int), typeof(uint), flags);
        }
        public int Exec() {
            return (int) interceptor.Invoke("exec", "exec()", typeof(int));
        }
        public void Exit(int returnCode) {
            interceptor.Invoke("exit$", "exit(int)", typeof(void), typeof(int), returnCode);
        }
        public void Exit() {
            interceptor.Invoke("exit", "exit()", typeof(void));
        }
        public bool IsRunning() {
            return (bool) interceptor.Invoke("isRunning", "isRunning() const", typeof(bool));
        }
        public void WakeUp() {
            interceptor.Invoke("wakeUp", "wakeUp()", typeof(void));
        }
        [Q_SLOT("void quit()")]
        public void Quit() {
            interceptor.Invoke("quit", "quit()", typeof(void));
        }
        ~QEventLoop() {
            interceptor.Invoke("~QEventLoop", "~QEventLoop()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QEventLoop", "~QEventLoop()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQEventLoopSignals Emit {
            get { return (IQEventLoopSignals) Q_EMIT; }
        }
    }

    public interface IQEventLoopSignals : IQObjectSignals {
    }
}
