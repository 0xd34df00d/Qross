//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  List of KFileItems, which adds a few helper
    ///  methods to QList<KFileItem>.
    ///  </remarks>        <short>    List of KFileItems, which adds a few helper  methods to QList<KFileItem>.</short>
    [SmokeClass("KFileItemList")]
    public class KFileItemList : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected KFileItemList(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KFileItemList), this);
        }
        public KFileItemList() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFileItemList", "KFileItemList()", typeof(void));
        }
        public KFileItemList(List<KFileItem> items) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KFileItemList?", "KFileItemList(const QList<KFileItem>&)", typeof(void), typeof(List<KFileItem>), items);
        }
        /// <remarks>
        ///  Find a KFileItem by name and return it.
        /// </remarks>        <return> the item with the given name, or a null-item if none was found
        ///          (see KFileItem.IsNull())
        ///    </return>
        ///         <short>    Find a KFileItem by name and return it.</short>
        public KFileItem FindByName(string fileName) {
            return (KFileItem) interceptor.Invoke("findByName$", "findByName(const QString&) const", typeof(KFileItem), typeof(string), fileName);
        }
        /// <remarks>
        ///  Find a KFileItem by URL and return it.
        /// </remarks>        <return> the item with the given URL, or a null-item if none was found
        ///          (see KFileItem.IsNull())
        ///    </return>
        ///         <short>    Find a KFileItem by URL and return it.</short>
        public KFileItem FindByUrl(KUrl url) {
            return (KFileItem) interceptor.Invoke("findByUrl#", "findByUrl(const KUrl&) const", typeof(KFileItem), typeof(KUrl), url);
        }
        public List<KUrl> UrlList() {
            return (List<KUrl>) interceptor.Invoke("urlList", "urlList() const", typeof(List<KUrl>));
        }
        ~KFileItemList() {
            interceptor.Invoke("~KFileItemList", "~KFileItemList()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~KFileItemList", "~KFileItemList()", typeof(void));
        }
    }
}
