//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Collections.Generic;
    /// <remarks> See <see cref="IQNetworkAccessManagerSignals"></see> for signals emitted by QNetworkAccessManager
    /// </remarks>
    [SmokeClass("QNetworkAccessManager")]
    public class QNetworkAccessManager : QObject, IDisposable {
        protected QNetworkAccessManager(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QNetworkAccessManager), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QNetworkAccessManager() {
            staticInterceptor = new SmokeInvocation(typeof(QNetworkAccessManager), null);
        }
        public enum Operation {
            HeadOperation = 1,
            GetOperation = 2,
            PutOperation = 3,
            PostOperation = 4,
            DeleteOperation = 5,
            UnknownOperation = 0,
        }
        public QNetworkAccessManager(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QNetworkAccessManager#", "QNetworkAccessManager(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QNetworkAccessManager() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QNetworkAccessManager", "QNetworkAccessManager()", typeof(void));
        }
        public QNetworkProxy Proxy() {
            return (QNetworkProxy) interceptor.Invoke("proxy", "proxy() const", typeof(QNetworkProxy));
        }
        public void SetProxy(QNetworkProxy proxy) {
            interceptor.Invoke("setProxy#", "setProxy(const QNetworkProxy&)", typeof(void), typeof(QNetworkProxy), proxy);
        }
        public QNetworkProxyFactory ProxyFactory() {
            return (QNetworkProxyFactory) interceptor.Invoke("proxyFactory", "proxyFactory() const", typeof(QNetworkProxyFactory));
        }
        public void SetProxyFactory(QNetworkProxyFactory factory) {
            interceptor.Invoke("setProxyFactory#", "setProxyFactory(QNetworkProxyFactory*)", typeof(void), typeof(QNetworkProxyFactory), factory);
        }
        public QAbstractNetworkCache Cache() {
            return (QAbstractNetworkCache) interceptor.Invoke("cache", "cache() const", typeof(QAbstractNetworkCache));
        }
        public void SetCache(QAbstractNetworkCache cache) {
            interceptor.Invoke("setCache#", "setCache(QAbstractNetworkCache*)", typeof(void), typeof(QAbstractNetworkCache), cache);
        }
        public QNetworkCookieJar CookieJar() {
            return (QNetworkCookieJar) interceptor.Invoke("cookieJar", "cookieJar() const", typeof(QNetworkCookieJar));
        }
        public void SetCookieJar(QNetworkCookieJar cookieJar) {
            interceptor.Invoke("setCookieJar#", "setCookieJar(QNetworkCookieJar*)", typeof(void), typeof(QNetworkCookieJar), cookieJar);
        }
        public QNetworkReply Head(QNetworkRequest request) {
            return (QNetworkReply) interceptor.Invoke("head#", "head(const QNetworkRequest&)", typeof(QNetworkReply), typeof(QNetworkRequest), request);
        }
        public QNetworkReply Get(QNetworkRequest request) {
            return (QNetworkReply) interceptor.Invoke("get#", "get(const QNetworkRequest&)", typeof(QNetworkReply), typeof(QNetworkRequest), request);
        }
        public QNetworkReply Post(QNetworkRequest request, QIODevice data) {
            return (QNetworkReply) interceptor.Invoke("post##", "post(const QNetworkRequest&, QIODevice*)", typeof(QNetworkReply), typeof(QNetworkRequest), request, typeof(QIODevice), data);
        }
        public QNetworkReply Post(QNetworkRequest request, QByteArray data) {
            return (QNetworkReply) interceptor.Invoke("post##", "post(const QNetworkRequest&, const QByteArray&)", typeof(QNetworkReply), typeof(QNetworkRequest), request, typeof(QByteArray), data);
        }
        public QNetworkReply Put(QNetworkRequest request, QIODevice data) {
            return (QNetworkReply) interceptor.Invoke("put##", "put(const QNetworkRequest&, QIODevice*)", typeof(QNetworkReply), typeof(QNetworkRequest), request, typeof(QIODevice), data);
        }
        public QNetworkReply Put(QNetworkRequest request, QByteArray data) {
            return (QNetworkReply) interceptor.Invoke("put##", "put(const QNetworkRequest&, const QByteArray&)", typeof(QNetworkReply), typeof(QNetworkRequest), request, typeof(QByteArray), data);
        }
        public QNetworkReply DeleteResource(QNetworkRequest request) {
            return (QNetworkReply) interceptor.Invoke("deleteResource#", "deleteResource(const QNetworkRequest&)", typeof(QNetworkReply), typeof(QNetworkRequest), request);
        }
        [SmokeMethod("createRequest(QNetworkAccessManager::Operation, const QNetworkRequest&, QIODevice*)")]
        protected virtual QNetworkReply CreateRequest(QNetworkAccessManager.Operation op, QNetworkRequest request, QIODevice outgoingData) {
            return (QNetworkReply) interceptor.Invoke("createRequest$##", "createRequest(QNetworkAccessManager::Operation, const QNetworkRequest&, QIODevice*)", typeof(QNetworkReply), typeof(QNetworkAccessManager.Operation), op, typeof(QNetworkRequest), request, typeof(QIODevice), outgoingData);
        }
        [SmokeMethod("createRequest(QNetworkAccessManager::Operation, const QNetworkRequest&)")]
        protected virtual QNetworkReply CreateRequest(QNetworkAccessManager.Operation op, QNetworkRequest request) {
            return (QNetworkReply) interceptor.Invoke("createRequest$#", "createRequest(QNetworkAccessManager::Operation, const QNetworkRequest&)", typeof(QNetworkReply), typeof(QNetworkAccessManager.Operation), op, typeof(QNetworkRequest), request);
        }
        ~QNetworkAccessManager() {
            interceptor.Invoke("~QNetworkAccessManager", "~QNetworkAccessManager()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QNetworkAccessManager", "~QNetworkAccessManager()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQNetworkAccessManagerSignals Emit {
            get { return (IQNetworkAccessManagerSignals) Q_EMIT; }
        }
    }

    public interface IQNetworkAccessManagerSignals : IQObjectSignals {
        [Q_SIGNAL("void proxyAuthenticationRequired(QNetworkProxy, QAuthenticator*)")]
        void ProxyAuthenticationRequired(QNetworkProxy proxy, QAuthenticator authenticator);
        [Q_SIGNAL("void authenticationRequired(QNetworkReply*, QAuthenticator*)")]
        void AuthenticationRequired(QNetworkReply reply, QAuthenticator authenticator);
        [Q_SIGNAL("void finished(QNetworkReply*)")]
        void Finished(QNetworkReply reply);
        [Q_SIGNAL("void sslErrors(QNetworkReply*, QList<QSslError>)")]
        void SslErrors(QNetworkReply reply, List<QSslError> errors);
    }
}
