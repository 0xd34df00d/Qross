//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  KDoubleNumInput combines a QSpinBox and optionally a QSlider
    ///  with a label to make an easy to use control for setting some float
    ///  parameter. This is especially nice for configuration dialogs,
    ///  which can have many such combinated controls.
    ///  The slider is created only when the user specifies a range
    ///  for the control using the setRange function with the slider
    ///  parameter set to "true".
    ///  A special feature of KDoubleNumInput, designed specifically for
    ///  the situation when there are several instances in a column,
    ///  is that you can specify what portion of the control is taken by the
    ///  QSpinBox (the remaining portion is used by the slider). This makes
    ///  it very simple to have all the sliders in a column be the same size.
    ///  It uses the KDoubleValidator validator class. KDoubleNumInput
    ///  enforces the value to be in the given range, but see the class
    ///  documentation of KDoubleSpinBox for the tricky
    ///  interrelationship of precision and values. All of what is said
    ///  there applies here, too.
    ///  See <see cref="IKDoubleNumInputSignals"></see> for signals emitted by KDoubleNumInput
    /// </remarks>        <short> An input control for real numbers, consisting of a spinbox and a slider. </short>
    ///         <see> KIntNumInput</see>
    ///         <see> KDoubleSpinBox</see>
    [SmokeClass("KDoubleNumInput")]
    public class KDoubleNumInput : KNumInput, IDisposable {
        protected KDoubleNumInput(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KDoubleNumInput), this);
        }
        [Q_PROPERTY("double", "value")]
        public double Value {
            get { return (double) interceptor.Invoke("value", "value()", typeof(double)); }
            set { interceptor.Invoke("setValue$", "setValue(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("double", "minimum")]
        public double Minimum {
            get { return (double) interceptor.Invoke("minimum", "minimum()", typeof(double)); }
            set { interceptor.Invoke("setMinimum$", "setMinimum(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("double", "maximum")]
        public double Maximum {
            get { return (double) interceptor.Invoke("maximum", "maximum()", typeof(double)); }
            set { interceptor.Invoke("setMaximum$", "setMaximum(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("QString", "suffix")]
        public string Suffix {
            get { return (string) interceptor.Invoke("suffix", "suffix()", typeof(string)); }
            set { interceptor.Invoke("setSuffix$", "setSuffix(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QString", "prefix")]
        public string Prefix {
            get { return (string) interceptor.Invoke("prefix", "prefix()", typeof(string)); }
            set { interceptor.Invoke("setPrefix$", "setPrefix(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QString", "specialValueText")]
        public string SpecialValueText {
            get { return (string) interceptor.Invoke("specialValueText", "specialValueText()", typeof(string)); }
            set { interceptor.Invoke("setSpecialValueText$", "setSpecialValueText(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("int", "decimals")]
        public int Decimals {
            get { return (int) interceptor.Invoke("decimals", "decimals()", typeof(int)); }
            set { interceptor.Invoke("setDecimals$", "setDecimals(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("double", "referencePoint")]
        public double ReferencePoint {
            get { return (double) interceptor.Invoke("referencePoint", "referencePoint()", typeof(double)); }
            set { interceptor.Invoke("setReferencePoint$", "setReferencePoint(double)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("double", "relativeValue")]
        public double RelativeValue {
            get { return (double) interceptor.Invoke("relativeValue", "relativeValue()", typeof(double)); }
            set { interceptor.Invoke("setRelativeValue$", "setRelativeValue(double)", typeof(void), typeof(double), value); }
        }
        /// <remarks>
        ///  Constructs an input control for double values
        ///  with initial value 0.00.
        ///      </remarks>        <short>    Constructs an input control for double values  with initial value 0.</short>
        public KDoubleNumInput(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput#", "KDoubleNumInput(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KDoubleNumInput() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput", "KDoubleNumInput()", typeof(void));
        }
        /// <remarks>
        ///  Constructor
        /// <param> name="lower" lower boundary value
        /// </param><param> name="upper" upper boundary value
        /// </param><param> name="value" initial value for the control
        /// </param><param> name="step" step size to use for up/down arrow clicks
        /// </param><param> name="precision" number of digits after the decimal point
        /// </param><param> name="parent" parent QWidget
        ///      </param></remarks>        <short>    Constructor </short>
        public KDoubleNumInput(double lower, double upper, double value, QWidget parent, double step, int precision) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput$$$#$$", "KDoubleNumInput(double, double, double, QWidget*, double, int)", typeof(void), typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent, typeof(double), step, typeof(int), precision);
        }
        public KDoubleNumInput(double lower, double upper, double value, QWidget parent, double step) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput$$$#$", "KDoubleNumInput(double, double, double, QWidget*, double)", typeof(void), typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent, typeof(double), step);
        }
        public KDoubleNumInput(double lower, double upper, double value, QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput$$$#", "KDoubleNumInput(double, double, double, QWidget*)", typeof(void), typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent);
        }
        public KDoubleNumInput(double lower, double upper, double value) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput$$$", "KDoubleNumInput(double, double, double)", typeof(void), typeof(double), lower, typeof(double), upper, typeof(double), value);
        }
        /// <remarks>
        ///  Constructor
        ///  the difference here is the "below" parameter. It tells this
        ///  instance that it is visually put below some other KNumInput
        ///  widget.  Note that these two KNumInput's need not to have the
        ///  same parent widget or be in the same layout group.  The effect
        ///  is that it'll adjust its layout in correspondence with the
        ///  layout of the other KNumInput's (you can build an arbitrary long
        ///  chain).
        /// <param> name="below" append KDoubleNumInput to the KDoubleNumInput chain
        /// </param><param> name="lower" lower boundary value
        /// </param><param> name="upper" upper boundary value
        /// </param><param> name="value" initial value for the control
        /// </param><param> name="step" step size to use for up/down arrow clicks
        /// </param><param> name="precision" number of digits after the decimal point
        /// </param><param> name="parent" parent QWidget
        /// </param> \deprecated use the version without below instead
        ///      </remarks>        <short>    Constructor </short>
        public KDoubleNumInput(KNumInput below, double lower, double upper, double value, QWidget parent, double step, int precision) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput#$$$#$$", "KDoubleNumInput(KNumInput*, double, double, double, QWidget*, double, int)", typeof(void), typeof(KNumInput), below, typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent, typeof(double), step, typeof(int), precision);
        }
        public KDoubleNumInput(KNumInput below, double lower, double upper, double value, QWidget parent, double step) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput#$$$#$", "KDoubleNumInput(KNumInput*, double, double, double, QWidget*, double)", typeof(void), typeof(KNumInput), below, typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent, typeof(double), step);
        }
        public KDoubleNumInput(KNumInput below, double lower, double upper, double value, QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput#$$$#", "KDoubleNumInput(KNumInput*, double, double, double, QWidget*)", typeof(void), typeof(KNumInput), below, typeof(double), lower, typeof(double), upper, typeof(double), value, typeof(QWidget), parent);
        }
        public KDoubleNumInput(KNumInput below, double lower, double upper, double value) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KDoubleNumInput#$$$", "KDoubleNumInput(KNumInput*, double, double, double)", typeof(void), typeof(KNumInput), below, typeof(double), lower, typeof(double), upper, typeof(double), value);
        }
        /// <remarks>
        /// <param> name="min" minimum value
        /// </param><param> name="max" maximum value
        /// </param><param> name="step" step size for the QSlider
        /// </param><param> name="slider" whether the slider is created or not
        ///      </param></remarks>        <short>   </short>
        public void SetRange(double min, double max, double step, bool slider) {
            interceptor.Invoke("setRange$$$$", "setRange(double, double, double, bool)", typeof(void), typeof(double), min, typeof(double), max, typeof(double), step, typeof(bool), slider);
        }
        public void SetRange(double min, double max, double step) {
            interceptor.Invoke("setRange$$$", "setRange(double, double, double)", typeof(void), typeof(double), min, typeof(double), max, typeof(double), step);
        }
        public void SetRange(double min, double max) {
            interceptor.Invoke("setRange$$", "setRange(double, double)", typeof(void), typeof(double), min, typeof(double), max);
        }
        [SmokeMethod("setLabel(const QString&, Qt::Alignment)")]
        public override void SetLabel(string label, uint a) {
            interceptor.Invoke("setLabel$$", "setLabel(const QString&, Qt::Alignment)", typeof(void), typeof(string), label, typeof(uint), a);
        }
        [SmokeMethod("setLabel(const QString&)")]
        public override void SetLabel(string label) {
            interceptor.Invoke("setLabel$", "setLabel(const QString&)", typeof(void), typeof(string), label);
        }
        [SmokeMethod("minimumSizeHint() const")]
        public override QSize MinimumSizeHint() {
            return (QSize) interceptor.Invoke("minimumSizeHint", "minimumSizeHint() const", typeof(QSize));
        }
        /// <remarks>
        ///  Sets the value of the control.
        ///      </remarks>        <short>    Sets the value of the control.</short>
        [Q_SLOT("void setValue(double)")]
        public void SetValue(double arg1) {
            interceptor.Invoke("setValue$", "setValue(double)", typeof(void), typeof(double), arg1);
        }
        /// <remarks>
        ///  Sets the value in units of referencePoint.
        ///      </remarks>        <short>    Sets the value in units of referencePoint.</short>
        [Q_SLOT("void setRelativeValue(double)")]
        public void SetRelativeValue(double arg1) {
            interceptor.Invoke("setRelativeValue$", "setRelativeValue(double)", typeof(void), typeof(double), arg1);
        }
        /// <remarks>
        ///  Sets the reference Point to <code>ref.</code> It <code>ref</code> == 0, emitting of
        ///  relativeValueChanged is blocked and relativeValue
        ///  just returns 0.
        ///      </remarks>        <short>    Sets the reference Point to <code>ref.</code></short>
        [Q_SLOT("void setReferencePoint(double)")]
        public void SetReferencePoint(double arg1) {
            interceptor.Invoke("setReferencePoint$", "setReferencePoint(double)", typeof(void), typeof(double), arg1);
        }
        /// <remarks>
        ///  Sets the suffix to be displayed to <code>suffix.</code> Use string() to disable
        ///  this feature. Note that the suffix is attached to the value without any
        ///  spacing. So if you prefer to display a space separator, set suffix
        ///  to something like " cm".
        /// </remarks>        <short>    Sets the suffix to be displayed to <code>suffix.</code></short>
        ///         <see> setSuffix</see>
        [Q_SLOT("void setSuffix(QString)")]
        public void SetSuffix(string suffix) {
            interceptor.Invoke("setSuffix$", "setSuffix(const QString&)", typeof(void), typeof(string), suffix);
        }
        /// <remarks>
        ///  Sets the prefix to be displayed to <code>prefix.</code> Use string() to disable
        ///  this feature. Note that the prefix is attached to the value without any
        ///  spacing.
        /// </remarks>        <short>    Sets the prefix to be displayed to <code>prefix.</code></short>
        ///         <see> setPrefix</see>
        [Q_SLOT("void setPrefix(QString)")]
        public void SetPrefix(string prefix) {
            interceptor.Invoke("setPrefix$", "setPrefix(const QString&)", typeof(void), typeof(string), prefix);
        }
        [SmokeMethod("doLayout()")]
        protected override void DoLayout() {
            interceptor.Invoke("doLayout", "doLayout()", typeof(void));
        }
        [SmokeMethod("resizeEvent(QResizeEvent*)")]
        protected override void ResizeEvent(QResizeEvent arg1) {
            interceptor.Invoke("resizeEvent#", "resizeEvent(QResizeEvent*)", typeof(void), typeof(QResizeEvent), arg1);
        }
        ~KDoubleNumInput() {
            interceptor.Invoke("~KDoubleNumInput", "~KDoubleNumInput()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KDoubleNumInput", "~KDoubleNumInput()", typeof(void));
        }
        protected new IKDoubleNumInputSignals Emit {
            get { return (IKDoubleNumInputSignals) Q_EMIT; }
        }
    }

    public interface IKDoubleNumInputSignals : IKNumInputSignals {
        /// <remarks>
        ///  Emitted every time the value changes (by calling setValue() or
        ///  by user interaction).
        ///      </remarks>        <short>    Emitted every time the value changes (by calling setValue() or  by user interaction).</short>
        [Q_SIGNAL("void valueChanged(double)")]
        void ValueChanged(double arg1);
        /// <remarks>
        ///  This is an overloaded member function, provided for
        ///  convenience. It essentially behaves like the above function.
        ///  Contains the value in units of referencePoint.
        ///      </remarks>        <short>    This is an overloaded member function, provided for  convenience.</short>
        [Q_SIGNAL("void relativeValueChanged(double)")]
        void RelativeValueChanged(double arg1);
    }
}
