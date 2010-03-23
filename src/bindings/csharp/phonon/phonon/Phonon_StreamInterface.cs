//Auto-generated by kalyptus. DO NOT EDIT.
namespace Phonon {
    using Phonon;
    using System;
    using Qyoto;
    /// <remarks> \class StreamInterface streaminterface.h Phonon/StreamInterface
    ///  \brief Backend interface to handle media streams (AbstractMediaStream).
    ///  \author Matthias Kretz <kretz@kde.org>
    ///  </remarks>        <short>   \class StreamInterface streaminterface.</short>
    [SmokeClass("Phonon::StreamInterface")]
    public abstract class StreamInterface : Object {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected StreamInterface(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(StreamInterface), this);
        }
        /// <remarks>
        ///  Called by the application to send a chunk of (encoded) media data.
        ///  It is recommended to keep the QByteArray object until the data is consumed so that no
        ///  memcopy is needed.
        ///          </remarks>        <short>    Called by the application to send a chunk of (encoded) media data.</short>
        [SmokeMethod("writeData(const QByteArray&)")]
        public abstract void WriteData(QByteArray data);
        /// <remarks>
        ///  Called when no more media data is available and writeData will not be called anymore.
        ///          </remarks>        <short>    Called when no more media data is available and writeData will not be called anymore.</short>
        [SmokeMethod("endOfData()")]
        public abstract void EndOfData();
        /// <remarks>
        ///  Called at the start of the stream to tell how many bytes will be sent through writeData
        ///  (if no seeks happen, of course). If this value is negative the stream size cannot be
        ///  determined (might be a "theoretically infinite" stream - like webradio).
        ///          </remarks>        <short>    Called at the start of the stream to tell how many bytes will be sent through writeData  (if no seeks happen, of course).</short>
        [SmokeMethod("setStreamSize(qint64)")]
        public abstract void SetStreamSize(long newSize);
        /// <remarks>
        ///  Tells whether the stream is seekable.
        ///          </remarks>        <short>    Tells whether the stream is seekable.</short>
        [SmokeMethod("setStreamSeekable(bool)")]
        public abstract void SetStreamSeekable(bool s);
        /// <remarks>
        ///  Call this function from the constructor of your StreamInterface implementation (or as
        ///  soon as you get the MediaSource object). This will connect your object to the
        ///  AbstractMediaStream object. Only after the connection is done will the following
        ///  functions have an effect.
        ///          </remarks>        <short>    Call this function from the constructor of your StreamInterface implementation (or as  soon as you get the MediaSource object).</short>
        public void ConnectToSource(Phonon.MediaSource mediaSource) {
            interceptor.Invoke("connectToSource#", "connectToSource(const Phonon::MediaSource&)", typeof(void), typeof(Phonon.MediaSource), mediaSource);
        }
        /// <remarks>
        ///  Call this function to tell the AbstractMediaStream that you need more data. The data will
        ///  arrive through writeData. Don't rely on writeData getting called from needData, though
        ///  some AbstractMediaStream implementations might do so.
        ///  Depending on the buffering you need you either treat needData as a replacement for a
        ///  read call like QIODevice.Read, or you start calling needData whenever your buffer
        ///  reaches a certain lower threshold.
        ///          </remarks>        <short>    Call this function to tell the AbstractMediaStream that you need more data.</short>
        public void NeedData() {
            interceptor.Invoke("needData", "needData()", typeof(void));
        }
        /// <remarks>
        ///  Call this function to tell the AbstractMediaStream that you have enough data in your
        ///  buffer and that it should pause calling writeData if possible.
        ///          </remarks>        <short>    Call this function to tell the AbstractMediaStream that you have enough data in your  buffer and that it should pause calling writeData if possible.</short>
        public void EnoughData() {
            interceptor.Invoke("enoughData", "enoughData()", typeof(void));
        }
        /// <remarks>
        ///  If the stream is seekable, calling this function will make the next call to writeData
        ///  pass data that starts at the byte offset <pre>seekTo</pre>.
        ///          </remarks>        <short>    If the stream is seekable, calling this function will make the next call to writeData  pass data that starts at the byte offset \p seekTo.</short>
        public void SeekStream(long seekTo) {
            interceptor.Invoke("seekStream$", "seekStream(qint64)", typeof(void), typeof(long), seekTo);
        }
        /// <remarks>
        ///  Resets the AbstractMediaStream. E.g. this can be useful for non-seekable streams to start
        ///  over again.
        ///          </remarks>        <short>    Resets the AbstractMediaStream.</short>
        public void Reset() {
            interceptor.Invoke("reset", "reset()", typeof(void));
        }
        public StreamInterface() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("StreamInterface", "StreamInterface()", typeof(void));
        }
    }
}
