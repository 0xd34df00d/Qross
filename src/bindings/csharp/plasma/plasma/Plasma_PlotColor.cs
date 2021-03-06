//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    [SmokeClass("Plasma::PlotColor")]
    public class PlotColor : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected PlotColor(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(PlotColor), this);
        }
        public QColor Color {
            get { return (QColor) interceptor.Invoke("color", "color()", typeof(QColor)); }
            set { interceptor.Invoke("setColor#", "setColor(QColor)", typeof(void), typeof(QColor), value); }
        }
        public QColor DarkColor {
            get { return (QColor) interceptor.Invoke("darkColor", "darkColor()", typeof(QColor)); }
            set { interceptor.Invoke("setDarkColor#", "setDarkColor(QColor)", typeof(void), typeof(QColor), value); }
        }
        public PlotColor() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("PlotColor", "PlotColor()", typeof(void));
        }
        ~PlotColor() {
            interceptor.Invoke("~PlotColor", "~PlotColor()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~PlotColor", "~PlotColor()", typeof(void));
        }
    }
}
