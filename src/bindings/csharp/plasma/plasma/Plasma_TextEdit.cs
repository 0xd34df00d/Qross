//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  @class TextEdit plasma/widgets/textedit.h <Plasma/Widgets/TextEdit>
    ///  See <see cref="ITextEditSignals"></see> for signals emitted by TextEdit
    /// </remarks>        <short> Provides a plasma-themed KTextEdit.  </short>
    [SmokeClass("Plasma::TextEdit")]
    public class TextEdit : QGraphicsProxyWidget, IDisposable {
        protected TextEdit(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(TextEdit), this);
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
        [Q_PROPERTY("QString", "stylesheet")]
        public string Stylesheet {
            get { return (string) interceptor.Invoke("styleSheet", "styleSheet()", typeof(string)); }
            set { interceptor.Invoke("setStyleSheet$", "setStyleSheet(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("KTextEdit*", "nativeWidget")]
        public KTextEdit NativeWidget {
            get { return (KTextEdit) interceptor.Invoke("nativeWidget", "nativeWidget()", typeof(KTextEdit)); }
            set { interceptor.Invoke("setNativeWidget#", "setNativeWidget(KTextEdit*)", typeof(void), typeof(KTextEdit), value); }
        }
        [Q_PROPERTY("bool", "readOnly")]
        public bool ReadOnly {
            get { return (bool) interceptor.Invoke("isReadOnly", "isReadOnly()", typeof(bool)); }
            set { interceptor.Invoke("setReadOnly$", "setReadOnly(bool)", typeof(void), typeof(bool), value); }
        }
        public TextEdit(QGraphicsWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("TextEdit#", "TextEdit(QGraphicsWidget*)", typeof(void), typeof(QGraphicsWidget), parent);
        }
        public TextEdit() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("TextEdit", "TextEdit()", typeof(void));
        }
        /// <remarks>
        ///  Allows appending text to the text browser
        /// </remarks>        <short>    Allows appending text to the text browser </short>
        [Q_SLOT("void append(QString)")]
        public void Append(string text) {
            interceptor.Invoke("append$", "append(const QString&)", typeof(void), typeof(string), text);
        }
        [Q_SLOT("void dataUpdated(QString, Plasma::DataEngine::Data)")]
        public void DataUpdated(string sourceName, Dictionary<string, QVariant> data) {
            interceptor.Invoke("dataUpdated$?", "dataUpdated(const QString&, const QHash<QString,QVariant>&)", typeof(void), typeof(string), sourceName, typeof(Dictionary<string, QVariant>), data);
        }
        [SmokeMethod("resizeEvent(QGraphicsSceneResizeEvent*)")]
        protected override void ResizeEvent(QGraphicsSceneResizeEvent arg1) {
            interceptor.Invoke("resizeEvent#", "resizeEvent(QGraphicsSceneResizeEvent*)", typeof(void), typeof(QGraphicsSceneResizeEvent), arg1);
        }
        [SmokeMethod("changeEvent(QEvent*)")]
        protected override void ChangeEvent(QEvent arg1) {
            interceptor.Invoke("changeEvent#", "changeEvent(QEvent*)", typeof(void), typeof(QEvent), arg1);
        }
        [SmokeMethod("contextMenuEvent(QGraphicsSceneContextMenuEvent*)")]
        protected override void ContextMenuEvent(QGraphicsSceneContextMenuEvent arg1) {
            interceptor.Invoke("contextMenuEvent#", "contextMenuEvent(QGraphicsSceneContextMenuEvent*)", typeof(void), typeof(QGraphicsSceneContextMenuEvent), arg1);
        }
        ~TextEdit() {
            interceptor.Invoke("~TextEdit", "~TextEdit()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~TextEdit", "~TextEdit()", typeof(void));
        }
        protected new ITextEditSignals Emit {
            get { return (ITextEditSignals) Q_EMIT; }
        }
    }

    public interface ITextEditSignals : IQGraphicsProxyWidgetSignals {
        [Q_SIGNAL("void textChanged()")]
        void TextChanged();
    }
}
