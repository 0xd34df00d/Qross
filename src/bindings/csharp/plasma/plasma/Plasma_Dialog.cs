//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    /// <remarks>
    ///  @class Dialog plasma/dialog.h <Plasma/Dialog>
    ///  Dialog provides a dialog-like widget that can be used to display additional
    ///  information.
    ///  Dialog uses the plasma theme, and usually has no window decoration. It's meant
    ///  as an interim solution to display widgets as extension to plasma applets, for
    ///  example when you click on an applet like the devicenotifier or the clock, the
    ///  widget that is then displayed, is a Dialog.
    ///   See <see cref="IDialogSignals"></see> for signals emitted by Dialog
    /// </remarks>        <short> A dialog that uses the Plasma style.</short>
    [SmokeClass("Plasma::Dialog")]
    public class Dialog : QWidget, IDisposable {
        protected Dialog(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(Dialog), this);
        }
        /// <remarks>
        ///  Use these flags to choose the active resize corners.
        ///          </remarks>        <short>    Use these flags to choose the active resize corners.</short>
        public enum ResizeCorner {
            NoCorner = 0,
            NorthEast = 1,
            SouthEast = 2,
            NorthWest = 4,
            SouthWest = 8,
            All = NorthEast|SouthEast|NorthWest|SouthWest,
        }
        /// <remarks>
        ///  @arg parent the parent widget, for plasmoids, this is usually 0.
        ///  @arg f the Qt.WindowFlags, default is to not show a windowborder.
        ///          </remarks>        <short>    @arg parent the parent widget, for plasmoids, this is usually 0.</short>
        public Dialog(QWidget parent, uint f) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("Dialog#$", "Dialog(QWidget*, Qt::WindowFlags)", typeof(void), typeof(QWidget), parent, typeof(uint), f);
        }
        public Dialog(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("Dialog#", "Dialog(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public Dialog() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("Dialog", "Dialog()", typeof(void));
        }
        /// <remarks>
        ///  Sets a QGraphicsWidget to be shown as the content in this dialog.
        ///  The dialog will then set up a QGraphicsView and coordinate geometry with
        ///  the widget automatically.
        ///  @arg widget the QGraphicsWidget to display in this dialog
        ///          </remarks>        <short>    Sets a QGraphicsWidget to be shown as the content in this dialog.</short>
        public void SetGraphicsWidget(QGraphicsWidget widget) {
            interceptor.Invoke("setGraphicsWidget#", "setGraphicsWidget(QGraphicsWidget*)", typeof(void), typeof(QGraphicsWidget), widget);
        }
        /// <remarks>
        /// </remarks>        <return> the graphics widget shown in this dialog
        ///          </return>
        ///         <short>   </short>
        public QGraphicsWidget GraphicsWidget() {
            return (QGraphicsWidget) interceptor.Invoke("graphicsWidget", "graphicsWidget()", typeof(QGraphicsWidget));
        }
        /// <remarks>
        ///  @arg corners the corners the resize handlers should be placed in.
        ///          </remarks>        <short>    @arg corners the corners the resize handlers should be placed in.</short>
        public void SetResizeHandleCorners(uint corners) {
            interceptor.Invoke("setResizeHandleCorners$", "setResizeHandleCorners(Plasma::Dialog::ResizeCorners)", typeof(void), typeof(uint), corners);
        }
        /// <remarks>
        ///  Convenience method to get the enabled resize corners.
        /// </remarks>        <return> which resize corners are active.
        ///          </return>
        ///         <short>    Convenience method to get the enabled resize corners.</short>
        public uint ResizeCorners() {
            return (uint) interceptor.Invoke("resizeCorners", "resizeCorners() const", typeof(uint));
        }
        /// <remarks>
        ///  Causes an animated hide; requires compositing to work, otherwise
        ///  the dialog will simply hide.
        /// </remarks>        <short>    Causes an animated hide; requires compositing to work, otherwise  the dialog will simply hide.</short>
        public void AnimatedHide(Plasma.Direction direction) {
            interceptor.Invoke("animatedHide$", "animatedHide(Plasma::Direction)", typeof(void), typeof(Plasma.Direction), direction);
        }
        /// <remarks>
        ///  Causes an animated show; requires compositing to work, otherwise
        ///  the dialog will simply show.
        /// </remarks>        <short>    Causes an animated show; requires compositing to work, otherwise  the dialog will simply show.</short>
        public void AnimatedShow(Plasma.Direction direction) {
            interceptor.Invoke("animatedShow$", "animatedShow(Plasma::Direction)", typeof(void), typeof(Plasma.Direction), direction);
        }
        /// <remarks>
        /// </remarks>        <return> the preferred aspect ratio mode for placement and resizing
        /// </return>
        ///         <short>   </short>
        public Plasma.AspectRatioMode aspectRatioMode() {
            return (Plasma.AspectRatioMode) interceptor.Invoke("aspectRatioMode", "aspectRatioMode() const", typeof(Plasma.AspectRatioMode));
        }
        /// <remarks>
        ///  Sets the preferred aspect ratio mode for placement and resizing
        /// </remarks>        <short>    Sets the preferred aspect ratio mode for placement and resizing </short>
        public void SetAspectRatioMode(Plasma.AspectRatioMode mode) {
            interceptor.Invoke("setAspectRatioMode$", "setAspectRatioMode(Plasma::AspectRatioMode)", typeof(void), typeof(Plasma.AspectRatioMode), mode);
        }
        /// <remarks>
        ///  Reimplemented from QWidget
        ///          </remarks>        <short>    Reimplemented from QWidget          </short>
        [SmokeMethod("paintEvent(QPaintEvent*)")]
        protected override void PaintEvent(QPaintEvent e) {
            interceptor.Invoke("paintEvent#", "paintEvent(QPaintEvent*)", typeof(void), typeof(QPaintEvent), e);
        }
        [SmokeMethod("event(QEvent*)")]
        protected override bool Event(QEvent arg1) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), arg1);
        }
        [SmokeMethod("resizeEvent(QResizeEvent*)")]
        protected override void ResizeEvent(QResizeEvent e) {
            interceptor.Invoke("resizeEvent#", "resizeEvent(QResizeEvent*)", typeof(void), typeof(QResizeEvent), e);
        }
        [SmokeMethod("eventFilter(QObject*, QEvent*)")]
        protected new virtual bool EventFilter(QObject watched, QEvent arg2) {
            return (bool) interceptor.Invoke("eventFilter##", "eventFilter(QObject*, QEvent*)", typeof(bool), typeof(QObject), watched, typeof(QEvent), arg2);
        }
        [SmokeMethod("hideEvent(QHideEvent*)")]
        protected override void HideEvent(QHideEvent arg1) {
            interceptor.Invoke("hideEvent#", "hideEvent(QHideEvent*)", typeof(void), typeof(QHideEvent), arg1);
        }
        [SmokeMethod("showEvent(QShowEvent*)")]
        protected override void ShowEvent(QShowEvent arg1) {
            interceptor.Invoke("showEvent#", "showEvent(QShowEvent*)", typeof(void), typeof(QShowEvent), arg1);
        }
        [SmokeMethod("focusInEvent(QFocusEvent*)")]
        protected override void FocusInEvent(QFocusEvent arg1) {
            interceptor.Invoke("focusInEvent#", "focusInEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), arg1);
        }
        [SmokeMethod("mouseMoveEvent(QMouseEvent*)")]
        protected override void MouseMoveEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseMoveEvent#", "mouseMoveEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mousePressEvent(QMouseEvent*)")]
        protected override void MousePressEvent(QMouseEvent arg1) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("mouseReleaseEvent(QMouseEvent*)")]
        protected override void MouseReleaseEvent(QMouseEvent arg1) {
            interceptor.Invoke("mouseReleaseEvent#", "mouseReleaseEvent(QMouseEvent*)", typeof(void), typeof(QMouseEvent), arg1);
        }
        [SmokeMethod("keyPressEvent(QKeyEvent*)")]
        protected override void KeyPressEvent(QKeyEvent arg1) {
            interceptor.Invoke("keyPressEvent#", "keyPressEvent(QKeyEvent*)", typeof(void), typeof(QKeyEvent), arg1);
        }
        [SmokeMethod("moveEvent(QMoveEvent*)")]
        protected override void MoveEvent(QMoveEvent arg1) {
            interceptor.Invoke("moveEvent#", "moveEvent(QMoveEvent*)", typeof(void), typeof(QMoveEvent), arg1);
        }
        /// <remarks>
        ///  Convenience method to know whether the point is in a control area (e.g. resize area)
        ///  or not.
        /// </remarks>        <return> true if the point is in the control area.
        ///          </return>
        ///         <short>    Convenience method to know whether the point is in a control area (e.</short>
        protected bool InControlArea(QPoint point) {
            return (bool) interceptor.Invoke("inControlArea#", "inControlArea(const QPoint&)", typeof(bool), typeof(QPoint), point);
        }
        ~Dialog() {
            interceptor.Invoke("~Dialog", "~Dialog()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~Dialog", "~Dialog()", typeof(void));
        }
        protected new IDialogSignals Emit {
            get { return (IDialogSignals) Q_EMIT; }
        }
    }

    public interface IDialogSignals : IQWidgetSignals {
        /// <remarks>
        ///  Fires when the dialog automatically resizes.
        ///          </remarks>        <short>    Fires when the dialog automatically resizes.</short>
        [Q_SIGNAL("void dialogResized()")]
        void DialogResized();
        /// <remarks>
        ///  Emit a signal when the dialog become visible/invisible
        ///          </remarks>        <short>    Emit a signal when the dialog become visible/invisible          </short>
        [Q_SIGNAL("void dialogVisible(bool)")]
        void DialogVisible(bool status);
    }
}
