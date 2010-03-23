//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QStyleOptionTab")]
    public class QStyleOptionTab : QStyleOption, IDisposable {
        protected QStyleOptionTab(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QStyleOptionTab), this);
        }
        public enum StyleOptionType {
            Type = QStyleOption.OptionType.SO_Tab,
        }
        public enum StyleOptionVersion {
            Version = 1,
        }
        public enum TabPosition {
            Beginning = 0,
            Middle = 1,
            End = 2,
            OnlyOneTab = 3,
        }
        public enum SelectedPosition {
            NotAdjacent = 0,
            NextIsSelected = 1,
            PreviousIsSelected = 2,
        }
        public enum CornerWidget {
            NoCornerWidgets = 0x00,
            LeftCornerWidget = 0x01,
            RightCornerWidget = 0x02,
        }
        public QTabBar.Shape Shape {
            get { return (QTabBar.Shape) interceptor.Invoke("shape", "shape()", typeof(QTabBar.Shape)); }
            set { interceptor.Invoke("setShape$", "setShape(QTabBar::Shape)", typeof(void), typeof(QTabBar.Shape), value); }
        }
        public string Text {
            get { return (string) interceptor.Invoke("text", "text()", typeof(string)); }
            set { interceptor.Invoke("setText$", "setText(QString)", typeof(void), typeof(string), value); }
        }
        public QIcon Icon {
            get { return (QIcon) interceptor.Invoke("icon", "icon()", typeof(QIcon)); }
            set { interceptor.Invoke("setIcon#", "setIcon(QIcon)", typeof(void), typeof(QIcon), value); }
        }
        public int Row {
            get { return (int) interceptor.Invoke("row", "row()", typeof(int)); }
            set { interceptor.Invoke("setRow$", "setRow(int)", typeof(void), typeof(int), value); }
        }
        public QStyleOptionTab.TabPosition Position {
            get { return (QStyleOptionTab.TabPosition) interceptor.Invoke("position", "position()", typeof(QStyleOptionTab.TabPosition)); }
            set { interceptor.Invoke("setPosition$", "setPosition(QStyleOptionTab::TabPosition)", typeof(void), typeof(QStyleOptionTab.TabPosition), value); }
        }
        public QStyleOptionTab.SelectedPosition selectedPosition {
            get { return (QStyleOptionTab.SelectedPosition) interceptor.Invoke("selectedPosition", "selectedPosition()", typeof(QStyleOptionTab.SelectedPosition)); }
            set { interceptor.Invoke("setSelectedPosition$", "setSelectedPosition(QStyleOptionTab::SelectedPosition)", typeof(void), typeof(QStyleOptionTab.SelectedPosition), value); }
        }
        public uint CornerWidgets {
            get { return (uint) interceptor.Invoke("cornerWidgets", "cornerWidgets()", typeof(uint)); }
            set { interceptor.Invoke("setCornerWidgets$", "setCornerWidgets(QStyleOptionTab::CornerWidgets)", typeof(void), typeof(uint), value); }
        }
        public QStyleOptionTab() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionTab", "QStyleOptionTab()", typeof(void));
        }
        public QStyleOptionTab(QStyleOptionTab other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionTab#", "QStyleOptionTab(const QStyleOptionTab&)", typeof(void), typeof(QStyleOptionTab), other);
        }
        public QStyleOptionTab(int version) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QStyleOptionTab$", "QStyleOptionTab(int)", typeof(void), typeof(int), version);
        }
        ~QStyleOptionTab() {
            interceptor.Invoke("~QStyleOptionTab", "~QStyleOptionTab()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QStyleOptionTab", "~QStyleOptionTab()", typeof(void));
        }
    }
}
