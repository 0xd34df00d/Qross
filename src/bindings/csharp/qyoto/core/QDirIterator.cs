//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Collections.Generic;
    [SmokeClass("QDirIterator")]
    public class QDirIterator : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QDirIterator(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QDirIterator), this);
        }
        public enum IteratorFlag {
            NoIteratorFlags = 0x0,
            FollowSymlinks = 0x1,
            Subdirectories = 0x2,
        }
        public QDirIterator(QDir dir, uint flags) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator#$", "QDirIterator(const QDir&, QDirIterator::IteratorFlags)", typeof(void), typeof(QDir), dir, typeof(uint), flags);
        }
        public QDirIterator(QDir dir) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator#", "QDirIterator(const QDir&)", typeof(void), typeof(QDir), dir);
        }
        public QDirIterator(string path, uint flags) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$$", "QDirIterator(const QString&, QDirIterator::IteratorFlags)", typeof(void), typeof(string), path, typeof(uint), flags);
        }
        public QDirIterator(string path) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$", "QDirIterator(const QString&)", typeof(void), typeof(string), path);
        }
        public QDirIterator(string path, uint filter, uint flags) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$$$", "QDirIterator(const QString&, QDir::Filters, QDirIterator::IteratorFlags)", typeof(void), typeof(string), path, typeof(uint), filter, typeof(uint), flags);
        }
        public QDirIterator(string path, List<string> nameFilters, uint filters, uint flags) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$?$$", "QDirIterator(const QString&, const QStringList&, QDir::Filters, QDirIterator::IteratorFlags)", typeof(void), typeof(string), path, typeof(List<string>), nameFilters, typeof(uint), filters, typeof(uint), flags);
        }
        public QDirIterator(string path, List<string> nameFilters, uint filters) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$?$", "QDirIterator(const QString&, const QStringList&, QDir::Filters)", typeof(void), typeof(string), path, typeof(List<string>), nameFilters, typeof(uint), filters);
        }
        public QDirIterator(string path, List<string> nameFilters) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QDirIterator$?", "QDirIterator(const QString&, const QStringList&)", typeof(void), typeof(string), path, typeof(List<string>), nameFilters);
        }
        public string Next() {
            return (string) interceptor.Invoke("next", "next()", typeof(string));
        }
        public bool HasNext() {
            return (bool) interceptor.Invoke("hasNext", "hasNext() const", typeof(bool));
        }
        public string FileName() {
            return (string) interceptor.Invoke("fileName", "fileName() const", typeof(string));
        }
        public string FilePath() {
            return (string) interceptor.Invoke("filePath", "filePath() const", typeof(string));
        }
        public QFileInfo FileInfo() {
            return (QFileInfo) interceptor.Invoke("fileInfo", "fileInfo() const", typeof(QFileInfo));
        }
        public string Path() {
            return (string) interceptor.Invoke("path", "path() const", typeof(string));
        }
        ~QDirIterator() {
            interceptor.Invoke("~QDirIterator", "~QDirIterator()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QDirIterator", "~QDirIterator()", typeof(void));
        }
    }
}
