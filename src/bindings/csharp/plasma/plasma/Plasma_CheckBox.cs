//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    /// <remarks>
    ///  @class CheckBox plasma/widgets/checkbox.h <Plasma/Widgets/CheckBox>
    ///  See <see cref="ICheckBoxSignals"></see> for signals emitted by CheckBox
    /// </remarks>        <short> Provides a Plasma-themed checkbox.  </short>
    [SmokeClass("Plasma::CheckBox")]
    public class CheckBox : QGraphicsProxyWidget, IDisposable {
        protected CheckBox(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(CheckBox), this);
        }
        [Q_PROPERTY("QGraphicsWidget*", "parentWidget")]
        public QGraphicsWidget ParentWidget {
            get { return (QGraphicsWidget) interceptor.Invoke("parentWidget", "parentWidget()", typeof(QGraphicsWidget)); }
        }
        [Q_PROPERTY("QString", "text")]
        public string Text {
            get { return (string) interceptor.Invoke("text", "text()", typeof(string)); }
            set { interceptor.Invoke("setText$", "setText(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QString", "image")]
        public string Image {
            get { return (string) interceptor.Invoke("image", "image()", typeof(string)); }
            set { interceptor.Invoke("setImage$", "setImage(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QString", "styleSheet")]
        public string StyleSheet {
            get { return (string) interceptor.Invoke("styleSheet", "styleSheet()", typeof(string)); }
            set { interceptor.Invoke("setStyleSheet$", "setStyleSheet(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QCheckBox*", "nativeWidget")]
        public QCheckBox NativeWidget {
            get { return (QCheckBox) interceptor.Invoke("nativeWidget", "nativeWidget()", typeof(QCheckBox)); }
        }
        [Q_PROPERTY("bool", "isChecked")]
        public bool IsChecked {
            get { return (bool) interceptor.Invoke("isChecked", "isChecked()", typeof(bool)); }
            set { interceptor.Invoke("setChecked$", "setChecked(bool)", typeof(void), typeof(bool), value); }
        }
        public CheckBox(QGraphicsWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CheckBox#", "CheckBox(QGraphicsWidget*)", typeof(void), typeof(QGraphicsWidget), parent);
        }
        public CheckBox() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CheckBox", "CheckBox()", typeof(void));
        }
        [SmokeMethod("resizeEvent(QGraphicsSceneResizeEvent*)")]
        protected override void ResizeEvent(QGraphicsSceneResizeEvent arg1) {
            interceptor.Invoke("resizeEvent#", "resizeEvent(QGraphicsSceneResizeEvent*)", typeof(void), typeof(QGraphicsSceneResizeEvent), arg1);
        }
        [SmokeMethod("changeEvent(QEvent*)")]
        protected override void ChangeEvent(QEvent arg1) {
            interceptor.Invoke("changeEvent#", "changeEvent(QEvent*)", typeof(void), typeof(QEvent), arg1);
        }
        ~CheckBox() {
            interceptor.Invoke("~CheckBox", "~CheckBox()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~CheckBox", "~CheckBox()", typeof(void));
        }
        protected new ICheckBoxSignals Emit {
            get { return (ICheckBoxSignals) Q_EMIT; }
        }
    }

    public interface ICheckBoxSignals : IQGraphicsProxyWidgetSignals {
        [Q_SIGNAL("void toggled(bool)")]
        void Toggled(bool arg1);
    }
}
