//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QLayout")]
    public abstract class QLayout : QObject, IQLayoutItem {
        protected QLayout(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QLayout), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QLayout() {
            staticInterceptor = new SmokeInvocation(typeof(QLayout), null);
        }
        public enum SizeConstraint {
            SetDefaultConstraint = 0,
            SetNoConstraint = 1,
            SetMinimumSize = 2,
            SetFixedSize = 3,
            SetMaximumSize = 4,
            SetMinAndMaxSize = 5,
        }
        [Q_PROPERTY("int", "margin")]
        public int Margin {
            get { return (int) interceptor.Invoke("margin", "margin()", typeof(int)); }
            set { interceptor.Invoke("setMargin$", "setMargin(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("int", "spacing")]
        public int Spacing {
            get { return (int) interceptor.Invoke("spacing", "spacing()", typeof(int)); }
            set { interceptor.Invoke("setSpacing$", "setSpacing(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("QLayout::SizeConstraint", "sizeConstraint")]
        public QLayout.SizeConstraint sizeConstraint {
            get { return (QLayout.SizeConstraint) interceptor.Invoke("sizeConstraint", "sizeConstraint()", typeof(QLayout.SizeConstraint)); }
            set { interceptor.Invoke("setSizeConstraint$", "setSizeConstraint(QLayout::SizeConstraint)", typeof(void), typeof(QLayout.SizeConstraint), value); }
        }
        // QLayout* QLayout(QLayoutPrivate& arg1,QLayout* arg2,QWidget* arg3); >>>> NOT CONVERTED
        public QLayout(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLayout#", "QLayout(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public QLayout() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLayout", "QLayout()", typeof(void));
        }
        public void SetContentsMargins(int left, int top, int right, int bottom) {
            interceptor.Invoke("setContentsMargins$$$$", "setContentsMargins(int, int, int, int)", typeof(void), typeof(int), left, typeof(int), top, typeof(int), right, typeof(int), bottom);
        }
        public void SetContentsMargins(QMargins margins) {
            interceptor.Invoke("setContentsMargins#", "setContentsMargins(const QMargins&)", typeof(void), typeof(QMargins), margins);
        }
        public void GetContentsMargins(ref int left, ref int top, ref int right, ref int bottom) {
            StackItem[] stack = new StackItem[5];
            stack[1].s_int = left;
            stack[2].s_int = top;
            stack[3].s_int = right;
            stack[4].s_int = bottom;
            interceptor.Invoke("getContentsMargins$$$$", "getContentsMargins(int*, int*, int*, int*) const", stack);
            left = stack[1].s_int;
            top = stack[2].s_int;
            right = stack[3].s_int;
            bottom = stack[4].s_int;
            return;
        }
        public QMargins ContentsMargins() {
            return (QMargins) interceptor.Invoke("contentsMargins", "contentsMargins() const", typeof(QMargins));
        }
        public QRect ContentsRect() {
            return (QRect) interceptor.Invoke("contentsRect", "contentsRect() const", typeof(QRect));
        }
        public bool SetAlignment(QWidget w, uint alignment) {
            return (bool) interceptor.Invoke("setAlignment#$", "setAlignment(QWidget*, Qt::Alignment)", typeof(bool), typeof(QWidget), w, typeof(uint), alignment);
        }
        public bool SetAlignment(QLayout l, uint alignment) {
            return (bool) interceptor.Invoke("setAlignment#$", "setAlignment(QLayout*, Qt::Alignment)", typeof(bool), typeof(QLayout), l, typeof(uint), alignment);
        }
        public void SetAlignment(uint alignment) {
            interceptor.Invoke("setAlignment$", "setAlignment(Qt::Alignment)", typeof(void), typeof(uint), alignment);
        }
        public void SetMenuBar(QWidget w) {
            interceptor.Invoke("setMenuBar#", "setMenuBar(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        public QWidget MenuBar() {
            return (QWidget) interceptor.Invoke("menuBar", "menuBar() const", typeof(QWidget));
        }
        public QWidget ParentWidget() {
            return (QWidget) interceptor.Invoke("parentWidget", "parentWidget() const", typeof(QWidget));
        }
        [SmokeMethod("invalidate()")]
        public virtual void Invalidate() {
            interceptor.Invoke("invalidate", "invalidate()", typeof(void));
        }
        [SmokeMethod("geometry() const")]
        public virtual QRect Geometry() {
            return (QRect) interceptor.Invoke("geometry", "geometry() const", typeof(QRect));
        }
        public bool Activate() {
            return (bool) interceptor.Invoke("activate", "activate()", typeof(bool));
        }
        public void Update() {
            interceptor.Invoke("update", "update()", typeof(void));
        }
        public void AddWidget(QWidget w) {
            interceptor.Invoke("addWidget#", "addWidget(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        [SmokeMethod("addItem(QLayoutItem*)")]
        public abstract void AddItem(IQLayoutItem arg1);
        public void RemoveWidget(QWidget w) {
            interceptor.Invoke("removeWidget#", "removeWidget(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        public void RemoveItem(IQLayoutItem arg1) {
            interceptor.Invoke("removeItem#", "removeItem(QLayoutItem*)", typeof(void), typeof(IQLayoutItem), arg1);
        }
        [SmokeMethod("expandingDirections() const")]
        public virtual uint ExpandingDirections() {
            return (uint) interceptor.Invoke("expandingDirections", "expandingDirections() const", typeof(uint));
        }
        [SmokeMethod("minimumSize() const")]
        public virtual QSize MinimumSize() {
            return (QSize) interceptor.Invoke("minimumSize", "minimumSize() const", typeof(QSize));
        }
        [SmokeMethod("maximumSize() const")]
        public virtual QSize MaximumSize() {
            return (QSize) interceptor.Invoke("maximumSize", "maximumSize() const", typeof(QSize));
        }
        [SmokeMethod("setGeometry(const QRect&)")]
        public virtual void SetGeometry(QRect arg1) {
            interceptor.Invoke("setGeometry#", "setGeometry(const QRect&)", typeof(void), typeof(QRect), arg1);
        }
        [SmokeMethod("itemAt(int) const")]
        public abstract IQLayoutItem ItemAt(int index);
        [SmokeMethod("takeAt(int)")]
        public abstract IQLayoutItem TakeAt(int index);
        [SmokeMethod("indexOf(QWidget*) const")]
        public virtual int IndexOf(QWidget arg1) {
            return (int) interceptor.Invoke("indexOf#", "indexOf(QWidget*) const", typeof(int), typeof(QWidget), arg1);
        }
        [SmokeMethod("count() const")]
        public abstract int Count();
        [SmokeMethod("isEmpty() const")]
        public virtual bool IsEmpty() {
            return (bool) interceptor.Invoke("isEmpty", "isEmpty() const", typeof(bool));
        }
        public int TotalHeightForWidth(int w) {
            return (int) interceptor.Invoke("totalHeightForWidth$", "totalHeightForWidth(int) const", typeof(int), typeof(int), w);
        }
        public QSize TotalMinimumSize() {
            return (QSize) interceptor.Invoke("totalMinimumSize", "totalMinimumSize() const", typeof(QSize));
        }
        public QSize TotalMaximumSize() {
            return (QSize) interceptor.Invoke("totalMaximumSize", "totalMaximumSize() const", typeof(QSize));
        }
        public QSize TotalSizeHint() {
            return (QSize) interceptor.Invoke("totalSizeHint", "totalSizeHint() const", typeof(QSize));
        }
        [SmokeMethod("layout()")]
        public virtual QLayout Layout() {
            return (QLayout) interceptor.Invoke("layout", "layout()", typeof(QLayout));
        }
        public void SetEnabled(bool arg1) {
            interceptor.Invoke("setEnabled$", "setEnabled(bool)", typeof(void), typeof(bool), arg1);
        }
        public bool IsEnabled() {
            return (bool) interceptor.Invoke("isEnabled", "isEnabled() const", typeof(bool));
        }
        protected void WidgetEvent(QEvent arg1) {
            interceptor.Invoke("widgetEvent#", "widgetEvent(QEvent*)", typeof(void), typeof(QEvent), arg1);
        }
        [SmokeMethod("childEvent(QChildEvent*)")]
        protected override void ChildEvent(QChildEvent e) {
            interceptor.Invoke("childEvent#", "childEvent(QChildEvent*)", typeof(void), typeof(QChildEvent), e);
        }
        protected void AddChildLayout(QLayout l) {
            interceptor.Invoke("addChildLayout#", "addChildLayout(QLayout*)", typeof(void), typeof(QLayout), l);
        }
        protected void AddChildWidget(QWidget w) {
            interceptor.Invoke("addChildWidget#", "addChildWidget(QWidget*)", typeof(void), typeof(QWidget), w);
        }
        protected QRect AlignmentRect(QRect arg1) {
            return (QRect) interceptor.Invoke("alignmentRect#", "alignmentRect(const QRect&) const", typeof(QRect), typeof(QRect), arg1);
        }
        [SmokeMethod("sizeHint() const")]
        public abstract QSize SizeHint();
        [SmokeMethod("hasHeightForWidth() const")]
        public virtual bool HasHeightForWidth() {
            return (bool) interceptor.Invoke("hasHeightForWidth", "hasHeightForWidth() const", typeof(bool));
        }
        [SmokeMethod("heightForWidth(int) const")]
        public virtual int HeightForWidth(int arg1) {
            return (int) interceptor.Invoke("heightForWidth$", "heightForWidth(int) const", typeof(int), typeof(int), arg1);
        }
        [SmokeMethod("minimumHeightForWidth(int) const")]
        public virtual int MinimumHeightForWidth(int arg1) {
            return (int) interceptor.Invoke("minimumHeightForWidth$", "minimumHeightForWidth(int) const", typeof(int), typeof(int), arg1);
        }
        [SmokeMethod("widget()")]
        public virtual QWidget Widget() {
            return (QWidget) interceptor.Invoke("widget", "widget()", typeof(QWidget));
        }
        [SmokeMethod("spacerItem()")]
        public virtual QSpacerItem SpacerItem() {
            return (QSpacerItem) interceptor.Invoke("spacerItem", "spacerItem()", typeof(QSpacerItem));
        }
        public uint Alignment() {
            return (uint) interceptor.Invoke("alignment", "alignment() const", typeof(uint));
        }
        public uint ControlTypes() {
            return (uint) interceptor.Invoke("controlTypes", "controlTypes() const", typeof(uint));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        public static QSize ClosestAcceptableSize(QWidget w, QSize s) {
            return (QSize) staticInterceptor.Invoke("closestAcceptableSize##", "closestAcceptableSize(const QWidget*, const QSize&)", typeof(QSize), typeof(QWidget), w, typeof(QSize), s);
        }
        protected new IQLayoutSignals Emit {
            get { return (IQLayoutSignals) Q_EMIT; }
        }
    }

    public interface IQLayoutSignals : IQObjectSignals {
    }
}
