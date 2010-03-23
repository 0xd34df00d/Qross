//Auto-generated by kalyptus. DO NOT EDIT.
namespace Soprano.Client {
    using Soprano;
    using System;
    using Qyoto;
    /// <remarks>
    ///  \class SparqlModel sparqlmodel.h Soprano/Client/SparqlModel
    ///  \brief Remote client Model for Http SPARQL end points.
    ///  The SparqlModel provides a very simple way of accessing remote
    ///  <a href="http://www.w3.org/TR/rdf-sparql-protocol/">SPARQL (SPARQL Protocol and RDF Query Language)</a>
    ///  web services via Http.
    ///  Its usage is simple: set hostname and optionally user credentials, then
    ///  call the well known Model methods like Model.ExecuteQuery to work with the remote
    ///  repository.
    ///  \author Rajeev J Sebastian <rajeev.sebastian@gmail.com><br>Sebastian Trueg <trueg@kde.org>
    ///  \since 2.2
    ///          </remarks>        <short>    \class SparqlModel sparqlmodel.</short>
    [SmokeClass("Soprano::Client::SparqlModel")]
    public class SparqlModel : Soprano.Model, IDisposable {
        protected SparqlModel(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(SparqlModel), this);
        }
        /// <remarks>
        ///  Create a new SparqlModel instance.
        ///  \param host The host to connect to (example: dbpedia.org)
        ///  \param port The port on which to connect the host (most
        ///         Http services run on port 80.
        ///  \param user The userName in case the host does not allow
        ///         anonymous access.
        ///  \param password The password for <pre>user</pre> in case the host
        ///  does not allow anonymous access.
        ///              </remarks>        <short>    Create a new SparqlModel instance.</short>
        public SparqlModel(string host, ushort port, string user, string password) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SparqlModel$$$$", "SparqlModel(const QString&, unsigned short, const QString&, const QString&)", typeof(void), typeof(string), host, typeof(ushort), port, typeof(string), user, typeof(string), password);
        }
        public SparqlModel(string host, ushort port, string user) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SparqlModel$$$", "SparqlModel(const QString&, unsigned short, const QString&)", typeof(void), typeof(string), host, typeof(ushort), port, typeof(string), user);
        }
        public SparqlModel(string host, ushort port) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SparqlModel$$", "SparqlModel(const QString&, unsigned short)", typeof(void), typeof(string), host, typeof(ushort), port);
        }
        public SparqlModel(string host) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SparqlModel$", "SparqlModel(const QString&)", typeof(void), typeof(string), host);
        }
        public SparqlModel() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("SparqlModel", "SparqlModel()", typeof(void));
        }
        /// <remarks>
        ///  Set the host to connect to.
        ///  \param host The host to connect to (example: dbpedia.org)
        ///  \param port The port on which to connect the host (most
        ///         Http services run on port 80.
        ///              </remarks>        <short>    Set the host to connect to.</short>
        public void SetHost(string host, ushort port) {
            interceptor.Invoke("setHost$$", "setHost(const QString&, unsigned short)", typeof(void), typeof(string), host, typeof(ushort), port);
        }
        public void SetHost(string host) {
            interceptor.Invoke("setHost$", "setHost(const QString&)", typeof(void), typeof(string), host);
        }
        /// <remarks>
        ///  Set the user name and password to access the host.
        ///  \param user The userName in case the host does not allow
        ///         anonymous access.
        ///  \param password The password for <pre>user</pre> in case the host
        ///              </remarks>        <short>    Set the user name and password to access the host.</short>
        public void SetUser(string user, string password) {
            interceptor.Invoke("setUser$$", "setUser(const QString&, const QString&)", typeof(void), typeof(string), user, typeof(string), password);
        }
        public void SetUser(string user) {
            interceptor.Invoke("setUser$", "setUser(const QString&)", typeof(void), typeof(string), user);
        }
        /// <remarks>
        ///  Set the path to where the SPARQL endpoint is exposed on the server.
        ///  For historical reasons the default path is set to "/sparql".
        ///  \since 2.2.1
        ///              </remarks>        <short>    Set the path to where the SPARQL endpoint is exposed on the server.</short>
        public void SetPath(string path) {
            interceptor.Invoke("setPath$", "setPath(const QString&)", typeof(void), typeof(string), path);
        }
        /// <remarks>
        ///  Add a statement to the remote model.
        ///  This method is realized using the <a href="http://jena.hpl.hp.com/~afs/SPARQL-Update.html">SPARQL/Update</a>
        ///  language extension. Thus, it will only work on services supporting this extension.
        ///  \param statement The Statement to add.
        ///  \return Error.ErrorNone on success and an error code if statement was invalid or an error
        ///  occured. Check Error.ErrorCache.LastError for detailed error information.
        ///              </remarks>        <short>    Add a statement to the remote model.</short>
        [SmokeMethod("addStatement(const Soprano::Statement&)")]
        public override Soprano.Error.ErrorCode AddStatement(Soprano.Statement statement) {
            return (Soprano.Error.ErrorCode) interceptor.Invoke("addStatement#", "addStatement(const Soprano::Statement&)", typeof(Soprano.Error.ErrorCode), typeof(Soprano.Statement), statement);
        }
        /// <remarks>
        ///  Removed a statement from the remote model.
        ///  This method is realized using the <a href="http://jena.hpl.hp.com/~afs/SPARQL-Update.html">SPARQL/Update</a>
        ///  language extension. Thus, it will only work on services supporting this extension.
        ///  \param statement The Statement to remove.
        ///  \return Error.ErrorNone on success and an error code if statement was invalid or an error
        ///  occured. Check Error.ErrorCache.LastError for detailed error information.
        ///              </remarks>        <short>    Removed a statement from the remote model.</short>
        [SmokeMethod("removeStatement(const Soprano::Statement&)")]
        public override Soprano.Error.ErrorCode RemoveStatement(Soprano.Statement statement) {
            return (Soprano.Error.ErrorCode) interceptor.Invoke("removeStatement#", "removeStatement(const Soprano::Statement&)", typeof(Soprano.Error.ErrorCode), typeof(Soprano.Statement), statement);
        }
        /// <remarks>
        ///  Remove all statements that match the partial statement. For removing
        ///  one specific statement see removeStatement().
        ///  This method is realized using the <a href="http://jena.hpl.hp.com/~afs/SPARQL-Update.html">SPARQL/Update</a>
        ///  language extension. Thus, it will only work on services supporting this extension.
        ///  \param statement A possible partially defined statement that serves as
        ///  a filter for all statements that should be removed.
        ///  \return Error.ErrorNone on success and an error code if statement was invalid or an error
        ///  occured. Check Error.ErrorCache.LastError for detailed error information.
        ///              </remarks>        <short>    Remove all statements that match the partial statement.</short>
        [SmokeMethod("removeAllStatements(const Soprano::Statement&)")]
        public override Soprano.Error.ErrorCode RemoveAllStatements(Soprano.Statement statement) {
            return (Soprano.Error.ErrorCode) interceptor.Invoke("removeAllStatements#", "removeAllStatements(const Soprano::Statement&)", typeof(Soprano.Error.ErrorCode), typeof(Soprano.Statement), statement);
        }
        [SmokeMethod("listStatements(const Soprano::Statement&) const")]
        public override Soprano.StatementIterator ListStatements(Soprano.Statement partial) {
            return (Soprano.StatementIterator) interceptor.Invoke("listStatements#", "listStatements(const Soprano::Statement&) const", typeof(Soprano.StatementIterator), typeof(Soprano.Statement), partial);
        }
        /// <remarks>
        ///  Execute a query on the SPARQL endpoint.
        ///  \param query The query to evaluate.
        ///  \param language The query language used to encode <pre>query</pre>. Be aware that
        ///         the SparqlModel does only support one query language: Query.QueryLanguageSparql.
        ///  \param userQueryLanguage unused since <pre>language</pre> needs to be set to Query.QueryLanguageSparql.
        ///  \return An iterator over all results matching the query, 
        ///  on error an invalid iterator is returned.
        ///              </remarks>        <short>    Execute a query on the SPARQL endpoint.</short>
        [SmokeMethod("executeQuery(const QString&, Soprano::Query::QueryLanguage, const QString&) const")]
        public override Soprano.QueryResultIterator ExecuteQuery(string query, Soprano.Query.QueryLanguage language, string userQueryLanguage) {
            return (Soprano.QueryResultIterator) interceptor.Invoke("executeQuery$$$", "executeQuery(const QString&, Soprano::Query::QueryLanguage, const QString&) const", typeof(Soprano.QueryResultIterator), typeof(string), query, typeof(Soprano.Query.QueryLanguage), language, typeof(string), userQueryLanguage);
        }
        [SmokeMethod("executeQuery(const QString&, Soprano::Query::QueryLanguage) const")]
        public virtual Soprano.QueryResultIterator ExecuteQuery(string query, Soprano.Query.QueryLanguage language) {
            return (Soprano.QueryResultIterator) interceptor.Invoke("executeQuery$$", "executeQuery(const QString&, Soprano::Query::QueryLanguage) const", typeof(Soprano.QueryResultIterator), typeof(string), query, typeof(Soprano.Query.QueryLanguage), language);
        }
        public Soprano.QueryResultIterator ExecuteQuery(string query) {
            return (Soprano.QueryResultIterator) interceptor.Invoke("executeQuery$", "executeQuery(const QString&) const", typeof(Soprano.QueryResultIterator), typeof(string), query);
        }
        /// <remarks>
        ///  Asyncroneously execute the given query over the Model.
        ///  \param query The query to evaluate.
        ///  \param language The %query language used to encode <pre>query</pre>.
        ///  \param userQueryLanguage If <pre>language</pre> equals Query.QueryLanguageUser
        ///  userQueryLanguage defines the language to use.
        ///  \sa executeQuery
        ///  \return an AsyncResult with result type QueryResultIterator
        ///  object which will signal when the result is ready.
        ///              </remarks>        <short>    Asyncroneously execute the given query over the Model.</short>
        public Soprano.Util.AsyncResult ExecuteQueryAsync(string query, Soprano.Query.QueryLanguage language, string userQueryLanguage) {
            return (Soprano.Util.AsyncResult) interceptor.Invoke("executeQueryAsync$$$", "executeQueryAsync(const QString&, Soprano::Query::QueryLanguage, const QString&) const", typeof(Soprano.Util.AsyncResult), typeof(string), query, typeof(Soprano.Query.QueryLanguage), language, typeof(string), userQueryLanguage);
        }
        public Soprano.Util.AsyncResult ExecuteQueryAsync(string query, Soprano.Query.QueryLanguage language) {
            return (Soprano.Util.AsyncResult) interceptor.Invoke("executeQueryAsync$$", "executeQueryAsync(const QString&, Soprano::Query::QueryLanguage) const", typeof(Soprano.Util.AsyncResult), typeof(string), query, typeof(Soprano.Query.QueryLanguage), language);
        }
        public Soprano.Util.AsyncResult ExecuteQueryAsync(string query) {
            return (Soprano.Util.AsyncResult) interceptor.Invoke("executeQueryAsync$", "executeQueryAsync(const QString&) const", typeof(Soprano.Util.AsyncResult), typeof(string), query);
        }
        [SmokeMethod("listContexts() const")]
        public override Soprano.NodeIterator ListContexts() {
            return (Soprano.NodeIterator) interceptor.Invoke("listContexts", "listContexts() const", typeof(Soprano.NodeIterator));
        }
        [SmokeMethod("containsStatement(const Soprano::Statement&) const")]
        public override bool ContainsStatement(Soprano.Statement statement) {
            return (bool) interceptor.Invoke("containsStatement#", "containsStatement(const Soprano::Statement&) const", typeof(bool), typeof(Soprano.Statement), statement);
        }
        [SmokeMethod("containsAnyStatement(const Soprano::Statement&) const")]
        public override bool ContainsAnyStatement(Soprano.Statement statement) {
            return (bool) interceptor.Invoke("containsAnyStatement#", "containsAnyStatement(const Soprano::Statement&) const", typeof(bool), typeof(Soprano.Statement), statement);
        }
        /// <remarks>
        ///  Retrieving the number of statements is not supported by the SparqlModel.
        ///  \return -1
        ///              </remarks>        <short>    Retrieving the number of statements is not supported by the SparqlModel.</short>
        [SmokeMethod("statementCount() const")]
        public override int StatementCount() {
            return (int) interceptor.Invoke("statementCount", "statementCount() const", typeof(int));
        }
        /// <remarks>
        ///  Not supported by the SparqlModel.
        ///  \return false
        ///              </remarks>        <short>    Not supported by the SparqlModel.</short>
        [SmokeMethod("isEmpty() const")]
        public override bool IsEmpty() {
            return (bool) interceptor.Invoke("isEmpty", "isEmpty() const", typeof(bool));
        }
        /// <remarks>
        ///  Creation of blank nodes is not supported by the SparqlModel.
        ///  \return an invalid Node
        ///              </remarks>        <short>    Creation of blank nodes is not supported by the SparqlModel.</short>
        [SmokeMethod("createBlankNode()")]
        public override Soprano.Node CreateBlankNode() {
            return (Soprano.Node) interceptor.Invoke("createBlankNode", "createBlankNode()", typeof(Soprano.Node));
        }
        ~SparqlModel() {
            interceptor.Invoke("~SparqlModel", "~SparqlModel()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~SparqlModel", "~SparqlModel()", typeof(void));
        }
        protected new ISparqlModelSignals Emit {
            get { return (ISparqlModelSignals) Q_EMIT; }
        }
    }

    public interface ISparqlModelSignals : Soprano.IModelSignals {
    }
}
