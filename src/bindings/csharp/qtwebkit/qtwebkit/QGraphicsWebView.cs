//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    /// <remarks> See <see cref="IQGraphicsWebViewSignals"></see> for signals emitted by QGraphicsWebView
    /// </remarks>
    [SmokeClass("QGraphicsWebView")]
    public class QGraphicsWebView : QGraphicsWidget, IDisposable {
        protected QGraphicsWebView(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QGraphicsWebView), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QGraphicsWebView() {
            staticInterceptor = new SmokeInvocation(typeof(QGraphicsWebView), null);
        }
        [Q_PROPERTY("QString", "title")]
        public string Title {
            get { return (string) interceptor.Invoke("title", "title()", typeof(string)); }
            set { interceptor.Invoke("titleChanged$", "titleChanged(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QIcon", "icon")]
        public QIcon icon {
            get { return (QIcon) interceptor.Invoke("icon", "icon()", typeof(QIcon)); }
            set { interceptor.Invoke("iconChanged#", "iconChanged(QIcon)", typeof(void), typeof(QIcon), value); }
        }
        [Q_PROPERTY("qreal", "zoomFactor")]
        public double ZoomFactor {
            get { return (double) interceptor.Invoke("zoomFactor", "zoomFactor()", typeof(double)); }
            set { interceptor.Invoke("setZoomFactor$", "setZoomFactor(qreal)", typeof(void), typeof(double), value); }
        }
        [Q_PROPERTY("QUrl", "url")]
        public QUrl Url {
            get { return (QUrl) interceptor.Invoke("url", "url()", typeof(QUrl)); }
            set { interceptor.Invoke("setUrl#", "setUrl(QUrl)", typeof(void), typeof(QUrl), value); }
        }
        [Q_PROPERTY("bool", "modified")]
        public bool Modified {
            get { return (bool) interceptor.Invoke("isModified", "isModified()", typeof(bool)); }
        }
        public QGraphicsWebView(IQGraphicsItem parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsWebView#", "QGraphicsWebView(QGraphicsItem*)", typeof(void), typeof(IQGraphicsItem), parent);
        }
        public QGraphicsWebView() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QGraphicsWebView", "QGraphicsWebView()", typeof(void));
        }
        public QWebPage Page() {
            return (QWebPage) interceptor.Invoke("page", "page() const", typeof(QWebPage));
        }
        public void SetPage(QWebPage arg1) {
            interceptor.Invoke("setPage#", "setPage(QWebPage*)", typeof(void), typeof(QWebPage), arg1);
        }
        public void Load(QUrl url) {
            interceptor.Invoke("load#", "load(const QUrl&)", typeof(void), typeof(QUrl), url);
        }
        public void Load(QNetworkRequest request, QNetworkAccessManager.Operation operation, QByteArray body) {
            interceptor.Invoke("load#$#", "load(const QNetworkRequest&, QNetworkAccessManager::Operation, const QByteArray&)", typeof(void), typeof(QNetworkRequest), request, typeof(QNetworkAccessManager.Operation), operation, typeof(QByteArray), body);
        }
        public void Load(QNetworkRequest request, QNetworkAccessManager.Operation operation) {
            interceptor.Invoke("load#$", "load(const QNetworkRequest&, QNetworkAccessManager::Operation)", typeof(void), typeof(QNetworkRequest), request, typeof(QNetworkAccessManager.Operation), operation);
        }
        public void Load(QNetworkRequest request) {
            interceptor.Invoke("load#", "load(const QNetworkRequest&)", typeof(void), typeof(QNetworkRequest), request);
        }
        public void SetHtml(string html, QUrl baseUrl) {
            interceptor.Invoke("setHtml$#", "setHtml(const QString&, const QUrl&)", typeof(void), typeof(string), html, typeof(QUrl), baseUrl);
        }
        public void SetHtml(string html) {
            interceptor.Invoke("setHtml$", "setHtml(const QString&)", typeof(void), typeof(string), html);
        }
        public void SetContent(QByteArray data, string mimeType, QUrl baseUrl) {
            interceptor.Invoke("setContent#$#", "setContent(const QByteArray&, const QString&, const QUrl&)", typeof(void), typeof(QByteArray), data, typeof(string), mimeType, typeof(QUrl), baseUrl);
        }
        public void SetContent(QByteArray data, string mimeType) {
            interceptor.Invoke("setContent#$", "setContent(const QByteArray&, const QString&)", typeof(void), typeof(QByteArray), data, typeof(string), mimeType);
        }
        public void SetContent(QByteArray data) {
            interceptor.Invoke("setContent#", "setContent(const QByteArray&)", typeof(void), typeof(QByteArray), data);
        }
        public QWebHistory History() {
            return (QWebHistory) interceptor.Invoke("history", "history() const", typeof(QWebHistory));
        }
        public QWebSettings Settings() {
            return (QWebSettings) interceptor.Invoke("settings", "settings() const", typeof(QWebSettings));
        }
        public QAction PageAction(QWebPage.WebAction action) {
            return (QAction) interceptor.Invoke("pageAction$", "pageAction(QWebPage::WebAction) const", typeof(QAction), typeof(QWebPage.WebAction), action);
        }
        public void TriggerPageAction(QWebPage.WebAction action, bool arg2) {
            interceptor.Invoke("triggerPageAction$$", "triggerPageAction(QWebPage::WebAction, bool)", typeof(void), typeof(QWebPage.WebAction), action, typeof(bool), arg2);
        }
        public void TriggerPageAction(QWebPage.WebAction action) {
            interceptor.Invoke("triggerPageAction$", "triggerPageAction(QWebPage::WebAction)", typeof(void), typeof(QWebPage.WebAction), action);
        }
        public bool FindText(string subString, uint options) {
            return (bool) interceptor.Invoke("findText$$", "findText(const QString&, QWebPage::FindFlags)", typeof(bool), typeof(string), subString, typeof(uint), options);
        }
        public bool FindText(string subString) {
            return (bool) interceptor.Invoke("findText$", "findText(const QString&)", typeof(bool), typeof(string), subString);
        }
        [SmokeMethod("setGeometry(const QRectF&)")]
        public override void SetGeometry(QRectF rect) {
            interceptor.Invoke("setGeometry#", "setGeometry(const QRectF&)", typeof(void), typeof(QRectF), rect);
        }
        [SmokeMethod("updateGeometry()")]
        public new virtual void UpdateGeometry() {
            interceptor.Invoke("updateGeometry", "updateGeometry()", typeof(void));
        }
        [SmokeMethod("paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)")]
        public override void Paint(QPainter arg1, QStyleOptionGraphicsItem options, QWidget widget) {
            interceptor.Invoke("paint###", "paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)", typeof(void), typeof(QPainter), arg1, typeof(QStyleOptionGraphicsItem), options, typeof(QWidget), widget);
        }
        [SmokeMethod("paint(QPainter*, const QStyleOptionGraphicsItem*)")]
        public override void Paint(QPainter arg1, QStyleOptionGraphicsItem options) {
            interceptor.Invoke("paint##", "paint(QPainter*, const QStyleOptionGraphicsItem*)", typeof(void), typeof(QPainter), arg1, typeof(QStyleOptionGraphicsItem), options);
        }
        [SmokeMethod("itemChange(QGraphicsItem::GraphicsItemChange, const QVariant&)")]
        public new virtual QVariant ItemChange(QGraphicsItem.GraphicsItemChange change, QVariant value) {
            return (QVariant) interceptor.Invoke("itemChange$#", "itemChange(QGraphicsItem::GraphicsItemChange, const QVariant&)", typeof(QVariant), typeof(QGraphicsItem.GraphicsItemChange), change, typeof(QVariant), value);
        }
        [SmokeMethod("event(QEvent*)")]
        public new virtual bool Event(QEvent arg1) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), arg1);
        }
        [SmokeMethod("sizeHint(Qt::SizeHint, const QSizeF&) const")]
        public new virtual QSizeF SizeHint(Qt.SizeHint which, QSizeF constraint) {
            return (QSizeF) interceptor.Invoke("sizeHint$#", "sizeHint(Qt::SizeHint, const QSizeF&) const", typeof(QSizeF), typeof(Qt.SizeHint), which, typeof(QSizeF), constraint);
        }
        [SmokeMethod("inputMethodQuery(Qt::InputMethodQuery) const")]
        public new virtual QVariant InputMethodQuery(Qt.InputMethodQuery query) {
            return (QVariant) interceptor.Invoke("inputMethodQuery$", "inputMethodQuery(Qt::InputMethodQuery) const", typeof(QVariant), typeof(Qt.InputMethodQuery), query);
        }
        [Q_SLOT("void stop()")]
        public void Stop() {
            interceptor.Invoke("stop", "stop()", typeof(void));
        }
        [Q_SLOT("void back()")]
        public void Back() {
            interceptor.Invoke("back", "back()", typeof(void));
        }
        [Q_SLOT("void forward()")]
        public void Forward() {
            interceptor.Invoke("forward", "forward()", typeof(void));
        }
        [Q_SLOT("void reload()")]
        public void Reload() {
            interceptor.Invoke("reload", "reload()", typeof(void));
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
        [SmokeMethod("mouseMoveEvent(QGraphicsSceneMouseEvent*)")]
        protected override void MouseMoveEvent(QGraphicsSceneMouseEvent arg1) {
            interceptor.Invoke("mouseMoveEvent#", "mouseMoveEvent(QGraphicsSceneMouseEvent*)", typeof(void), typeof(QGraphicsSceneMouseEvent), arg1);
        }
        [SmokeMethod("hoverMoveEvent(QGraphicsSceneHoverEvent*)")]
        protected override void HoverMoveEvent(QGraphicsSceneHoverEvent arg1) {
            interceptor.Invoke("hoverMoveEvent#", "hoverMoveEvent(QGraphicsSceneHoverEvent*)", typeof(void), typeof(QGraphicsSceneHoverEvent), arg1);
        }
        [SmokeMethod("hoverLeaveEvent(QGraphicsSceneHoverEvent*)")]
        protected override void HoverLeaveEvent(QGraphicsSceneHoverEvent arg1) {
            interceptor.Invoke("hoverLeaveEvent#", "hoverLeaveEvent(QGraphicsSceneHoverEvent*)", typeof(void), typeof(QGraphicsSceneHoverEvent), arg1);
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
        [SmokeMethod("contextMenuEvent(QGraphicsSceneContextMenuEvent*)")]
        protected override void ContextMenuEvent(QGraphicsSceneContextMenuEvent arg1) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QGraphicsSceneContextMenuEvent*)", typeof(void), typeof(QGraphicsSceneContextMenuEvent), arg1);
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
        [SmokeMethod("focusInEvent(QFocusEvent*)")]
        protected override void FocusInEvent(QFocusEvent arg1) {
            interceptor.Invoke("focusInEvent#", "focusInEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), arg1);
        }
        [SmokeMethod("focusOutEvent(QFocusEvent*)")]
        protected override void FocusOutEvent(QFocusEvent arg1) {
            interceptor.Invoke("focusOutEvent#", "focusOutEvent(QFocusEvent*)", typeof(void), typeof(QFocusEvent), arg1);
        }
        [SmokeMethod("inputMethodEvent(QInputMethodEvent*)")]
        protected override void InputMethodEvent(QInputMethodEvent arg1) {
            interceptor.Invoke("inputMethodEvent#", "inputMethodEvent(QInputMethodEvent*)", typeof(void), typeof(QInputMethodEvent), arg1);
        }
        [SmokeMethod("focusNextPrevChild(bool)")]
        protected override bool FocusNextPrevChild(bool next) {
            return (bool) interceptor.Invoke("focusNextPrevChild$", "focusNextPrevChild(bool)", typeof(bool), typeof(bool), next);
        }
        [SmokeMethod("sceneEvent(QEvent*)")]
        protected override bool SceneEvent(QEvent arg1) {
            return (bool) interceptor.Invoke("sceneEvent#", "sceneEvent(QEvent*)", typeof(bool), typeof(QEvent), arg1);
        }
        ~QGraphicsWebView() {
            interceptor.Invoke("~QGraphicsWebView", "~QGraphicsWebView()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QGraphicsWebView", "~QGraphicsWebView()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQGraphicsWebViewSignals Emit {
            get { return (IQGraphicsWebViewSignals) Q_EMIT; }
        }
    }

    public interface IQGraphicsWebViewSignals : IQGraphicsWidgetSignals {
        [Q_SIGNAL("void loadStarted()")]
        void LoadStarted();
        [Q_SIGNAL("void loadFinished(bool)")]
        void LoadFinished(bool arg1);
        [Q_SIGNAL("void loadProgress(int)")]
        void LoadProgress(int progress);
        [Q_SIGNAL("void urlChanged(QUrl)")]
        void UrlChanged(QUrl arg1);
        [Q_SIGNAL("void titleChanged(QString)")]
        void TitleChanged(string arg1);
        [Q_SIGNAL("void iconChanged()")]
        void IconChanged();
        [Q_SIGNAL("void statusBarMessage(QString)")]
        void StatusBarMessage(string message);
        [Q_SIGNAL("void linkClicked(QUrl)")]
        void LinkClicked(QUrl arg1);
    }
}
