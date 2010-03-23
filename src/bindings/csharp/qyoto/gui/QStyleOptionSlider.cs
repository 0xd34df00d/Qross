//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QStyleOptionSlider")]
    public class QStyleOptionSlider : QStyleOptionComplex, IDisposable {
        protected QStyleOptionSlider(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QStyleOptionSlider), this);
        }
        public enum StyleOptionType {
            Type = QStyleOption.OptionType.SO_Slider,
        }
        public enum StyleOptionVersion {
            Version = 1,
        }
        public Qt.Orientation Orientation {
            get { return (Qt.Orientation) interceptor.Invoke("orientation", "orientation()", typeof(Qt.Orientation)); }
            set { interceptor.Invoke("setOrientation$", "setOrientation(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), value); }
        }
        public int Minimum {
            get { return (int) interceptor.Invoke("minimum", "minimum()", typeof(int)); }
            set { interceptor.Invoke("setMinimum$", "setMinimum(int)", typeof(void), typeof(int), value); }
        }
        public int Maximum {
            get { return (int) interceptor.Invoke("maximum", "maximum()", typeof(int)); }
            set { interceptor.Invoke("setMaximum$", "setMaximum(int)", typeof(void), typeof(int), value); }
        }
        public QSlider.TickPosition TickPosition {
            get { return (QSlider.TickPosition) interceptor.Invoke("tickPosition", "tickPosition()", typeof(QSlider.TickPosition)); }
            set { interceptor.Invoke("setTickPosition$", "setTickPosition(QSlider::TickPosition)", typeof(void), typeof(QSlider.TickPosition), value); }
        }
        public int TickInterval {
            get { return (int) interceptor.Invoke("tickInterval", "tickInterval()", typeof(int)); }
            set { interceptor.Invoke("setTickInterval$", "setTickInterval(int)", typeof(void), typeof(int), value); }
        }
        public bool UpsideDown {
            get { return (bool) interceptor.Invoke("upsideDown", "upsideDown()", typeof(bool)); }
            set { interceptor.Invoke("setUpsideDown$", "setUpsideDown(bool)", typeof(void), typeof(bool), value); }
        }
        public int SliderPosition {
            get { return (int) interceptor.Invoke("sliderPosition", "sliderPosition()", typeof(int)); }
            set { interceptor.Invoke("setSliderPosition$", "setSliderPosition(int)", typeof(void), typeof(int), value); }
        }
        public int SliderValue {
            get { return (int) interceptor.Invoke("sliderValue", "sliderValue()", typeof(int)); }
            set { interceptor.Invoke("setSliderValue$", "setSliderValue(int)", typeof(void), typeof(int), value); }
        }
        public int SingleStep {
            get { return (int) interceptor.Invoke("singleStep", "singleStep()", typeof(int)); }
            set { interceptor.Invoke("setSingleStep$", "setSingleStep(int)", typeof(void), typeof(int), value); }
        }
        public int PageStep {
            get { return (int) interceptor.Invoke("pageStep", "pageStep()", typeof(int)); }
            set { interceptor.Invoke("setPageStep$", "setPageStep(int)", typeof(void), typeof(int), value); }
        }
        public double NotchTarget {
            get { return (double) interceptor.Invoke("notchTarget", "notchTarget()", typeof(double)); }
            set { interceptor.Invoke("setNotchTarget$", "setNotchTarget(qreal)", typeof(void), typeof(double), value); }
        }
        public bool DialWrapping {
            get { return (bool) interceptor.Invoke("dialWrapping", "dialWrapping()", typeof(bool)); }
            set { interceptor.Invoke("setDialWrapping$", "setDialWrapping(bool)", typeof(void), typeof(bool), value); }
        }
        public QStyleOptionSlider() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionSlider", "QStyleOptionSlider()", typeof(void));
        }
        public QStyleOptionSlider(QStyleOptionSlider other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionSlider#", "QStyleOptionSlider(const QStyleOptionSlider&)", typeof(void), typeof(QStyleOptionSlider), other);
        }
        public QStyleOptionSlider(int version) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionSlider$", "QStyleOptionSlider(int)", typeof(void), typeof(int), version);
        }
        ~QStyleOptionSlider() {
            interceptor.Invoke("~QStyleOptionSlider", "~QStyleOptionSlider()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QStyleOptionSlider", "~QStyleOptionSlider()", typeof(void));
        }
    }
}
