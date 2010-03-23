//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  This widget lets the user choose a QKeySequence, which is usually used as a shortcut key,
    ///  by pressing the keys just like to trigger a shortcut. Calling captureKeySequence(), or
    ///  the user clicking into the widget, start recording.
    ///  A check for conflict with shortcut of this application can also be performed.
    ///  call setCheckActionCollections() to set the list of action collections to check with,
    ///  and applyStealShortcut when applying changes.
    ///   See <see cref="IKKeySequenceWidgetSignals"></see> for signals emitted by KKeySequenceWidget
    /// </remarks>        <author> Mark Donohoe <donohoe@kde.org>
    /// </author>
    ///         <short> A widget to input a QKeySequence. </short>
    [SmokeClass("KKeySequenceWidget")]
    public class KKeySequenceWidget : QWidget, IDisposable {
        protected KKeySequenceWidget(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KKeySequenceWidget), this);
        }
        public enum Validation {
            Validate = 0,
            NoValidate = 1,
        }
        /// <remarks>
        ///  Constructor.
        /// 	</remarks>        <short>    Constructor.</short>
        public KKeySequenceWidget(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KKeySequenceWidget#", "KKeySequenceWidget(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KKeySequenceWidget() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KKeySequenceWidget", "KKeySequenceWidget()", typeof(void));
        }
        /// <remarks>
        ///  Set if a key sequence should be checked against kde's standard
        ///  shortcuts (@see KStandardShortcut).
        ///  It is a good idea to enable this when caputing a key sequence for a
        ///  global shortcut. The default is not to check against standard
        ///  shortcuts.
        /// <param> name="check" True . Check against standard shortcuts
        /// </param></remarks>        <short>    Set if a key sequence should be checked against kde's standard  shortcuts (@see KStandardShortcut).</short>
        public bool CheckAgainstStandardShortcuts() {
            return (bool) interceptor.Invoke("checkAgainstStandardShortcuts", "checkAgainstStandardShortcuts() const", typeof(bool));
        }
        public void SetCheckAgainstStandardShortcuts(bool check) {
            interceptor.Invoke("setCheckAgainstStandardShortcuts$", "setCheckAgainstStandardShortcuts(bool)", typeof(void), typeof(bool), check);
        }
        /// <remarks>
        ///  This only applies to user input, not to setShortcut().
        ///  Set whether to accept "plain" keys without modifiers (like Ctrl, Alt, Meta).
        ///  Plain keys by our definition include letter and symbol keys and
        ///  text editing keys (Return, Space, Tab, Backspace, Delete).
        ///  "Special" keys like F1, Cursor keys, Insert, PageDown will always work.
        /// 	 </remarks>        <short>    This only applies to user input, not to setShortcut().</short>
        public void SetModifierlessAllowed(bool allow) {
            interceptor.Invoke("setModifierlessAllowed$", "setModifierlessAllowed(bool)", typeof(void), typeof(bool), allow);
        }
        /// <remarks>
        ///  Checks whether the key sequence <b>seq</b> is available to grab.
        ///  The sequence is checked under the same rules as if it has been typed by
        ///  the user. This method is useful if you get key sequences from another
        ///  input source and want to check if it is save to set them.
        /// </remarks>        <short>    Checks whether the key sequence <b>seq</b> is available to grab.</short>
        public bool IsKeySequenceAvailable(QKeySequence seq) {
            return (bool) interceptor.Invoke("isKeySequenceAvailable#", "isKeySequenceAvailable(const QKeySequence&) const", typeof(bool), typeof(QKeySequence), seq);
        }
        /// <remarks>
        /// </remarks>        <short>   </short>
        ///         <see> setModifierlessAllowed</see>
        public bool IsModifierlessAllowed() {
            return (bool) interceptor.Invoke("isModifierlessAllowed", "isModifierlessAllowed()", typeof(bool));
        }
        /// <remarks>
        ///  Set whether a small button to set an empty key sequence should be displayed next to the
        ///  main input widget. The default is to show the clear button.
        /// 	 </remarks>        <short>    Set whether a small button to set an empty key sequence should be displayed next to the  main input widget.</short>
        public void SetClearButtonShown(bool show) {
            interceptor.Invoke("setClearButtonShown$", "setClearButtonShown(bool)", typeof(void), typeof(bool), show);
        }
        /// <remarks>
        ///  Return the currently selected key sequence.
        /// 	 </remarks>        <short>    Return the currently selected key sequence.</short>
        public QKeySequence KeySequence() {
            return (QKeySequence) interceptor.Invoke("keySequence", "keySequence() const", typeof(QKeySequence));
        }
        /// <remarks>
        ///  Set a list of action collections to check against for conflictuous shortcut.
        ///  If a KAction with a conflicting shortcut is found inside this list and
        ///  its shortcut can be configured (KAction.IsShortcutConfigurable()
        ///  returns true) the user will be prompted whether to steal the shortcut
        ///  from this action.
        ///  Global shortcuts are automatically checked for conflicts. For checking
        ///  against KStandardShortcuts - @see checkAgainstStandardShortcuts().
        ///  Don't forget to call applyStealShortcut to actually steal the shortcut
        ///  and read it's documentation for some limitation when handling global
        ///  shortcuts.
        /// </remarks>        <short>    Set a list of action collections to check against for conflictuous shortcut.</short>
        public void SetCheckActionCollections(List<KActionCollection> actionCollections) {
            interceptor.Invoke("setCheckActionCollections?", "setCheckActionCollections(const QList<KActionCollection*>&)", typeof(void), typeof(List<KActionCollection>), actionCollections);
        }
        /// <remarks>
        ///  Capture a shortcut from the keyboard. This call will only return once a key sequence
        ///  has been captured or input was aborted.
        ///  If a key sequence was input, keySequenceChanged() will be emitted.
        /// </remarks>        <short>    Capture a shortcut from the keyboard.</short>
        ///         <see> setModifierlessAllowed</see>
        [Q_SLOT("void captureKeySequence()")]
        public void CaptureKeySequence() {
            interceptor.Invoke("captureKeySequence", "captureKeySequence()", typeof(void));
        }
        /// <remarks>
        ///  Set the key sequence.
        ///  If <code>val</code> == Validate, and the call is actually changing the key sequence,
        ///  conflictuous shortcut will be checked.
        /// 	 </remarks>        <short>    Set the key sequence.</short>
        [Q_SLOT("void setKeySequence(QKeySequence, Validation)")]
        public void SetKeySequence(QKeySequence seq, KKeySequenceWidget.Validation val) {
            interceptor.Invoke("setKeySequence#$", "setKeySequence(const QKeySequence&, KKeySequenceWidget::Validation)", typeof(void), typeof(QKeySequence), seq, typeof(KKeySequenceWidget.Validation), val);
        }
        [Q_SLOT("void setKeySequence(QKeySequence)")]
        public void SetKeySequence(QKeySequence seq) {
            interceptor.Invoke("setKeySequence#", "setKeySequence(const QKeySequence&)", typeof(void), typeof(QKeySequence), seq);
        }
        /// <remarks>
        ///  Clear the key sequence.
        /// 	 </remarks>        <short>    Clear the key sequence.</short>
        [Q_SLOT("void clearKeySequence()")]
        public void ClearKeySequence() {
            interceptor.Invoke("clearKeySequence", "clearKeySequence()", typeof(void));
        }
        /// <remarks>
        ///  Actually remove the shortcut that the user wanted to steal, from the
        ///  action that was using it. This only applies to actions provided to us
        ///  by setCheckActionCollections() and setCheckActionList().
        ///  Global and Standard Shortcuts have to be stolen immediately when the
        ///  user gives his consent (technical reasons). That means those changes
        ///  will be active even if you never call applyStealShortcut().
        ///  To be called before you apply your changes. No local shortcuts are
        ///  stolen until this function is called.
        /// 	 </remarks>        <short>    Actually remove the shortcut that the user wanted to steal, from the  action that was using it.</short>
        [Q_SLOT("void applyStealShortcut()")]
        public void ApplyStealShortcut() {
            interceptor.Invoke("applyStealShortcut", "applyStealShortcut()", typeof(void));
        }
        ~KKeySequenceWidget() {
            interceptor.Invoke("~KKeySequenceWidget", "~KKeySequenceWidget()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KKeySequenceWidget", "~KKeySequenceWidget()", typeof(void));
        }
        protected new IKKeySequenceWidgetSignals Emit {
            get { return (IKKeySequenceWidgetSignals) Q_EMIT; }
        }
    }

    public interface IKKeySequenceWidgetSignals : IQWidgetSignals {
        /// <remarks>
        ///  This signal is emitted when the current key sequence has changed, be it by user
        ///  input or programmatically.
        /// 	 </remarks>        <short>    This signal is emitted when the current key sequence has changed, be it by user  input or programmatically.</short>
        [Q_SIGNAL("void keySequenceChanged(QKeySequence)")]
        void KeySequenceChanged(QKeySequence seq);
    }
}
