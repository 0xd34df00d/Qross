//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///   Converts between collection id and collection path.
    ///   While it is generally recommended to use collection ids, it can
    ///   be necessary in some cases (eg. a command line client) to use the
    ///   collection path instead. Use this class to get a collection id
    ///   from a collection path.
    /// </remarks>        <short>     Converts between collection id and collection path.</short>
    [SmokeClass("Akonadi::CollectionPathResolver")]
    public class CollectionPathResolver : Akonadi.Job, IDisposable {
        protected CollectionPathResolver(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(CollectionPathResolver), this);
        }
        // Id collection(); >>>> NOT CONVERTED
        /// <remarks>
        ///       Creates a new CollectionPathResolver to convert a path into a id.
        /// <param> name="path" The collection path.
        /// </param><param> name="parent" The parent object.
        ///     </param></remarks>        <short>         Creates a new CollectionPathResolver to convert a path into a id.</short>
        public CollectionPathResolver(string path, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionPathResolver$#", "CollectionPathResolver(const QString&, QObject*)", typeof(void), typeof(string), path, typeof(QObject), parent);
        }
        public CollectionPathResolver(string path) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionPathResolver$", "CollectionPathResolver(const QString&)", typeof(void), typeof(string), path);
        }
        /// <remarks>
        ///       Creates a new CollectionPathResolver to determine the path of
        ///       the given collection.
        /// <param> name="collection" The collection
        /// </param><param> name="parent" The parent object.
        ///     </param></remarks>        <short>         Creates a new CollectionPathResolver to determine the path of       the given collection.</short>
        public CollectionPathResolver(Akonadi.Collection collection, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionPathResolver##", "CollectionPathResolver(const Akonadi::Collection&, QObject*)", typeof(void), typeof(Akonadi.Collection), collection, typeof(QObject), parent);
        }
        public CollectionPathResolver(Akonadi.Collection collection) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("CollectionPathResolver#", "CollectionPathResolver(const Akonadi::Collection&)", typeof(void), typeof(Akonadi.Collection), collection);
        }
        /// <remarks>
        ///       Returns the collection id. Only valid after the job succeeded.
        ///     </remarks>        <short>         Returns the collection id.</short>
        /// <remarks>
        ///       Returns the collection path. Only valid after the job succeeded.
        ///     </remarks>        <short>         Returns the collection path.</short>
        public string Path() {
            return (string) interceptor.Invoke("path", "path() const", typeof(string));
        }
        [SmokeMethod("doStart()")]
        protected override void DoStart() {
            interceptor.Invoke("doStart", "doStart()", typeof(void));
        }
        ~CollectionPathResolver() {
            interceptor.Invoke("~CollectionPathResolver", "~CollectionPathResolver()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~CollectionPathResolver", "~CollectionPathResolver()", typeof(void));
        }
        protected new ICollectionPathResolverSignals Emit {
            get { return (ICollectionPathResolverSignals) Q_EMIT; }
        }
    }

    public interface ICollectionPathResolverSignals : Akonadi.IJobSignals {
    }
}
