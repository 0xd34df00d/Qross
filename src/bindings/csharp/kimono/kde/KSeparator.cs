//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  Standard horizontal or vertical separator.
    /// </remarks>        <author> Michael Roth <mroth@wirlweb.de>
    ///  </author>
    ///         <short>    Standard horizontal or vertical separator.</short>
    [SmokeClass("KSeparator")]
    public class KSeparator : QFrame, IDisposable {
        protected KSeparator(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KSeparator), this);
        }
        [Q_PROPERTY("Qt::Orientation", "orientation")]
        public new Qt.Orientation Orientation {
            get { return (Qt.Orientation) interceptor.Invoke("orientation", "orientation()", typeof(Qt.Orientation)); }
            set { interceptor.Invoke("setOrientation$", "setOrientation(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), value); }
        }
        /// <remarks>
        ///  Constructor.
        /// <param> name="parent" parent object.
        /// </param><param> name="f" extra QWidget flags.
        /// </param></remarks>        <short>    Constructor.</short>
        public KSeparator(QWidget parent, uint f) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator#$", "KSeparator(QWidget*, Qt::WindowFlags)", typeof(void), typeof(QWidget), parent, typeof(uint), f);
        }
        public KSeparator(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator#", "KSeparator(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KSeparator() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator", "KSeparator()", typeof(void));
        }
        /// <remarks>
        ///  Constructor.
        /// <param> name="orientation" Set the orientation of the separator.
        ///  Possible values are Horizontal or Vertical.
        /// </param><param> name="parent" parent object.
        /// </param><param> name="f" extra QWidget flags.
        /// </param></remarks>        <short>    Constructor.</short>
        public KSeparator(Qt.Orientation orientation, QWidget parent, uint f) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator$#$", "KSeparator(Qt::Orientation, QWidget*, Qt::WindowFlags)", typeof(void), typeof(Qt.Orientation), orientation, typeof(QWidget), parent, typeof(uint), f);
        }
        public KSeparator(Qt.Orientation orientation, QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator$#", "KSeparator(Qt::Orientation, QWidget*)", typeof(void), typeof(Qt.Orientation), orientation, typeof(QWidget), parent);
        }
        public KSeparator(Qt.Orientation orientation) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KSeparator$", "KSeparator(Qt::Orientation)", typeof(void), typeof(Qt.Orientation), orientation);
        }
        ~KSeparator() {
            interceptor.Invoke("~KSeparator", "~KSeparator()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KSeparator", "~KSeparator()", typeof(void));
        }
        protected new IKSeparatorSignals Emit {
            get { return (IKSeparatorSignals) Q_EMIT; }
        }
    }

    public interface IKSeparatorSignals : IQFrameSignals {
    }
}
