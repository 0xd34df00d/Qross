//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Runtime.InteropServices;
    using System.Text;
    [SmokeClass("QDoubleValidator")]
    public class QDoubleValidator : QValidator, IDisposable {
        protected QDoubleValidator(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QDoubleValidator), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QDoubleValidator() {
            staticInterceptor = new SmokeInvocation(typeof(QDoubleValidator), null);
        }
        public enum Notation {
            StandardNotation = 0,
            ScientificNotation = 1,
        }
        [Q_PROPERTY("double", "bottom")]
        public double Bottom {
            get { return (double) interceptor.Invoke("bottom", "bottom()", typeof(double)); }
            set { interceptor.Invoke("setBottom$", "setBottom(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("double", "top")]
        public double Top {
            get { return (double) interceptor.Invoke("top", "top()", typeof(double)); }
            set { interceptor.Invoke("setTop$", "setTop(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("int", "decimals")]
        public int Decimals {
            get { return (int) interceptor.Invoke("decimals", "decimals()", typeof(int)); }
            set { interceptor.Invoke("setDecimals$", "setDecimals(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("QDoubleValidator::Notation", "notation")]
        public QDoubleValidator.Notation notation {
            get { return (QDoubleValidator.Notation) interceptor.Invoke("notation", "notation()", typeof(QDoubleValidator.Notation)); }
            set { interceptor.Invoke("setNotation$", "setNotation(QDoubleValidator::Notation)", typeof(void), typeof(QDoubleValidator.Notation), value); }
        }
        public QDoubleValidator(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDoubleValidator#", "QDoubleValidator(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QDoubleValidator(double bottom, double top, int decimals, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDoubleValidator$$$#", "QDoubleValidator(double, double, int, QObject*)", typeof(void), typeof(double), bottom, typeof(double), top, typeof(int), decimals, typeof(QObject), parent);
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
        [SmokeMethod("setRange(double, double, int)")]
        public virtual void SetRange(double bottom, double top, int decimals) {
            interceptor.Invoke("setRange$$$", "setRange(double, double, int)", typeof(void), typeof(double), bottom, typeof(double), top, typeof(int), decimals);
        }
        [SmokeMethod("setRange(double, double)")]
        public virtual void SetRange(double bottom, double top) {
            interceptor.Invoke("setRange$$", "setRange(double, double)", typeof(void), typeof(double), bottom, typeof(double), top);
        }
        ~QDoubleValidator() {
            interceptor.Invoke("~QDoubleValidator", "~QDoubleValidator()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QDoubleValidator", "~QDoubleValidator()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQDoubleValidatorSignals Emit {
            get { return (IQDoubleValidatorSignals) Q_EMIT; }
        }
    }

    public interface IQDoubleValidatorSignals : IQValidatorSignals {
    }
}
