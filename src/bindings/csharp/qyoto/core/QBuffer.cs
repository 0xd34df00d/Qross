//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QBuffer")]
    public class QBuffer : QIODevice, IDisposable {
        protected QBuffer(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QBuffer), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QBuffer() {
            staticInterceptor = new SmokeInvocation(typeof(QBuffer), null);
        }
        public QBuffer(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QBuffer#", "QBuffer(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public QBuffer() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QBuffer", "QBuffer()", typeof(void));
        }
        public QBuffer(QByteArray buf, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QBuffer##", "QBuffer(QByteArray*, QObject*)", typeof(void), typeof(QByteArray), buf, typeof(QObject), parent);
        }
        public QBuffer(QByteArray buf) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QBuffer#", "QBuffer(QByteArray*)", typeof(void), typeof(QByteArray), buf);
        }
        public QByteArray Buffer() {
            return (QByteArray) interceptor.Invoke("buffer", "buffer()", typeof(QByteArray));
        }
        public void SetBuffer(QByteArray a) {
            interceptor.Invoke("setBuffer#", "setBuffer(QByteArray*)", typeof(void), typeof(QByteArray), a);
        }
        public void SetData(QByteArray data) {
            interceptor.Invoke("setData#", "setData(const QByteArray&)", typeof(void), typeof(QByteArray), data);
        }
        public void SetData(string data, int len) {
            interceptor.Invoke("setData$$", "setData(const char*, int)", typeof(void), typeof(string), data, typeof(int), len);
        }
        public QByteArray Data() {
            return (QByteArray) interceptor.Invoke("data", "data() const", typeof(QByteArray));
        }
        [SmokeMethod("open(QIODevice::OpenMode)")]
        public override bool Open(uint openMode) {
            return (bool) interceptor.Invoke("open$", "open(QIODevice::OpenMode)", typeof(bool), typeof(uint), openMode);
        }
        [SmokeMethod("close()")]
        public override void Close() {
            interceptor.Invoke("close", "close()", typeof(void));
        }
        [SmokeMethod("size() const")]
        public override long Size() {
            return (long) interceptor.Invoke("size", "size() const", typeof(long));
        }
        [SmokeMethod("pos() const")]
        public override long Pos() {
            return (long) interceptor.Invoke("pos", "pos() const", typeof(long));
        }
        [SmokeMethod("seek(qint64)")]
        public override bool Seek(long off) {
            return (bool) interceptor.Invoke("seek$", "seek(qint64)", typeof(bool), typeof(long), off);
        }
        [SmokeMethod("atEnd() const")]
        public override bool AtEnd() {
            return (bool) interceptor.Invoke("atEnd", "atEnd() const", typeof(bool));
        }
        [SmokeMethod("canReadLine() const")]
        public override bool CanReadLine() {
            return (bool) interceptor.Invoke("canReadLine", "canReadLine() const", typeof(bool));
        }
        [SmokeMethod("connectNotify(const char*)")]
        protected override void ConnectNotify(string arg1) {
            interceptor.Invoke("connectNotify$", "connectNotify(const char*)", typeof(void), typeof(string), arg1);
        }
        [SmokeMethod("disconnectNotify(const char*)")]
        protected override void DisconnectNotify(string arg1) {
            interceptor.Invoke("disconnectNotify$", "disconnectNotify(const char*)", typeof(void), typeof(string), arg1);
        }
        [SmokeMethod("readData(char*, qint64)")]
        protected override long ReadData(Pointer<sbyte> data, long maxlen) {
            return (long) interceptor.Invoke("readData$$", "readData(char*, qint64)", typeof(long), typeof(Pointer<sbyte>), data, typeof(long), maxlen);
        }
        [SmokeMethod("writeData(const char*, qint64)")]
        protected override long WriteData(string data, long len) {
            return (long) interceptor.Invoke("writeData$$", "writeData(const char*, qint64)", typeof(long), typeof(string), data, typeof(long), len);
        }
        ~QBuffer() {
            interceptor.Invoke("~QBuffer", "~QBuffer()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~QBuffer", "~QBuffer()", typeof(void));
        }
        public static new string Tr(string s, string c) {
            return (string) staticInterceptor.Invoke("tr$$", "tr(const char*, const char*)", typeof(string), typeof(string), s, typeof(string), c);
        }
        public static new string Tr(string s) {
            return (string) staticInterceptor.Invoke("tr$", "tr(const char*)", typeof(string), typeof(string), s);
        }
        protected new IQBufferSignals Emit {
            get { return (IQBufferSignals) Q_EMIT; }
        }
    }

    public interface IQBufferSignals : IQIODeviceSignals {
    }
}
