//Auto-generated by kalyptus. DO NOT EDIT.
namespace Soprano.Server {
    using Soprano;
    using System;
    using Qyoto;
    /// <remarks>
    ///  \class DBusExportModel dbusexportmodel.h Soprano/Server/DBusExportModel
    ///  \brief Exports a %Soprano Model via D-Bus.
    ///  DBusExportModel is a FilterModel like any other. As such,
    ///  it can occure anywhere in a stack of models. However,
    ///  the model exported via D-Bus is actually the FilterModel.ParentModel,
    ///  not the DBusExportModel itself. Thus, subclassing DBusExportModel
    ///  to modify the behaviour of methods called via D-Bus does not 
    ///  make sense. Instead stack the DBusExportModel on top of
    ///  your own custom FilterModel.
    ///  For creating a simple %Soprano D-Bus server see 
    ///  ServerCore.RegisterAsDBusObject.
    ///  The interface exported can be accessed via Client.DBusModel.
    ///  DBusExportModel automatically makes use of a Util.AsyncModel as
    ///  parent model to create delayed D-Bus replies. If the parent model
    ///  is not a Util.AsyncModel all calls will be performed syncroneously.
    ///  \author Sebastian Trueg <trueg@kde.org>
    ///  \sa \ref soprano_server_dbus
    ///  \since 2.1
    ///          </remarks>        <short>    \class DBusExportModel dbusexportmodel.</short>
    [SmokeClass("Soprano::Server::DBusExportModel")]
    public class DBusExportModel : Soprano.FilterModel, IDisposable {
        protected DBusExportModel(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(DBusExportModel), this);
        }
        /// <remarks>
        ///  Create a new D-Bus export model.
        ///  \param model The parent model which should be exported.
        ///              </remarks>        <short>    Create a new D-Bus export model.</short>
        public DBusExportModel(Soprano.Model model) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("DBusExportModel#", "DBusExportModel(Soprano::Model*)", typeof(void), typeof(Soprano.Model), model);
        }
        public DBusExportModel() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("DBusExportModel", "DBusExportModel()", typeof(void));
        }
        /// <remarks>
        ///  Register the model under the given D-Bus object path.
        ///  \sa QDBusConnection.RegisterObject
        ///              </remarks>        <short>    Register the model under the given D-Bus object path.</short>
        public bool RegisterModel(string dbusObjectPath) {
            return (bool) interceptor.Invoke("registerModel$", "registerModel(const QString&)", typeof(bool), typeof(string), dbusObjectPath);
        }
        /// <remarks>
        ///  Unregister the model from D-Bus.
        ///  \sa QDBusConnection.UnregisterObject
        ///              </remarks>        <short>    Unregister the model from D-Bus.</short>
        public void UnregisterModel() {
            interceptor.Invoke("unregisterModel", "unregisterModel()", typeof(void));
        }
        /// <remarks>
        ///  The path this model is exported on.
        ///  This is an empty string if the model is not exported.
        ///              </remarks>        <short>    The path this model is exported on.</short>
        public string DbusObjectPath() {
            return (string) interceptor.Invoke("dbusObjectPath", "dbusObjectPath() const", typeof(string));
        }
        ~DBusExportModel() {
            interceptor.Invoke("~DBusExportModel", "~DBusExportModel()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~DBusExportModel", "~DBusExportModel()", typeof(void));
        }
        protected new IDBusExportModelSignals Emit {
            get { return (IDBusExportModelSignals) Q_EMIT; }
        }
    }

    public interface IDBusExportModelSignals : Soprano.IFilterModelSignals {
    }
}
