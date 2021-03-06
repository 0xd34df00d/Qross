//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  This class provides a widget with a lineedit and a button, which invokes
    ///  a font dialog (KFontDialog).
    ///  The lineedit provides a preview of the selected font. The preview text can
    ///  be customized. You can also have the font dialog show only the fixed fonts.
    ///  \image html kfontrequester.png "KDE Font Requester"
    ///   See <see cref="IKFontRequesterSignals"></see> for signals emitted by KFontRequester
    /// </remarks>        <author> Nadeem Hasan <nhasan@kde.org>
    /// </author>
    ///         <short>    This class provides a widget with a lineedit and a button, which invokes  a font dialog (KFontDialog).</short>
    [SmokeClass("KFontRequester")]
    public class KFontRequester : QWidget, IDisposable {
        protected KFontRequester(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KFontRequester), this);
        }
        [Q_PROPERTY("QString", "title")]
        public string Title {
            get { return (string) interceptor.Invoke("title", "title()", typeof(string)); }
            set { interceptor.Invoke("setTitle$", "setTitle(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QString", "sampleText")]
        public string SampleText {
            get { return (string) interceptor.Invoke("sampleText", "sampleText()", typeof(string)); }
            set { interceptor.Invoke("setSampleText$", "setSampleText(QString)", typeof(void), typeof(string), value); }
        }
        [Q_PROPERTY("QFont", "font")]
        public new QFont Font {
            get { return (QFont) interceptor.Invoke("font", "font()", typeof(QFont)); }
            set { interceptor.Invoke("setFont#", "setFont(QFont)", typeof(void), typeof(QFont), value); }
        }
        /// <remarks>
        ///  Constructs a font requester widget.
        /// <param> name="parent" The parent widget.
        /// </param><param> name="onlyFixed" Only display fonts which have fixed-width character
        ///         sizes.
        ///      </param></remarks>        <short>    Constructs a font requester widget.</short>
        public KFontRequester(QWidget parent, bool onlyFixed) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFontRequester#$", "KFontRequester(QWidget*, bool)", typeof(void), typeof(QWidget), parent, typeof(bool), onlyFixed);
        }
        public KFontRequester(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFontRequester#", "KFontRequester(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KFontRequester() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFontRequester", "KFontRequester()", typeof(void));
        }
        /// <remarks>
        /// </remarks>        <return> Returns true if only fixed fonts are displayed.
        ///      </return>
        ///         <short>   </short>
        public bool IsFixedOnly() {
            return (bool) interceptor.Invoke("isFixedOnly", "isFixedOnly() const", typeof(bool));
        }
        /// <remarks>
        /// </remarks>        <return> Pointer to the label used for preview.
        ///      </return>
        ///         <short>   </short>
        public QLabel Label() {
            return (QLabel) interceptor.Invoke("label", "label() const", typeof(QLabel));
        }
        /// <remarks>
        /// </remarks>        <return> Pointer to the pushbutton in the widget.
        ///      </return>
        ///         <short>   </short>
        public QPushButton Button() {
            return (QPushButton) interceptor.Invoke("button", "button() const", typeof(QPushButton));
        }
        /// <remarks>
        ///  Sets the currently selected font in the requester.
        /// <param> name="font" The font to select.
        /// </param><param> name="onlyFixed" Display only fixed-width fonts in the font dialog
        ///  if <code>true</code>, or vice-versa.
        ///      </param></remarks>        <short>    Sets the currently selected font in the requester.</short>
        [SmokeMethod("setFont(const QFont&, bool)")]
        public virtual void SetFont(QFont font, bool onlyFixed) {
            interceptor.Invoke("setFont#$", "setFont(const QFont&, bool)", typeof(void), typeof(QFont), font, typeof(bool), onlyFixed);
        }
        [SmokeMethod("setFont(const QFont&)")]
        public virtual void SetFont(QFont font) {
            interceptor.Invoke("setFont#", "setFont(const QFont&)", typeof(void), typeof(QFont), font);
        }
        /// <remarks>
        ///  Sets the sample text.
        ///  Normally you should not change this
        ///  text, but it can be better to do this if the default text is
        ///  too large for the edit area when using the default font of your
        ///  application. Default text is current font name and size. Setting
        ///  the text to string() will restore the default.
        /// <param> name="text" The new sample text. The current will be removed.
        ///      </param></remarks>        <short>    Sets the sample text.</short>
        [SmokeMethod("setSampleText(const QString&)")]
        public virtual void SetSampleText(string text) {
            interceptor.Invoke("setSampleText$", "setSampleText(const QString&)", typeof(void), typeof(string), text);
        }
        /// <remarks>
        ///  Set the title for the widget that will be used in the tooltip and
        ///  what's this text.
        /// <param> name="title" The title to be set.
        ///      </param></remarks>        <short>    Set the title for the widget that will be used in the tooltip and  what's this text.</short>
        [SmokeMethod("setTitle(const QString&)")]
        public virtual void SetTitle(string title) {
            interceptor.Invoke("setTitle$", "setTitle(const QString&)", typeof(void), typeof(string), title);
        }
        ~KFontRequester() {
            interceptor.Invoke("~KFontRequester", "~KFontRequester()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KFontRequester", "~KFontRequester()", typeof(void));
        }
        protected new IKFontRequesterSignals Emit {
            get { return (IKFontRequesterSignals) Q_EMIT; }
        }
    }

    public interface IKFontRequesterSignals : IQWidgetSignals {
        /// <remarks>
        ///  Emitted when a new <code>font</code> has been selected in the underlying dialog
        ///      </remarks>        <short>    Emitted when a new <code>font</code> has been selected in the underlying dialog      </short>
        [Q_SIGNAL("void fontSelected(QFont)")]
        void FontSelected(QFont font);
    }
}
