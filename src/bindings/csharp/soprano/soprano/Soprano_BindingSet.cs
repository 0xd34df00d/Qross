//Auto-generated by kalyptus. DO NOT EDIT.
namespace Soprano {
    using Soprano;
    using System;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  \class BindingSet bindingset.h Soprano/BindingSet
    ///  \brief Represents one set of bindings in the result of a select query.
    ///  BindingSet is mostly a convenience class for caching of query
    ///  results.
    ///  \sa QueryResultIterator
    ///  \author Sebastian Trueg <trueg@kde.org>
    ///      </remarks>        <short>    \class BindingSet bindingset.</short>
    [SmokeClass("Soprano::BindingSet")]
    public class BindingSet : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected BindingSet(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(BindingSet), this);
        }
        /// <remarks>
        ///  Create an emtpy set.
        ///          </remarks>        <short>    Create an emtpy set.</short>
        public BindingSet() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("BindingSet", "BindingSet()", typeof(void));
        }
        /// <remarks>
        ///  Copy constructor.
        ///          </remarks>        <short>    Copy constructor.</short>
        public BindingSet(Soprano.BindingSet other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("BindingSet#", "BindingSet(const Soprano::BindingSet&)", typeof(void), typeof(Soprano.BindingSet), other);
        }
        /// <remarks>
        ///  \return The names of the bound variables in this set.
        ///          </remarks>        <short>    \return The names of the bound variables in this set.</short>
        public List<string> BindingNames() {
            return (List<string>) interceptor.Invoke("bindingNames", "bindingNames() const", typeof(List<string>));
        }
        /// <remarks>
        ///  Get the binding for a variable by index.
        ///  \param offset The index of the requested variable.
        ///  \return The binding for the requested variable or and invalid
        ///  node if offset is out of bounds, i.e. bigger or equal to count().
        ///  \sa QueryResultIterator.Binding(int) const.
        ///          </remarks>        <short>    Get the binding for a variable by index.</short>
        public Soprano.Node Value(int offset) {
            return (Soprano.Node) interceptor.Invoke("value$", "value(int) const", typeof(Soprano.Node), typeof(int), offset);
        }
        /// <remarks>
        ///  Get the binding for a variable.
        ///  \param name The name of the requested variable.
        ///  \return The binding for the requested variable or and invalid
        ///  node if the bindings do not contain the variable.
        ///  \sa QueryResultIterator.Binding(string) const.
        ///          </remarks>        <short>    Get the binding for a variable.</short>
        public Soprano.Node Value(string name) {
            return (Soprano.Node) interceptor.Invoke("value$", "value(const QString&) const", typeof(Soprano.Node), typeof(string), name);
        }
        /// <remarks>
        ///  Check if a certain variable has a binding in this set.
        ///  \param name The variable name.
        ///  \return <pre>true</pre> if this set contains a binding for the 
        ///  variable name, <pre>false</pre> otherwise.
        ///          </remarks>        <short>    Check if a certain variable has a binding in this set.</short>
        public bool Contains(string name) {
            return (bool) interceptor.Invoke("contains$", "contains(const QString&) const", typeof(bool), typeof(string), name);
        }
        /// <remarks>
        ///  The number of bindings in this set.
        ///  \return The number of bindings.
        ///          </remarks>        <short>    The number of bindings in this set.</short>
        public int Count() {
            return (int) interceptor.Invoke("count", "count() const", typeof(int));
        }
        /// <remarks>
        ///  Insert a new binding into the set.
        ///          </remarks>        <short>    Insert a new binding into the set.</short>
        public void Insert(string name, Soprano.Node value) {
            interceptor.Invoke("insert$#", "insert(const QString&, const Soprano::Node&)", typeof(void), typeof(string), name, typeof(Soprano.Node), value);
        }
        /// <remarks>
        ///  Replaces a value in the binding set.
        ///  \since 2.3
        ///          </remarks>        <short>    Replaces a value in the binding set.</short>
        public void Replace(int offset, Soprano.Node value) {
            interceptor.Invoke("replace$#", "replace(int, const Soprano::Node&)", typeof(void), typeof(int), offset, typeof(Soprano.Node), value);
        }
        /// <remarks>
        ///  Replaces a value in the binding set.
        ///  \since 2.3
        ///          </remarks>        <short>    Replaces a value in the binding set.</short>
        public void Replace(string name, Soprano.Node value) {
            interceptor.Invoke("replace$#", "replace(const QString&, const Soprano::Node&)", typeof(void), typeof(string), name, typeof(Soprano.Node), value);
        }
        ~BindingSet() {
            interceptor.Invoke("~BindingSet", "~BindingSet()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~BindingSet", "~BindingSet()", typeof(void));
        }
    }
}
