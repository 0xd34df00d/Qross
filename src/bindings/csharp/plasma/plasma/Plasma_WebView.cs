//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    /// <remarks>
    ///  @class WebView plasma/widgets/webview.h <Plasma/Widgets/WebView>
    ///  See <see cref="IWebViewSignals"></see> for signals emitted by WebView
    /// </remarks>        <short> Provides a widget to display html content in Plasma.  </short>
    [SmokeClass("Plasma::WebView")]
    public class WebView : QGraphicsWidget, IDisposable {
        protected WebView(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(WebView), this);
        }
        [Q_PROPERTY("KUrl", "url")]
        public KUrl Url {
            get { return (KUrl) interceptor.Invoke("url", "url()", typeof(KUrl)); }
            set { interceptor.Invoke("setUrl#", "setUrl(KUrl)", typeof(void), typeof(KUrl), value); }
        }
        [Q_PROPERTY("QString", "html")]
        public string Html {
            get { return (string) interceptor.Invoke("html", "html()", typeof(string)); }
            set { interceptor.Invoke("setHtml$", "setHtml(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("bool", "dragToScroll")]
        public bool DragToScroll {
            get { return (bool) interceptor.Invoke("dragToScroll", "dragToScroll()", typeof(bool)); }
            set { interceptor.Invoke("setDragToScroll$", "setDragToScroll(bool)", typeof(void), typeof(bool), value); }
        }
        [Q_PROPERTY("QPointF", "scrollPosition")]
        public QPointF ScrollPosition {
            get { return (QPointF) interceptor.Invoke("scrollPosition", "scrollPosition()", typeof(QPointF)); }
            set { interceptor.Invoke("setScrollPosition#", "setScrollPosition(QPointF)", typeof(void), typeof(QPointF), value); }
        }
        [Q_PROPERTY("QSizeF", "contentsSize")]
        public QSizeF ContentsSize {
            get { return (QSizeF) interceptor.Invoke("contentsSize", "contentsSize()", typeof(QSizeF)); }
        }
        [Q_PROPERTY("QRectF", "viewportGeometry")]
        public QRectF ViewportGeometry {
            get { return (QRectF) interceptor.Invoke("viewportGeometry", "viewportGeometry()", typeof(QRectF)); }
        }
        [Q_PROPERTY("qreal", "zoomFactor")]
        public double ZoomFactor {
            get { return (double) interceptor.Invoke("zoomFactor", "zoomFactor()", typeof(double)); }
            set { interceptor.Invoke("setZoomFactor$", "setZoomFactor(qreal)", typeof(void), typeof(double), value); }
        }
        public WebView(IQGraphicsItem parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("WebView#", "WebView(QGraphicsItem*)", typeof(void), typeof(IQGraphicsItem), parent);
        }
        public WebView() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("WebView", "WebView()", typeof(void));
        }
        /// <remarks>
        ///  Sets the html to be shown along with a base URL to be used
        ///  to resolve relative references.
        /// <param> name="html" the html (in utf8) to display in the content area
        /// </param><param> name="baseUrl" the base url for relative references
        ///          </param></remarks>        <short>    Sets the html to be shown along with a base URL to be used  to resolve relative references.</short>
        public void SetHtml(QByteArray html, KUrl baseUrl) {
            interceptor.Invoke("setHtml##", "setHtml(const QByteArray&, const KUrl&)", typeof(void), typeof(QByteArray), html, typeof(KUrl), baseUrl);
        }
        public void SetHtml(QByteArray html) {
            interceptor.Invoke("setHtml#", "setHtml(const QByteArray&)", typeof(void), typeof(QByteArray), html);
        }
        /// <remarks>
        ///  Sets the html to be shown along with a base URL to be used
        ///  to resolve relative references.
        /// <param> name="html" the html (in utf8) to display in the content area
        /// </param><param> name="baseUrl" the base url for relative references
        ///          </param></remarks>        <short>    Sets the html to be shown along with a base URL to be used  to resolve relative references.</short>
        public void SetHtml(string html, KUrl baseUrl) {
            interceptor.Invoke("setHtml$#", "setHtml(const QString&, const KUrl&)", typeof(void), typeof(string), html, typeof(KUrl), baseUrl);
        }
        public void SetHtml(string html) {
            interceptor.Invoke("setHtml$", "setHtml(const QString&)", typeof(void), typeof(string), html);
        }
        /// <remarks>
        ///  Reimplementation
        ///          </remarks>        <short>    Reimplementation          </short>
        public new QRectF Geometry() {
            return (QRectF) interceptor.Invoke("geometry", "geometry() const", typeof(QRectF));
        }
        /// <remarks>
        ///  Sets the page to use in this item. The owner of the webpage remains,
        ///  however if this WebView object is the owner of the current page,
        ///  then the current page is deleted
        /// <param> name="page" the page to set in this view
        ///          </param></remarks>        <short>    Sets the page to use in this item.</short>
        public void SetPage(QWebPage page) {
            interceptor.Invoke("setPage#", "setPage(QWebPage*)", typeof(void), typeof(QWebPage), page);
        }
        /// <remarks>
        ///  The QWebPage associated with this item. Useful when more
        ///  of the features of the full QWebPage object need to be accessed.
        ///          </remarks>        <short>    The QWebPage associated with this item.</short>
        public QWebPage Page() {
            return (QWebPage) interceptor.Invoke("page", "page() const", typeof(QWebPage));
        }
        /// <remarks>
        ///  The main web frame associated with this item.
        ///          </remarks>        <short>    The main web frame associated with this item.</short>
        public QWebFrame MainFrame() {
            return (QWebFrame) interceptor.Invoke("mainFrame", "mainFrame() const", typeof(QWebFrame));
        }
        /// <remarks>
        ///  Reimplementation
        ///          </remarks>        <short>    Reimplementation          </short>
        [SmokeMethod("setGeometry(const QRectF&)")]
        public override void SetGeometry(QRectF geometry) {
            interceptor.Invoke("setGeometry#", "setGeometry(const QRectF&)", typeof(void), typeof(QRectF), geometry);
        }
        /// <remarks>
        ///  Reimplementation
        ///          </remarks>        <short>    Reimplementation          </short>
        [SmokeMethod("paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)")]
        protected new virtual void Paint(QPainter painter, QStyleOptionGraphicsItem option, QWidget widget) {
            interceptor.Invoke("paint###", "paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)", typeof(void), typeof(QPainter), painter, typeof(QStyleOptionGraphicsItem), option, typeof(QWidget), widget);
        }
        [SmokeMethod("paint(QPainter*, const QStyleOptionGraphicsItem*)")]
        protected new virtual void Paint(QPainter painter, QStyleOptionGraphicsItem option) {
            interceptor.Invoke("paint##", "paint(QPainter*, const QStyleOptionGraphicsItem*)", typeof(void), typeof(QPainter), painter, typeof(QStyleOptionGraphicsItem), option);
        }
        [SmokeMethod("mouseMoveEvent(QGraphicsSceneMouseEvent*)")]
        protected override void MouseMoveEvent(QGraphicsSceneMouseEvent arg1) {
            interceptor.Invoke("mouseMoveEvent#", "mouseMoveEvent(QGraphicsSceneMouseEvent*)", typeof(void), typeof(QGraphicsSceneMouseEvent), arg1);
        }
        [SmokeMethod("hoverMoveEvent(QGraphicsSceneHoverEvent*)")]
        protected override void HoverMoveEvent(QGraphicsSceneHoverEvent arg1) {
            interceptor.Invoke("hoverMoveEvent#", "hoverMoveEvent(QGraphicsSceneHoverEvent*)", typeof(void), typeof(QGraphicsSceneHoverEvent), arg1);
        }
        [SmokeMethod("mousePressEvent(QGraphicsSceneMouseEvent*)")]
        protected override void MousePressEvent(QGraphicsSceneMouseEvent arg1) {
            interceptor.Invoke("mousePressEvent#", "mousePressEvent(QGraphicsSceneMouseEvent*)", typeof(void), typeof(QGraphicsSceneMouseEvent), arg1);
        }
        [SmokeMethod("mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)")]
        protected override void MouseDoubleClickEvent(QGraphicsSceneMouseEvent arg1) {
            interceptor.Invoke("mouseDoubleClickEvent#", "mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)", typeof(void), typeof(QGraphicsSceneMouseEvent), arg1);
        }
        [SmokeMethod("mouseReleaseEvent(QGraphicsSceneMouseEvent*)")]
        protected override void MouseReleaseEvent(QGraphicsSceneMouseEvent arg1) {
            interceptor.Invoke("mouseReleaseEvent#", "mouseReleaseEvent(QGraphicsSceneMouseEvent*)", typeof(void), typeof(QGraphicsSceneMouseEvent), arg1);
        }
        [SmokeMethod("contextMenuEvent(QGraphicsSceneContextMenuEvent*)")]
        protected override void ContextMenuEvent(QGraphicsSceneContextMenuEvent arg1) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QGraphicsSceneContextMenuEvent*)", typeof(void), typeof(QGraphicsSceneContextMenuEvent), arg1);
        }
        [SmokeMethod("wheelEvent(QGraphicsSceneWheelEvent*)")]
        protected override void WheelEvent(QGraphicsSceneWheelEvent arg1) {
            interceptor.Invoke("wheelEvent#", "wheelEvent(QGraphicsSceneWheelEvent*)", typeof(void), typeof(QGraphicsSceneWheelEvent), arg1);
        }
        [SmokeMethod("keyPressEvent(QKeyEvent*)")]
        protected override void KeyPressEvent(QKeyEvent arg1) {
            interceptor.Invoke("keyPressEvent#", "keyPressEvent(QKeyEvent*)", typeof(void), typeof(QKeyEvent), arg1);
        }
        [SmokeMethod("keyReleaseEvent(QKeyEvent*)")]
        protected override void KeyReleaseEvent(QKeyEvent arg1) {
            interceptor.Invoke("keyReleaseEvent#", "keyReleaseEvent(QKeyEvent*)", typeof(void), typeof(QKeyEvent), arg1);
        }
        [SmokeMethod("focusInEvent(QFocusEvent*)")]
        protected override void FocusInEvent(QFocusEvent arg1) {
            interceptor.Invoke("focusInEvent#", "focusInEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), arg1);
        }
        [SmokeMethod("focusOutEvent(QFocusEvent*)")]
        protected override void FocusOutEvent(QFocusEvent arg1) {
            interceptor.Invoke("focusOutEvent#", "focusOutEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), arg1);
        }
        [SmokeMethod("dragEnterEvent(QGraphicsSceneDragDropEvent*)")]
        protected override void DragEnterEvent(QGraphicsSceneDragDropEvent arg1) {
            interceptor.Invoke("dragEnterEvent#", "dragEnterEvent(QGraphicsSceneDragDropEvent*)", typeof(void), typeof(QGraphicsSceneDragDropEvent), arg1);
        }
        [SmokeMethod("dragLeaveEvent(QGraphicsSceneDragDropEvent*)")]
        protected override void DragLeaveEvent(QGraphicsSceneDragDropEvent arg1) {
            interceptor.Invoke("dragLeaveEvent#", "dragLeaveEvent(QGraphicsSceneDragDropEvent*)", typeof(void), typeof(QGraphicsSceneDragDropEvent), arg1);
        }
        [SmokeMethod("dragMoveEvent(QGraphicsSceneDragDropEvent*)")]
        protected override void DragMoveEvent(QGraphicsSceneDragDropEvent arg1) {
            interceptor.Invoke("dragMoveEvent#", "dragMoveEvent(QGraphicsSceneDragDropEvent*)", typeof(void), typeof(QGraphicsSceneDragDropEvent), arg1);
        }
        [SmokeMethod("dropEvent(QGraphicsSceneDragDropEvent*)")]
        protected override void DropEvent(QGraphicsSceneDragDropEvent arg1) {
            interceptor.Invoke("dropEvent#", "dropEvent(QGraphicsSceneDragDropEvent*)", typeof(void), typeof(QGraphicsSceneDragDropEvent), arg1);
        }
        [SmokeMethod("sizeHint(Qt::SizeHint, const QSizeF&) const")]
        public override QSizeF SizeHint(Qt.SizeHint which, QSizeF constraint) {
            return (QSizeF) interceptor.Invoke("sizeHint$#", "sizeHint(Qt::SizeHint, const QSizeF&) const", typeof(QSizeF), typeof(Qt.SizeHint), which, typeof(QSizeF), constraint);
        }
        ~WebView() {
            interceptor.Invoke("~WebView", "~WebView()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~WebView", "~WebView()", typeof(void));
        }
        protected new IWebViewSignals Emit {
            get { return (IWebViewSignals) Q_EMIT; }
        }
    }

    public interface IWebViewSignals : IQGraphicsWidgetSignals {
        /// <remarks>
        ///  During loading progress, this signal is emitted. The values
        ///  are always between 0 and 100, inclusive.
        /// <param> name="percent" the estimated amount the loading is complete
        ///          </param></remarks>        <short>    During loading progress, this signal is emitted.</short>
        [Q_SIGNAL("void loadProgress(int)")]
        void LoadProgress(int percent);
        /// <remarks>
        ///  This signal is emitted when loading is completed.
        /// <param> name="success" true if the content was loaded successfully,
        ///                 otherwise false
        ///          </param></remarks>        <short>    This signal is emitted when loading is completed.</short>
        [Q_SIGNAL("void loadFinished(bool)")]
        void LoadFinished(bool success);
    }
}
