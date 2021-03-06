//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QStyleOptionGroupBox")]
    public class QStyleOptionGroupBox : QStyleOptionComplex, IDisposable {
        protected QStyleOptionGroupBox(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QStyleOptionGroupBox), this);
        }
        public enum StyleOptionType {
            Type = QStyleOption.OptionType.SO_GroupBox,
        }
        public enum StyleOptionVersion {
            Version = 1,
        }
        public uint Features {
            get { return (uint) interceptor.Invoke("features", "features()", typeof(uint)); }
            set { interceptor.Invoke("setFeatures$", "setFeatures(QStyleOptionFrameV2::FrameFeatures)", typeof(void), typeof(uint), value); }
        }
        public string Text {
            get { return (string) interceptor.Invoke("text", "text()", typeof(string)); }
            set { interceptor.Invoke("setText$", "setText(QString)", typeof(void), typeof(string), value); }
        }
        public uint TextAlignment {
            get { return (uint) interceptor.Invoke("textAlignment", "textAlignment()", typeof(uint)); }
            set { interceptor.Invoke("setTextAlignment$", "setTextAlignment(Qt::Alignment)", typeof(void), typeof(uint), value); }
        }
        public QColor TextColor {
            get { return (QColor) interceptor.Invoke("textColor", "textColor()", typeof(QColor)); }
            set { interceptor.Invoke("setTextColor#", "setTextColor(QColor)", typeof(void), typeof(QColor), value); }
        }
        public int LineWidth {
            get { return (int) interceptor.Invoke("lineWidth", "lineWidth()", typeof(int)); }
            set { interceptor.Invoke("setLineWidth$", "setLineWidth(int)", typeof(void), typeof(int), value); }
        }
        public int MidLineWidth {
            get { return (int) interceptor.Invoke("midLineWidth", "midLineWidth()", typeof(int)); }
            set { interceptor.Invoke("setMidLineWidth$", "setMidLineWidth(int)", typeof(void), typeof(int), value); }
        }
        public QStyleOptionGroupBox() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionGroupBox", "QStyleOptionGroupBox()", typeof(void));
        }
        public QStyleOptionGroupBox(QStyleOptionGroupBox other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionGroupBox#", "QStyleOptionGroupBox(const QStyleOptionGroupBox&)", typeof(void), typeof(QStyleOptionGroupBox), other);
        }
        public QStyleOptionGroupBox(int version) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionGroupBox$", "QStyleOptionGroupBox(int)", typeof(void), typeof(int), version);
        }
        ~QStyleOptionGroupBox() {
            interceptor.Invoke("~QStyleOptionGroupBox", "~QStyleOptionGroupBox()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QStyleOptionGroupBox", "~QStyleOptionGroupBox()", typeof(void));
        }
    }
}
