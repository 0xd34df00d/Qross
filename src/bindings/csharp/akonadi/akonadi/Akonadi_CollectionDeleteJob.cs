//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///  This job deletes a collection and all its sub-collections as well as all associated content.
    ///  @code
    ///  Akonadi.Collection collection = ...
    ///  Akonadi.CollectionDeleteJob job = new Akonadi.CollectionDeleteJob( collection );
    ///  if ( job.Exec() )
    ///    qDebug() << "Deleted successfully";
    ///  else
    ///    qDebug() << "Error occurred";
    ///  @endcode
    /// </remarks>        <author> Volker Krause <vkrause@kde.org>
    ///  </author>
    ///         <short> Job that deletes a collection in the Akonadi storage. </short>
    [SmokeClass("Akonadi::CollectionDeleteJob")]
    public class CollectionDeleteJob : Akonadi.Job, IDisposable {
        protected CollectionDeleteJob(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(CollectionDeleteJob), this);
        }
        /// <remarks>
        ///  Creates a new collection delete job.
        /// <param> name="collection" The collection to delete.
        /// </param><param> name="parent" The parent object.
        ///      </param></remarks>        <short>    Creates a new collection delete job.</short>
        public CollectionDeleteJob(Akonadi.Collection collection, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionDeleteJob##", "CollectionDeleteJob(const Akonadi::Collection&, QObject*)", typeof(void), typeof(Akonadi.Collection), collection, typeof(QObject), parent);
        }
        public CollectionDeleteJob(Akonadi.Collection collection) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionDeleteJob#", "CollectionDeleteJob(const Akonadi::Collection&)", typeof(void), typeof(Akonadi.Collection), collection);
        }
        [SmokeMethod("doStart()")]
        protected override void DoStart() {
            interceptor.Invoke("doStart", "doStart()", typeof(void));
        }
        ~CollectionDeleteJob() {
            interceptor.Invoke("~CollectionDeleteJob", "~CollectionDeleteJob()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~CollectionDeleteJob", "~CollectionDeleteJob()", typeof(void));
        }
        protected new ICollectionDeleteJobSignals Emit {
            get { return (ICollectionDeleteJobSignals) Q_EMIT; }
        }
    }

    public interface ICollectionDeleteJobSignals : Akonadi.IJobSignals {
    }
}
