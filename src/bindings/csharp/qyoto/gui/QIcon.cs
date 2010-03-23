//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Collections.Generic;
    [SmokeClass("QIcon")]
    public partial class QIcon : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QIcon(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QIcon), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QIcon() {
            staticInterceptor = new SmokeInvocation(typeof(QIcon), null);
        }
        public enum Mode {
            Normal = 0,
            Disabled = 1,
            Active = 2,
            Selected = 3,
        }
        public enum State {
            On = 0,
            Off = 1,
        }
        // QIconPrivate*& data_ptr(); >>>> NOT CONVERTED
        public QIcon() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon", "QIcon()", typeof(void));
        }
        public QIcon(QPixmap pixmap) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon#", "QIcon(const QPixmap&)", typeof(void), typeof(QPixmap), pixmap);
        }
        public QIcon(QIcon other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon#", "QIcon(const QIcon&)", typeof(void), typeof(QIcon), other);
        }
        public QIcon(string fileName) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon$", "QIcon(const QString&)", typeof(void), typeof(string), fileName);
        }
        public QIcon(QIconEngine engine) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon#", "QIcon(QIconEngine*)", typeof(void), typeof(QIconEngine), engine);
        }
        public QIcon(QIconEngineV2 engine) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QIcon#", "QIcon(QIconEngineV2*)", typeof(void), typeof(QIconEngineV2), engine);
        }
        public QPixmap Pixmap(QSize size, QIcon.Mode mode, QIcon.State state) {
            return (QPixmap) interceptor.Invoke("pixmap#$$", "pixmap(const QSize&, QIcon::Mode, QIcon::State) const", typeof(QPixmap), typeof(QSize), size, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public QPixmap Pixmap(QSize size, QIcon.Mode mode) {
            return (QPixmap) interceptor.Invoke("pixmap#$", "pixmap(const QSize&, QIcon::Mode) const", typeof(QPixmap), typeof(QSize), size, typeof(QIcon.Mode), mode);
        }
        public QPixmap Pixmap(QSize size) {
            return (QPixmap) interceptor.Invoke("pixmap#", "pixmap(const QSize&) const", typeof(QPixmap), typeof(QSize), size);
        }
        public QPixmap Pixmap(int w, int h, QIcon.Mode mode, QIcon.State state) {
            return (QPixmap) interceptor.Invoke("pixmap$$$$", "pixmap(int, int, QIcon::Mode, QIcon::State) const", typeof(QPixmap), typeof(int), w, typeof(int), h, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public QPixmap Pixmap(int w, int h, QIcon.Mode mode) {
            return (QPixmap) interceptor.Invoke("pixmap$$$", "pixmap(int, int, QIcon::Mode) const", typeof(QPixmap), typeof(int), w, typeof(int), h, typeof(QIcon.Mode), mode);
        }
        public QPixmap Pixmap(int w, int h) {
            return (QPixmap) interceptor.Invoke("pixmap$$", "pixmap(int, int) const", typeof(QPixmap), typeof(int), w, typeof(int), h);
        }
        public QPixmap Pixmap(int extent, QIcon.Mode mode, QIcon.State state) {
            return (QPixmap) interceptor.Invoke("pixmap$$$", "pixmap(int, QIcon::Mode, QIcon::State) const", typeof(QPixmap), typeof(int), extent, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public QPixmap Pixmap(int extent, QIcon.Mode mode) {
            return (QPixmap) interceptor.Invoke("pixmap$$", "pixmap(int, QIcon::Mode) const", typeof(QPixmap), typeof(int), extent, typeof(QIcon.Mode), mode);
        }
        public QPixmap Pixmap(int extent) {
            return (QPixmap) interceptor.Invoke("pixmap$", "pixmap(int) const", typeof(QPixmap), typeof(int), extent);
        }
        public QSize ActualSize(QSize size, QIcon.Mode mode, QIcon.State state) {
            return (QSize) interceptor.Invoke("actualSize#$$", "actualSize(const QSize&, QIcon::Mode, QIcon::State) const", typeof(QSize), typeof(QSize), size, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public QSize ActualSize(QSize size, QIcon.Mode mode) {
            return (QSize) interceptor.Invoke("actualSize#$", "actualSize(const QSize&, QIcon::Mode) const", typeof(QSize), typeof(QSize), size, typeof(QIcon.Mode), mode);
        }
        public QSize ActualSize(QSize size) {
            return (QSize) interceptor.Invoke("actualSize#", "actualSize(const QSize&) const", typeof(QSize), typeof(QSize), size);
        }
        public void Paint(QPainter painter, QRect rect, uint alignment, QIcon.Mode mode, QIcon.State state) {
            interceptor.Invoke("paint##$$$", "paint(QPainter*, const QRect&, Qt::Alignment, QIcon::Mode, QIcon::State) const", typeof(void), typeof(QPainter), painter, typeof(QRect), rect, typeof(uint), alignment, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public void Paint(QPainter painter, QRect rect, uint alignment, QIcon.Mode mode) {
            interceptor.Invoke("paint##$$", "paint(QPainter*, const QRect&, Qt::Alignment, QIcon::Mode) const", typeof(void), typeof(QPainter), painter, typeof(QRect), rect, typeof(uint), alignment, typeof(QIcon.Mode), mode);
        }
        public void Paint(QPainter painter, QRect rect, uint alignment) {
            interceptor.Invoke("paint##$", "paint(QPainter*, const QRect&, Qt::Alignment) const", typeof(void), typeof(QPainter), painter, typeof(QRect), rect, typeof(uint), alignment);
        }
        public void Paint(QPainter painter, QRect rect) {
            interceptor.Invoke("paint##", "paint(QPainter*, const QRect&) const", typeof(void), typeof(QPainter), painter, typeof(QRect), rect);
        }
        public void Paint(QPainter painter, int x, int y, int w, int h, uint alignment, QIcon.Mode mode, QIcon.State state) {
            interceptor.Invoke("paint#$$$$$$$", "paint(QPainter*, int, int, int, int, Qt::Alignment, QIcon::Mode, QIcon::State) const", typeof(void), typeof(QPainter), painter, typeof(int), x, typeof(int), y, typeof(int), w, typeof(int), h, typeof(uint), alignment, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public void Paint(QPainter painter, int x, int y, int w, int h, uint alignment, QIcon.Mode mode) {
            interceptor.Invoke("paint#$$$$$$", "paint(QPainter*, int, int, int, int, Qt::Alignment, QIcon::Mode) const", typeof(void), typeof(QPainter), painter, typeof(int), x, typeof(int), y, typeof(int), w, typeof(int), h, typeof(uint), alignment, typeof(QIcon.Mode), mode);
        }
        public void Paint(QPainter painter, int x, int y, int w, int h, uint alignment) {
            interceptor.Invoke("paint#$$$$$", "paint(QPainter*, int, int, int, int, Qt::Alignment) const", typeof(void), typeof(QPainter), painter, typeof(int), x, typeof(int), y, typeof(int), w, typeof(int), h, typeof(uint), alignment);
        }
        public void Paint(QPainter painter, int x, int y, int w, int h) {
            interceptor.Invoke("paint#$$$$", "paint(QPainter*, int, int, int, int) const", typeof(void), typeof(QPainter), painter, typeof(int), x, typeof(int), y, typeof(int), w, typeof(int), h);
        }
        public bool IsNull() {
            return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
        }
        public bool IsDetached() {
            return (bool) interceptor.Invoke("isDetached", "isDetached() const", typeof(bool));
        }
        public void Detach() {
            interceptor.Invoke("detach", "detach()", typeof(void));
        }
        public int SerialNumber() {
            return (int) interceptor.Invoke("serialNumber", "serialNumber() const", typeof(int));
        }
        public long CacheKey() {
            return (long) interceptor.Invoke("cacheKey", "cacheKey() const", typeof(long));
        }
        public void AddPixmap(QPixmap pixmap, QIcon.Mode mode, QIcon.State state) {
            interceptor.Invoke("addPixmap#$$", "addPixmap(const QPixmap&, QIcon::Mode, QIcon::State)", typeof(void), typeof(QPixmap), pixmap, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public void AddPixmap(QPixmap pixmap, QIcon.Mode mode) {
            interceptor.Invoke("addPixmap#$", "addPixmap(const QPixmap&, QIcon::Mode)", typeof(void), typeof(QPixmap), pixmap, typeof(QIcon.Mode), mode);
        }
        public void AddPixmap(QPixmap pixmap) {
            interceptor.Invoke("addPixmap#", "addPixmap(const QPixmap&)", typeof(void), typeof(QPixmap), pixmap);
        }
        public void AddFile(string fileName, QSize size, QIcon.Mode mode, QIcon.State state) {
            interceptor.Invoke("addFile$#$$", "addFile(const QString&, const QSize&, QIcon::Mode, QIcon::State)", typeof(void), typeof(string), fileName, typeof(QSize), size, typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public void AddFile(string fileName, QSize size, QIcon.Mode mode) {
            interceptor.Invoke("addFile$#$", "addFile(const QString&, const QSize&, QIcon::Mode)", typeof(void), typeof(string), fileName, typeof(QSize), size, typeof(QIcon.Mode), mode);
        }
        public void AddFile(string fileName, QSize size) {
            interceptor.Invoke("addFile$#", "addFile(const QString&, const QSize&)", typeof(void), typeof(string), fileName, typeof(QSize), size);
        }
        public void AddFile(string fileName) {
            interceptor.Invoke("addFile$", "addFile(const QString&)", typeof(void), typeof(string), fileName);
        }
        public List<QSize> AvailableSizes(QIcon.Mode mode, QIcon.State state) {
            return (List<QSize>) interceptor.Invoke("availableSizes$$", "availableSizes(QIcon::Mode, QIcon::State) const", typeof(List<QSize>), typeof(QIcon.Mode), mode, typeof(QIcon.State), state);
        }
        public List<QSize> AvailableSizes(QIcon.Mode mode) {
            return (List<QSize>) interceptor.Invoke("availableSizes$", "availableSizes(QIcon::Mode) const", typeof(List<QSize>), typeof(QIcon.Mode), mode);
        }
        public List<QSize> AvailableSizes() {
            return (List<QSize>) interceptor.Invoke("availableSizes", "availableSizes() const", typeof(List<QSize>));
        }
        ~QIcon() {
            interceptor.Invoke("~QIcon", "~QIcon()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QIcon", "~QIcon()", typeof(void));
        }
        public static QVariant operatorQVariant(QIcon lhs) {
            return (QVariant) staticInterceptor.Invoke("operator QVariant", "operator QVariant() const", typeof(QVariant), typeof(QIcon), lhs);
        }
        public static QIcon FromTheme(string name, QIcon fallback) {
            return (QIcon) staticInterceptor.Invoke("fromTheme$#", "fromTheme(const QString&, const QIcon&)", typeof(QIcon), typeof(string), name, typeof(QIcon), fallback);
        }
        public static QIcon FromTheme(string name) {
            return (QIcon) staticInterceptor.Invoke("fromTheme$", "fromTheme(const QString&)", typeof(QIcon), typeof(string), name);
        }
        public static bool HasThemeIcon(string name) {
            return (bool) staticInterceptor.Invoke("hasThemeIcon$", "hasThemeIcon(const QString&)", typeof(bool), typeof(string), name);
        }
        public static List<string> ThemeSearchPaths() {
            return (List<string>) staticInterceptor.Invoke("themeSearchPaths", "themeSearchPaths()", typeof(List<string>));
        }
        public static void SetThemeSearchPaths(List<string> searchpath) {
            staticInterceptor.Invoke("setThemeSearchPaths?", "setThemeSearchPaths(const QStringList&)", typeof(void), typeof(List<string>), searchpath);
        }
        public static string ThemeName() {
            return (string) staticInterceptor.Invoke("themeName", "themeName()", typeof(string));
        }
        public static void SetThemeName(string path) {
            staticInterceptor.Invoke("setThemeName$", "setThemeName(const QString&)", typeof(void), typeof(string), path);
        }
    }
}
