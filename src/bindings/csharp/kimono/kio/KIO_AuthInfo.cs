//Auto-generated by kalyptus. DO NOT EDIT.
namespace KIO {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///  This class is intended to make it easier to prompt for, cache
    ///  and retrieve authorization information.
    ///  When using this class to cache, retrieve or prompt authentication
    ///  information, you only need to set the necessary attributes. For
    ///  example, to check whether a password is already cached, the only
    ///  required information is the URL of the resource and optionally
    ///  whether or not a path match should be performed.  Similarly, to
    ///  prompt for password you only need to optionally set the prompt,
    ///  username (if already supplied), comment and commentLabel fields.
    ///  <em>SPECIAL NOTE:</em> If you extend this class to add additional
    ///  parameters do not forget to overload the stream insertion and
    ///  extraction operators ("<<" and ">>") so that the added data can
    ///  be correctly serialzed.
    /// </remarks>        <author> Dawit Alemayehu <adawit@kde.org>
    ///  </author>
    ///         <short> A two way messaging class for passing authentication information. </short>
    [SmokeClass("KIO::AuthInfo")]
    public class AuthInfo : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected AuthInfo(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(AuthInfo), this);
        }
        /// <remarks>
        ///  Flags for extra fields
        /// </remarks>        <short>    Flags for extra fields </short>
        public enum FieldFlags {
            ExtraFieldNoFlags = 0,
            ExtraFieldReadOnly = 1<<1,
            ExtraFieldMandatory = 1<<2,
        }
        public KUrl Url {
            get { return (KUrl) interceptor.Invoke("url", "url()", typeof(KUrl)); }
            set { interceptor.Invoke("setUrl#", "setUrl(KUrl)", typeof(void), typeof(KUrl), value); }
        }
        public string Username {
            get { return (string) interceptor.Invoke("username", "username()", typeof(string)); }
            set { interceptor.Invoke("setUsername$", "setUsername(QString)", typeof(void), typeof(string), value); }
        }
        public string Password {
            get { return (string) interceptor.Invoke("password", "password()", typeof(string)); }
            set { interceptor.Invoke("setPassword$", "setPassword(QString)", typeof(void), typeof(string), value); }
        }
        public string Prompt {
            get { return (string) interceptor.Invoke("prompt", "prompt()", typeof(string)); }
            set { interceptor.Invoke("setPrompt$", "setPrompt(QString)", typeof(void), typeof(string), value); }
        }
        public string Caption {
            get { return (string) interceptor.Invoke("caption", "caption()", typeof(string)); }
            set { interceptor.Invoke("setCaption$", "setCaption(QString)", typeof(void), typeof(string), value); }
        }
        public string Comment {
            get { return (string) interceptor.Invoke("comment", "comment()", typeof(string)); }
            set { interceptor.Invoke("setComment$", "setComment(QString)", typeof(void), typeof(string), value); }
        }
        public string CommentLabel {
            get { return (string) interceptor.Invoke("commentLabel", "commentLabel()", typeof(string)); }
            set { interceptor.Invoke("setCommentLabel$", "setCommentLabel(QString)", typeof(void), typeof(string), value); }
        }
        public string RealmValue {
            get { return (string) interceptor.Invoke("realmValue", "realmValue()", typeof(string)); }
            set { interceptor.Invoke("setRealmValue$", "setRealmValue(QString)", typeof(void), typeof(string), value); }
        }
        public string DigestInfo {
            get { return (string) interceptor.Invoke("digestInfo", "digestInfo()", typeof(string)); }
            set { interceptor.Invoke("setDigestInfo$", "setDigestInfo(QString)", typeof(void), typeof(string), value); }
        }
        public bool VerifyPath {
            get { return (bool) interceptor.Invoke("verifyPath", "verifyPath()", typeof(bool)); }
            set { interceptor.Invoke("setVerifyPath$", "setVerifyPath(bool)", typeof(void), typeof(bool), value); }
        }
        public bool ReadOnly {
            get { return (bool) interceptor.Invoke("readOnly", "readOnly()", typeof(bool)); }
            set { interceptor.Invoke("setReadOnly$", "setReadOnly(bool)", typeof(void), typeof(bool), value); }
        }
        public bool KeepPassword {
            get { return (bool) interceptor.Invoke("keepPassword", "keepPassword()", typeof(bool)); }
            set { interceptor.Invoke("setKeepPassword$", "setKeepPassword(bool)", typeof(void), typeof(bool), value); }
        }
        /// <remarks>
        ///  Default constructor.
        ///     </remarks>        <short>    Default constructor.</short>
        public AuthInfo() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("AuthInfo", "AuthInfo()", typeof(void));
        }
        /// <remarks>
        ///  Copy constructor.
        ///     </remarks>        <short>    Copy constructor.</short>
        public AuthInfo(KIO.AuthInfo info) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("AuthInfo#", "AuthInfo(const KIO::AuthInfo&)", typeof(void), typeof(KIO.AuthInfo), info);
        }
        /// <remarks>
        ///  Use this method to check if the object was modified.
        /// </remarks>        <return> true if the object has been modified
        ///     </return>
        ///         <short>    Use this method to check if the object was modified.</short>
        public bool IsModified() {
            return (bool) interceptor.Invoke("isModified", "isModified() const", typeof(bool));
        }
        /// <remarks>
        ///  Use this method to indicate that this object has been modified.
        /// <param> name="flag" true to mark the object as modified, false to clear
        ///     </param></remarks>        <short>    Use this method to indicate that this object has been modified.</short>
        public void SetModified(bool flag) {
            interceptor.Invoke("setModified$", "setModified(bool)", typeof(void), typeof(bool), flag);
        }
        /// <remarks>
        ///  Set Extra Field Value. 
        ///  Currently supported extra-fields: 
        ///     "domain" (string), 
        ///     "anonymous" (bool)
        ///  Setting it to an invalid QVariant() will disable the field.
        ///  Extra Fields are disabled by default.
        /// </remarks>        <short>    Set Extra Field Value.</short>
        public void SetExtraField(string fieldName, QVariant value) {
            interceptor.Invoke("setExtraField$#", "setExtraField(const QString&, const QVariant&)", typeof(void), typeof(string), fieldName, typeof(QVariant), value);
        }
        /// <remarks>
        ///  Set Extra Field Flags
        /// </remarks>        <short>    Set Extra Field Flags </short>
        public void SetExtraFieldFlags(string fieldName, KIO.AuthInfo.FieldFlags flags) {
            interceptor.Invoke("setExtraFieldFlags$$", "setExtraFieldFlags(const QString&, const KIO::AuthInfo::FieldFlags)", typeof(void), typeof(string), fieldName, typeof(KIO.AuthInfo.FieldFlags), flags);
        }
        /// <remarks>
        ///  Get Extra Field Value
        ///  Check QVariant.IsValid() to find out if the field exists.
        /// </remarks>        <short>    Get Extra Field Value  Check QVariant.IsValid() to find out if the field exists.</short>
        public QVariant GetExtraField(string fieldName) {
            return (QVariant) interceptor.Invoke("getExtraField$", "getExtraField(const QString&) const", typeof(QVariant), typeof(string), fieldName);
        }
        /// <remarks>
        ///  Get Extra Field Flags
        /// </remarks>        <short>    Get Extra Field Flags </short>
        public KIO.AuthInfo.FieldFlags GetExtraFieldFlags(string fieldName) {
            return (KIO.AuthInfo.FieldFlags) interceptor.Invoke("getExtraFieldFlags$", "getExtraFieldFlags(const QString&) const", typeof(KIO.AuthInfo.FieldFlags), typeof(string), fieldName);
        }
        ~AuthInfo() {
            interceptor.Invoke("~AuthInfo", "~AuthInfo()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~AuthInfo", "~AuthInfo()", typeof(void));
        }
    }
}
