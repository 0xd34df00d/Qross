//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  @class AccessManager plasma/accessmanager.h <Plasma/AccessManager>
    ///  This manager provides a way to access an applet (either a binary or packaged one) that is hosted
    ///  on another machine. It also provides a mechanism to discover services announced to the network
    ///  through zeroconf.
    /// </remarks>        <short> Allows access to remote Plasma.Applet classes. </short>
    [SmokeClass("Plasma::AccessManager")]
    public class AccessManager : QObject {
        protected AccessManager(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(AccessManager), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static AccessManager() {
            staticInterceptor = new SmokeInvocation(typeof(AccessManager), null);
        }
        /// <remarks>
        ///  Access a native plasmoid hosted on another machine.
        /// <param> name="location" the location of the remote plasmoids. Exmples of valid urls:
        ///  plasma://ip:port/resourceName
        ///  zeroconf://PlasmoidName
        /// </param></remarks>        <return> a job that can be used to track when a remote plasmoid is ready for use, and to
        ///  obtain the applet when the package is sent over.
        ///          </return>
        ///         <short>    Access a native plasmoid hosted on another machine.</short>
        public Plasma.AccessAppletJob AccessRemoteApplet(KUrl location) {
            return (Plasma.AccessAppletJob) interceptor.Invoke("accessRemoteApplet#", "accessRemoteApplet(const KUrl&) const", typeof(Plasma.AccessAppletJob), typeof(KUrl), location);
        }
        /// <remarks>
        /// </remarks>        <return> a list of applets that are announced on the network through zeroconf. Use the
        ///  remoteLocation() function in PackageMetadata to obtain an url to pass to
        ///  accessRemoteApplet in AccessManager if you want to access one of these applets.
        ///          </return>
        ///         <short>   </short>
        public List<Plasma.PackageMetadata> RemoteApplets() {
            return (List<Plasma.PackageMetadata>) interceptor.Invoke("remoteApplets", "remoteApplets() const", typeof(List<Plasma.PackageMetadata>));
        }
        /// <remarks>
        ///  Singleton pattern accessor.
        ///          </remarks>        <short>    Singleton pattern accessor.</short>
        public static Plasma.AccessManager Self() {
            return (Plasma.AccessManager) staticInterceptor.Invoke("self", "self()", typeof(Plasma.AccessManager));
        }
        /// <remarks>
        /// </remarks>        <return> a list of supported protocols of urls that can be passed to accessRemoteApplet.
        ///          </return>
        ///         <short>   </short>
        public static List<string> SupportedProtocols() {
            return (List<string>) staticInterceptor.Invoke("supportedProtocols", "supportedProtocols()", typeof(List<string>));
        }
        protected new IAccessManagerSignals Emit {
            get { return (IAccessManagerSignals) Q_EMIT; }
        }
    }

    public interface IAccessManagerSignals : IQObjectSignals {
    }
}
