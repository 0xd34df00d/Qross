//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Runtime.InteropServices;
    using System.Text;
    [SmokeClass("QIntValidator")]
    public class QIntValidator : QValidator, IDisposable {
        protected QIntValidator(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QIntValidator), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QIntValidator() {
            staticInterceptor = new SmokeInvocation(typeof(QIntValidator), null);
        }
        [Q_PROPERTY("int", "bottom")]
        public int Bottom {
            get { return (int) interceptor.Invoke("bottom", "bottom()", typeof(int)); }
            set { interceptor.Invoke("setBottom$", "setBottom(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("int", "top")]
        public int Top {
            get { return (int) interceptor.Invoke("top", "top()", typeof(int)); }
            set { interceptor.Invoke("setTop$", "setTop(int)", typeof(void), typeof(int), value); }
        }
        public QIntValidator(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIntValidator#", "QIntValidator(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QIntValidator() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIntValidator", "QIntValidator()", typeof(void));
        }
        public QIntValidator(int bottom, int top, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIntValidator$$#", "QIntValidator(int, int, QObject*)", typeof(void), typeof(int), bottom, typeof(int), top, typeof(QObject), parent);
        }
        [SmokeMethod("validate(QString&, int&) const")]
        public override QValidator.State Validate(StringBuilder arg1, ref int arg2) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(arg1);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(arg1);
#endif
            stack[2].s_int = arg2;
            interceptor.Invoke("validate$$", "validate(QString&, int&) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            arg2 = stack[2].s_int;
            return (QValidator.State) Enum.ToObject(typeof(QValidator.State), stack[0].s_int);
        }
        [SmokeMethod("setRange(int, int)")]
        public virtual void SetRange(int bottom, int top) {
            interceptor.Invoke("setRange$$", "setRange(int, int)", typeof(void), typeof(int), bottom, typeof(int), top);
        }
        ~QIntValidator() {
            interceptor.Invoke("~QIntValidator", "~QIntValidator()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QIntValidator", "~QIntValidator()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQIntValidatorSignals Emit {
            get { return (IQIntValidatorSignals) Q_EMIT; }
        }
    }

    public interface IQIntValidatorSignals : IQValidatorSignals {
    }
}
