//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  A class for reading / writing (optionally compressed) tar archives.
    ///  KTar allows you to read and write tar archives, including those
    ///  that are compressed using gzip or bzip2.
    /// </remarks>        <author> Torben Weis <weis@kde.org>, David Faure <faure@kde.org>
    ///  </author>
    ///         <short>    A class for reading / writing (optionally compressed) tar archives.</short>
    [SmokeClass("KTar")]
    public class KTar : KArchive, IDisposable {
        protected KTar(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KTar), this);
        }
        /// <remarks>
        ///  Creates an instance that operates on the given filename
        ///  using the compression filter associated to given mimetype.
        /// <param> name="filename" is a local path (e.g. "/home/weis/myfile.tgz")
        /// </param><param> name="mimetype" "application/x-gzip" or "application/x-bzip"
        ///  Do not use application/x-compressed-tar or similar - you only need to
        ///  specify the compression layer !  If the mimetype is omitted, it
        ///  will be determined from the filename.
        ///      </param></remarks>        <short>    Creates an instance that operates on the given filename  using the compression filter associated to given mimetype.</short>
        public KTar(string filename, string mimetype) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KTar$$", "KTar(const QString&, const QString&)", typeof(void), typeof(string), filename, typeof(string), mimetype);
        }
        public KTar(string filename) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KTar$", "KTar(const QString&)", typeof(void), typeof(string), filename);
        }
        /// <remarks>
        ///  Creates an instance that operates on the given device.
        ///  The device can be compressed (KFilterDev) or not (QFile, etc.).
        ///  @warning Do not assume that giving a QFile here will decompress the file,
        ///  in case it's compressed!
        /// <param> name="dev" the device to read from. If the source is compressed, the
        ///  QIODevice must take care of decompression
        ///      </param></remarks>        <short>    Creates an instance that operates on the given device.</short>
        public KTar(QIODevice dev) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KTar#", "KTar(QIODevice*)", typeof(void), typeof(QIODevice), dev);
        }
        /// <remarks>
        ///  Special function for setting the "original file name" in the gzip header,
        ///  when writing a tar.gz file. It appears when using in the "file" command,
        ///  for instance. Should only be called if the underlying device is a KFilterDev!
        /// <param> name="fileName" the original file name
        ///      </param></remarks>        <short>    Special function for setting the "original file name" in the gzip header,  when writing a tar.</short>
        public void SetOrigFileName(QByteArray fileName) {
            interceptor.Invoke("setOrigFileName#", "setOrigFileName(const QByteArray&)", typeof(void), typeof(QByteArray), fileName);
        }
        [SmokeMethod("doWriteSymLink(const QString&, const QString&, const QString&, const QString&, mode_t, time_t, time_t, time_t)")]
        protected override bool DoWriteSymLink(string name, string target, string user, string group, long perm, int atime, int mtime, int ctime) {
            return (bool) interceptor.Invoke("doWriteSymLink$$$$$$$$", "doWriteSymLink(const QString&, const QString&, const QString&, const QString&, mode_t, time_t, time_t, time_t)", typeof(bool), typeof(string), name, typeof(string), target, typeof(string), user, typeof(string), group, typeof(long), perm, typeof(int), atime, typeof(int), mtime, typeof(int), ctime);
        }
        [SmokeMethod("doWriteDir(const QString&, const QString&, const QString&, mode_t, time_t, time_t, time_t)")]
        protected override bool DoWriteDir(string name, string user, string group, long perm, int atime, int mtime, int ctime) {
            return (bool) interceptor.Invoke("doWriteDir$$$$$$$", "doWriteDir(const QString&, const QString&, const QString&, mode_t, time_t, time_t, time_t)", typeof(bool), typeof(string), name, typeof(string), user, typeof(string), group, typeof(long), perm, typeof(int), atime, typeof(int), mtime, typeof(int), ctime);
        }
        [SmokeMethod("doPrepareWriting(const QString&, const QString&, const QString&, qint64, mode_t, time_t, time_t, time_t)")]
        protected override bool DoPrepareWriting(string name, string user, string group, long size, long perm, int atime, int mtime, int ctime) {
            return (bool) interceptor.Invoke("doPrepareWriting$$$$$$$$", "doPrepareWriting(const QString&, const QString&, const QString&, qint64, mode_t, time_t, time_t, time_t)", typeof(bool), typeof(string), name, typeof(string), user, typeof(string), group, typeof(long), size, typeof(long), perm, typeof(int), atime, typeof(int), mtime, typeof(int), ctime);
        }
        [SmokeMethod("doFinishWriting(qint64)")]
        protected override bool DoFinishWriting(long size) {
            return (bool) interceptor.Invoke("doFinishWriting$", "doFinishWriting(qint64)", typeof(bool), typeof(long), size);
        }
        /// <remarks>
        ///  Opens the archive for reading.
        ///  Parses the directory listing of the archive
        ///  and creates the KArchiveDirectory/KArchiveFile entries.
        /// <param> name="mode" the mode of the file
        ///      </param></remarks>        <short>    Opens the archive for reading.</short>
        [SmokeMethod("openArchive(QIODevice::OpenMode)")]
        protected override bool OpenArchive(uint mode) {
            return (bool) interceptor.Invoke("openArchive$", "openArchive(QIODevice::OpenMode)", typeof(bool), typeof(uint), mode);
        }
        [SmokeMethod("closeArchive()")]
        protected override bool CloseArchive() {
            return (bool) interceptor.Invoke("closeArchive", "closeArchive()", typeof(bool));
        }
        [SmokeMethod("createDevice(QIODevice::OpenMode)")]
        protected override bool CreateDevice(uint mode) {
            return (bool) interceptor.Invoke("createDevice$", "createDevice(QIODevice::OpenMode)", typeof(bool), typeof(uint), mode);
        }
        ~KTar() {
            interceptor.Invoke("~KTar", "~KTar()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~KTar", "~KTar()", typeof(void));
        }
    }
}
