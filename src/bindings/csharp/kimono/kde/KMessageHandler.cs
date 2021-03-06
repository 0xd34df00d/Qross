//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;

    public interface IKMessageHandler {
        void Message(KMessage.MessageType type, string text, string caption);
    }
    /// <remarks>
    ///  \class KMessageHandler kmessage.h <KMessageHandler>
    ///  @brief Abstract class for KMessage handler.
    ///  This class define how KMessage display a message.
    ///  Reimplement the methods then set your custom
    ///  KMessageHandler using KMessage.SetMessageHandler()
    /// </remarks>        <author> Michaël Larouche <michael.larouche@kdemail.net>
    ///  </author>
    ///         <short>    \class KMessageHandler kmessage.</short>
    [SmokeClass("KMessageHandler")]
    public abstract class KMessageHandler : Object, IKMessageHandler {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected KMessageHandler(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KMessageHandler), this);
        }
        /// <remarks>
        ///  @brief Display a long message of a certain type.
        ///  A long message span on multiple lines and can have a caption.
        /// <param> name="type" Currrent type of message. See MessageType enum.
        /// </param><param> name="text" Long message to be displayed.
        /// </param><param> name="caption" Caption to be used. This is optional.
        ///      </param></remarks>        <short>    @brief Display a long message of a certain type.</short>
        [SmokeMethod("message(KMessage::MessageType, const QString&, const QString&)")]
        public abstract void Message(KMessage.MessageType type, string text, string caption);
        public KMessageHandler() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KMessageHandler", "KMessageHandler()", typeof(void));
        }
    }
}
