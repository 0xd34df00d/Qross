//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///  This job creates so called or search collections, which don't contain
    ///  real data, but references to items that match a given search query.
    ///  @code
    ///  string name = "My search folder";
    ///  string query = "...";
    ///  Akonadi.SearchCreateJob job = new Akonadi.SearchCreateJob( name, query );
    ///  if ( job.Exec() )
    ///    qDebug() << "Created search folder successfully";
    ///  else
    ///    qDebug() << "Error occurred";
    ///  @endcode
    ///  @todo Add method that returns the new search collection.
    /// </remarks>        <author> Volker Krause <vkrause@kde.org>
    ///  </author>
    ///         <short> Job that creates a virtual/search collection in the Akonadi storage. </short>
    [SmokeClass("Akonadi::SearchCreateJob")]
    public class SearchCreateJob : Akonadi.Job, IDisposable {
        protected SearchCreateJob(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(SearchCreateJob), this);
        }
        /// <remarks>
        ///  Creates a search create job.
        /// <param> name="name" The name of the search collection.
        /// </param><param> name="query" The search query (format not defined yet).
        /// </param><param> name="parent" The parent object.
        ///      </param></remarks>        <short>    Creates a search create job.</short>
        public SearchCreateJob(string name, string query, QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SearchCreateJob$$#", "SearchCreateJob(const QString&, const QString&, QObject*)", typeof(void), typeof(string), name, typeof(string), query, typeof(QObject), parent);
        }
        public SearchCreateJob(string name, string query) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SearchCreateJob$$", "SearchCreateJob(const QString&, const QString&)", typeof(void), typeof(string), name, typeof(string), query);
        }
        [SmokeMethod("doStart()")]
        protected override void DoStart() {
            interceptor.Invoke("doStart", "doStart()", typeof(void));
        }
        ~SearchCreateJob() {
            interceptor.Invoke("~SearchCreateJob", "~SearchCreateJob()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~SearchCreateJob", "~SearchCreateJob()", typeof(void));
        }
        protected new ISearchCreateJobSignals Emit {
            get { return (ISearchCreateJobSignals) Q_EMIT; }
        }
    }

    public interface ISearchCreateJobSignals : Akonadi.IJobSignals {
    }
}
