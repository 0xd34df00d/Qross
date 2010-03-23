//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  @brief This is a convience KMessageHandler that use KMessageBox.
    /// </remarks>        <author> Michaël Larouche <michael.larouche@kdemail.net>
    /// </author>
    ///         <short>    @brief This is a convience KMessageHandler that use KMessageBox.</short>
    [SmokeClass("KMessageBoxMessageHandler")]
    public class KMessageBoxMessageHandler : QObject, IKMessageHandler, IDisposable {
        protected KMessageBoxMessageHandler(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KMessageBoxMessageHandler), this);
        }
        /// <remarks>
        ///  @brief Create a new KMessageBoxMessageHandler
        /// <param> name="parent" Parent widget to use for the KMessageBox.
        ///      </param></remarks>        <short>    @brief Create a new KMessageBoxMessageHandler </short>
        public KMessageBoxMessageHandler(QWidget parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMessageBoxMessageHandler#", "KMessageBoxMessageHandler(QWidget*)", typeof(void), typeof(QWidget), parent);
        }
        public KMessageBoxMessageHandler() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMessageBoxMessageHandler", "KMessageBoxMessageHandler()", typeof(void));
        }
        /// <remarks>
        ///  @copydoc KMessageHandler.Message
        ///      </remarks>        <short>    @copydoc KMessageHandler.Message      </short>
        [SmokeMethod("message(KMessage::MessageType, const QString&, const QString&)")]
        public virtual void Message(KMessage.MessageType messageType, string text, string caption) {
            interceptor.Invoke("message$$$", "message(KMessage::MessageType, const QString&, const QString&)", typeof(void), typeof(KMessage.MessageType), messageType, typeof(string), text, typeof(string), caption);
        }
        ~KMessageBoxMessageHandler() {
            interceptor.Invoke("~KMessageBoxMessageHandler", "~KMessageBoxMessageHandler()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KMessageBoxMessageHandler", "~KMessageBoxMessageHandler()", typeof(void));
        }
        protected new IKMessageBoxMessageHandlerSignals Emit {
            get { return (IKMessageBoxMessageHandlerSignals) Q_EMIT; }
        }
    }

    public interface IKMessageBoxMessageHandlerSignals : IQObjectSignals {
    }
}
