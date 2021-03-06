//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///   A flat self-updating message model.
    /// </remarks>        <short>     A flat self-updating message model.</short>
    [SmokeClass("Akonadi::MessageModel")]
    public class MessageModel : Akonadi.ItemModel, IDisposable {
        protected MessageModel(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(MessageModel), this);
        }
        /// <remarks>
        ///       Column types.
        ///     </remarks>        <short>         Column types.</short>
        public enum Column {
            Subject = 0,
            Sender = 1,
            Receiver = 2,
            Date = 3,
            Size = 4,
        }
        /// <remarks>
        ///       Creates a new message model.
        /// <param> name="parent" The parent object.
        ///     </param></remarks>        <short>         Creates a new message model.</short>
        public MessageModel(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("MessageModel#", "MessageModel(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public MessageModel() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("MessageModel", "MessageModel()", typeof(void));
        }
        /// <remarks>
        ///       Reimplemented from QAbstractItemModel.
        ///      </remarks>        <short>         Reimplemented from QAbstractItemModel.</short>
        [SmokeMethod("columnCount(const QModelIndex&) const")]
        public override int ColumnCount(QModelIndex parent) {
            return (int) interceptor.Invoke("columnCount#", "columnCount(const QModelIndex&) const", typeof(int), typeof(QModelIndex), parent);
        }
        [SmokeMethod("columnCount() const")]
        public override int ColumnCount() {
            return (int) interceptor.Invoke("columnCount", "columnCount() const", typeof(int));
        }
        /// <remarks>
        ///       Reimplemented from QAbstractItemModel.
        ///      </remarks>        <short>         Reimplemented from QAbstractItemModel.</short>
        [SmokeMethod("data(const QModelIndex&, int) const")]
        public override QVariant Data(QModelIndex index, int role) {
            return (QVariant) interceptor.Invoke("data#$", "data(const QModelIndex&, int) const", typeof(QVariant), typeof(QModelIndex), index, typeof(int), role);
        }
        [SmokeMethod("data(const QModelIndex&) const")]
        public override QVariant Data(QModelIndex index) {
            return (QVariant) interceptor.Invoke("data#", "data(const QModelIndex&) const", typeof(QVariant), typeof(QModelIndex), index);
        }
        /// <remarks>
        ///       Reimplemented from QAbstractItemModel.
        ///      </remarks>        <short>         Reimplemented from QAbstractItemModel.</short>
        [SmokeMethod("headerData(int, Qt::Orientation, int) const")]
        public override QVariant HeaderData(int section, Qt.Orientation orientation, int role) {
            return (QVariant) interceptor.Invoke("headerData$$$", "headerData(int, Qt::Orientation, int) const", typeof(QVariant), typeof(int), section, typeof(Qt.Orientation), orientation, typeof(int), role);
        }
        [SmokeMethod("headerData(int, Qt::Orientation) const")]
        public override QVariant HeaderData(int section, Qt.Orientation orientation) {
            return (QVariant) interceptor.Invoke("headerData$$", "headerData(int, Qt::Orientation) const", typeof(QVariant), typeof(int), section, typeof(Qt.Orientation), orientation);
        }
        ~MessageModel() {
            interceptor.Invoke("~MessageModel", "~MessageModel()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~MessageModel", "~MessageModel()", typeof(void));
        }
        protected new IMessageModelSignals Emit {
            get { return (IMessageModelSignals) Q_EMIT; }
        }
    }

    public interface IMessageModelSignals : Akonadi.IItemModelSignals {
    }
}
