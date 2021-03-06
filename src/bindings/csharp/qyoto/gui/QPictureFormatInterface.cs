//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QPictureFormatInterface")]
    public abstract class QPictureFormatInterface : QFactoryInterface {
        protected QPictureFormatInterface(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QPictureFormatInterface), this);
        }
        [SmokeMethod("loadPicture(const QString&, const QString&, QPicture*)")]
        public abstract bool LoadPicture(string format, string filename, QPicture arg3);
        [SmokeMethod("savePicture(const QString&, const QString&, const QPicture&)")]
        public abstract bool SavePicture(string format, string filename, QPicture arg3);
        [SmokeMethod("installIOHandler(const QString&)")]
        public abstract bool InstallIOHandler(string arg1);
        public QPictureFormatInterface() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QPictureFormatInterface", "QPictureFormatInterface()", typeof(void));
        }
    }
}
