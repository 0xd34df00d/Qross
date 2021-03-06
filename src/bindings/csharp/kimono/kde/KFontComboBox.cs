//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  A combobox to select the font from. Lightweight counterpart to KFontChooser,
    ///  for situations where only the font family should be selected, while the
    ///  font style and size are handled by other means. Like in KFontChooser,
    ///  this widget will show the font previews in the unrolled dropdown list.
    ///  @note The class is similar to QFontComboBox, but more tightly integrated
    ///  with KDE desktop. Use it instead of QFontComboBox by default in KDE code.
    ///  See <see cref="IKFontComboBoxSignals"></see> for signals emitted by KFontComboBox
    /// </remarks>        <author> Chusslove Illich \<caslav.ilic@gmx.net\>
    /// </author>
    ///         <short> A lightweight font selection widget. </short>
    ///         <see> KFontAction</see>
    ///         <see> KFontChooser</see>
    [SmokeClass("KFontComboBox")]
    public class KFontComboBox : KComboBox, IDisposable {
        protected KFontComboBox(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KFontComboBox), this);
        }
        [Q_PROPERTY("QFont", "currentFont")]
        public QFont CurrentFont {
            get { return (QFont) interceptor.Invoke("currentFont", "currentFont()", typeof(QFont)); }
            set { interceptor.Invoke("setCurrentFont#", "setCurrentFont(QFont)", typeof(void), typeof(QFont), value); }
        }
        /// <remarks>
        ///  Constructor.
        /// <param> name="parent" the parent widget
        ///      </param></remarks>        <short>    Constructor.</short>
        public KFontComboBox(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFontComboBox#", "KFontComboBox(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KFontComboBox() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFontComboBox", "KFontComboBox()", typeof(void));
        }
        /// <remarks>
        ///  Toggle selectable fonts to be only those of fixed width or all.
        /// <param> name="onlyFixed" only fixed width fonts when <code>true</code>,
        ///                   all fonts when <code>false</code>
        ///      </param></remarks>        <short>    Toggle selectable fonts to be only those of fixed width or all.</short>
        public void SetOnlyFixed(bool onlyFixed) {
            interceptor.Invoke("setOnlyFixed$", "setOnlyFixed(bool)", typeof(void), typeof(bool), onlyFixed);
        }
        /// <remarks>
        ///  The recommended size of the widget.
        ///  Reimplemented to make the recommended width independent
        ///  of the particular fonts installed.
        /// </remarks>        <return> recommended size
        ///      </return>
        ///         <short>    The recommended size of the widget.</short>
        [SmokeMethod("sizeHint() const")]
        public override QSize SizeHint() {
            return (QSize) interceptor.Invoke("sizeHint", "sizeHint() const", typeof(QSize));
        }
        /// <remarks>
        ///  Set the font to show as selected in the combobox.
        /// <param> name="font" the new font
        ///      </param></remarks>        <short>    Set the font to show as selected in the combobox.</short>
        [Q_SLOT("void setCurrentFont(QFont)")]
        public void SetCurrentFont(QFont font) {
            interceptor.Invoke("setCurrentFont#", "setCurrentFont(const QFont&)", typeof(void), typeof(QFont), font);
        }
        [SmokeMethod("event(QEvent*)")]
        protected new virtual bool Event(QEvent e) {
            return (bool) interceptor.Invoke("event#", "event(QEvent*)", typeof(bool), typeof(QEvent), e);
        }
        ~KFontComboBox() {
            interceptor.Invoke("~KFontComboBox", "~KFontComboBox()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KFontComboBox", "~KFontComboBox()", typeof(void));
        }
        protected new IKFontComboBoxSignals Emit {
            get { return (IKFontComboBoxSignals) Q_EMIT; }
        }
    }

    public interface IKFontComboBoxSignals : IKComboBoxSignals {
        /// <remarks>
        ///  Emitted when a new font has been selected,
        ///  either through user input or by setFont().
        /// <param> name="font" the new font
        ///      </param></remarks>        <short>    Emitted when a new font has been selected,  either through user input or by setFont().</short>
        [Q_SIGNAL("void currentFontChanged(QFont)")]
        void CurrentFontChanged(QFont font);
    }
}
