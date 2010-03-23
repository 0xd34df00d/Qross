//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QToolTip")]
    public class QToolTip : Object {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QToolTip(Type dummy) {}
        private static SmokeInvocation staticInterceptor = null;
        static QToolTip() {
            staticInterceptor = new SmokeInvocation(typeof(QToolTip), null);
        }
        public static void ShowText(QPoint pos, string text, QWidget w) {
            staticInterceptor.Invoke("showText#$#", "showText(const QPoint&, const QString&, QWidget*)", typeof(void), typeof(QPoint), pos, typeof(string), text, typeof(QWidget), w);
        }
        public static void ShowText(QPoint pos, string text) {
            staticInterceptor.Invoke("showText#$", "showText(const QPoint&, const QString&)", typeof(void), typeof(QPoint), pos, typeof(string), text);
        }
        public static void ShowText(QPoint pos, string text, QWidget w, QRect rect) {
            staticInterceptor.Invoke("showText#$##", "showText(const QPoint&, const QString&, QWidget*, const QRect&)", typeof(void), typeof(QPoint), pos, typeof(string), text, typeof(QWidget), w, typeof(QRect), rect);
        }
        public static void HideText() {
            staticInterceptor.Invoke("hideText", "hideText()", typeof(void));
        }
        public static bool IsVisible() {
            return (bool) staticInterceptor.Invoke("isVisible", "isVisible()", typeof(bool));
        }
        public static string Text() {
            return (string) staticInterceptor.Invoke("text", "text()", typeof(string));
        }
        public static QPalette Palette() {
            return (QPalette) staticInterceptor.Invoke("palette", "palette()", typeof(QPalette));
        }
        public static void SetPalette(QPalette arg1) {
            staticInterceptor.Invoke("setPalette#", "setPalette(const QPalette&)", typeof(void), typeof(QPalette), arg1);
        }
        public static QFont Font() {
            return (QFont) staticInterceptor.Invoke("font", "font()", typeof(QFont));
        }
        public static void SetFont(QFont arg1) {
            staticInterceptor.Invoke("setFont#", "setFont(const QFont&)", typeof(void), typeof(QFont), arg1);
        }
    }
}
