//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  This class can be used to retrieve the complete or partial collection tree
    ///  from the Akonadi storage.
    ///  @code
    ///  using namespace Akonadi;
    ///  // fetching all collections recursive, starting at the root collection
    ///  CollectionFetchJob job = new CollectionFetchJob( Collection.Root(), CollectionFetchJob.Recursive );
    ///  if ( job.Exec() ) {
    ///    Collection.List collections = job.Collections();
    ///    foreach( Collectioncollection, collections ) {
    ///      qDebug() << "Name:" << collection.name();
    ///    }
    ///  }
    ///  @endcode
    ///  See <see cref="ICollectionFetchJobSignals"></see> for signals emitted by CollectionFetchJob
    /// </remarks>        <author> Volker Krause <vkrause@kde.org>
    ///  </author>
    ///         <short> Job that fetches collections from the Akonadi storage. </short>
    [SmokeClass("Akonadi::CollectionFetchJob")]
    public class CollectionFetchJob : Akonadi.Job, IDisposable {
        protected CollectionFetchJob(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(CollectionFetchJob), this);
        }
        /// <remarks>
        ///  Describes the type of fetch depth.
        ///      </remarks>        <short>    Describes the type of fetch depth.</short>
        public enum TypeOf {
            Base = 0,
            FirstLevel = 1,
            Recursive = 2,
        }
        /// <remarks>
        ///  Creates a new collection fetch job.
        /// <param> name="collection" The base collection for the listing. Must be valid.
        /// </param><param> name="type" The type of fetch depth.
        /// </param><param> name="parent" The parent object.
        ///      </param></remarks>        <short>    Creates a new collection fetch job.</short>
        public CollectionFetchJob(Akonadi.Collection collection, Akonadi.CollectionFetchJob.TypeOf type, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionFetchJob#$#", "CollectionFetchJob(const Akonadi::Collection&, Akonadi::CollectionFetchJob::Type, QObject*)", typeof(void), typeof(Akonadi.Collection), collection, typeof(Akonadi.CollectionFetchJob.TypeOf), type, typeof(QObject), parent);
        }
        public CollectionFetchJob(Akonadi.Collection collection, Akonadi.CollectionFetchJob.TypeOf type) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionFetchJob#$", "CollectionFetchJob(const Akonadi::Collection&, Akonadi::CollectionFetchJob::Type)", typeof(void), typeof(Akonadi.Collection), collection, typeof(Akonadi.CollectionFetchJob.TypeOf), type);
        }
        public CollectionFetchJob(Akonadi.Collection collection) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionFetchJob#", "CollectionFetchJob(const Akonadi::Collection&)", typeof(void), typeof(Akonadi.Collection), collection);
        }
        /// <remarks>
        ///  Creates a new collection fetch job to retrieve a list of collections.
        /// <param> name="collections" A list of collections to fetch. Must not be empty, content must be valid.
        /// </param><param> name="parent" The parent object.
        ///      </param></remarks>        <short>    Creates a new collection fetch job to retrieve a list of collections.</short>
        public CollectionFetchJob(List<Akonadi.Collection> collections, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionFetchJob?#", "CollectionFetchJob(const QList<Akonadi::Collection>&, QObject*)", typeof(void), typeof(List<Akonadi.Collection>), collections, typeof(QObject), parent);
        }
        public CollectionFetchJob(List<Akonadi.Collection> collections) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionFetchJob?", "CollectionFetchJob(const QList<Akonadi::Collection>&)", typeof(void), typeof(List<Akonadi.Collection>), collections);
        }
        /// <remarks>
        ///  Returns the list of fetched collection.
        ///      </remarks>        <short>    Returns the list of fetched collection.</short>
        public List<Akonadi.Collection> Collections() {
            return (List<Akonadi.Collection>) interceptor.Invoke("collections", "collections() const", typeof(List<Akonadi.Collection>));
        }
        /// <remarks>
        ///  Sets a resource identifier to limit collection listing to one resource.
        /// <param> name="resource" The resource identifier.
        ///      </param></remarks>        <short>    Sets a resource identifier to limit collection listing to one resource.</short>
        public void SetResource(string resource) {
            interceptor.Invoke("setResource$", "setResource(const QString&)", typeof(void), typeof(string), resource);
        }
        /// <remarks>
        ///  Include also unsubscribed collections.
        ///      </remarks>        <short>    Include also unsubscribed collections.</short>
        public void IncludeUnsubscribed(bool include) {
            interceptor.Invoke("includeUnsubscribed$", "includeUnsubscribed(bool)", typeof(void), typeof(bool), include);
        }
        public void IncludeUnsubscribed() {
            interceptor.Invoke("includeUnsubscribed", "includeUnsubscribed()", typeof(void));
        }
        [SmokeMethod("doStart()")]
        protected override void DoStart() {
            interceptor.Invoke("doStart", "doStart()", typeof(void));
        }
        [SmokeMethod("doHandleResponse(const QByteArray&, const QByteArray&)")]
        protected override void DoHandleResponse(QByteArray tag, QByteArray data) {
            interceptor.Invoke("doHandleResponse##", "doHandleResponse(const QByteArray&, const QByteArray&)", typeof(void), typeof(QByteArray), tag, typeof(QByteArray), data);
        }
        [Q_SLOT("void slotResult(KJob*)")]
        [SmokeMethod("slotResult(KJob*)")]
        protected override void SlotResult(KJob job) {
            interceptor.Invoke("slotResult#", "slotResult(KJob*)", typeof(void), typeof(KJob), job);
        }
        ~CollectionFetchJob() {
            interceptor.Invoke("~CollectionFetchJob", "~CollectionFetchJob()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~CollectionFetchJob", "~CollectionFetchJob()", typeof(void));
        }
        protected new ICollectionFetchJobSignals Emit {
            get { return (ICollectionFetchJobSignals) Q_EMIT; }
        }
    }

    public interface ICollectionFetchJobSignals : Akonadi.IJobSignals {
        /// <remarks>
        ///  This signal is emitted whenever the job has received collections.
        /// <param> name="collections" The received collections.
        ///      </param></remarks>        <short>    This signal is emitted whenever the job has received collections.</short>
        [Q_SIGNAL("void collectionsReceived(Akonadi::Collection::List)")]
        void CollectionsReceived(List<Akonadi.Collection> collections);
    }
}
