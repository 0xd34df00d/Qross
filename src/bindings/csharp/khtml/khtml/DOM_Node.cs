//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>Node</code> interface is the primary datatype for the
	///  entire Document Object Model. It represents a single node in the
	///  document tree. While all objects implementing the <code>Node</code>
	///  interface expose methods for dealing with children, not all
	///  objects implementing the <code>Node</code> interface may have
	///  children. For example, <code>Text</code> nodes may not have
	///  children, and adding children to such nodes results in a
	///  <code>DOMException</code> being raised.
	///   The attributes <code>nodeName</code> , <code>nodeValue</code>
	///  and <code>attributes</code> are included as a mechanism to get at
	///  node information without casting down to the specific derived
	///  interface. In cases where there is no obvious mapping of these
	///  attributes for a specific <code>nodeType</code> (e.g.,
	///  <code>nodeValue</code> for an Element or <code>attributes</code> for a
	///  Comment), this returns <code>null</code> . Note that the
	///  specialized interfaces may contain additional and more convenient
	///  mechanisms to get and set the relevant information.
	///  </remarks>		<short>    The <code>Node</code> interface is the primary datatype for the  entire Document Object Model.</short>
	[SmokeClass("DOM::Node")]
	public class Node : Object, IDisposable {
		protected SmokeInvocation interceptor = null;
		private IntPtr smokeObject;
		protected Node(Type dummy) {}
		protected void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(Node), this);
		}
		private static SmokeInvocation staticInterceptor = null;
		static Node() {
			staticInterceptor = new SmokeInvocation(typeof(Node), null);
		}
		/// <remarks>
		///  An integer indicating which type of node this is.
		///  <p>The values of <code>nodeName</code>, <code>nodeValue</code>,
		///   and <code>attributes</code> vary according to the node type as follows:
		///    <table  border="1">
		///      <tr>
		///        <td></td>
		///        <td>nodeName</td>
		///        <td>nodeValue</td>
		///        <td>attributes</td>
		///      </tr>
		///      <tr>
		///        <td>Element</td>
		///        <td>tagName</td>
		///        <td>null</td>
		///        <td>NamedNodeMap</td>
		///      </tr>
		///      <tr>
		///        <td>Attr</td>
		///        <td>name of attribute</td>
		///        <td>value of attribute</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>Text</td>
		///        <td>#text</td>
		///        <td>content of the text node</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>CDATASection</td>
		///        <td>#cdata-section</td>
		///        <td>content of the CDATA Section</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>EntityReference</td>
		///        <td>name of entity referenced</td>
		///        <td>null</td>
		///        <td>null</td>
		///        </tr>
		///      <tr>
		///        <td>Entity</td>
		///        <td>entity name</td>
		///        <td>null</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>ProcessingInstruction</td>
		///        <td>target</td>
		///        <td>entire content excluding the target</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>Comment</td>
		///        <td>#comment</td>
		///        <td>content of the comment</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>Document</td>
		///        <td>#document</td>
		///        <td>null</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>DocumentType</td>
		///        <td>document type name</td>
		///        <td>null</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>DocumentFragment</td>
		///        <td>#document-fragment</td>
		///        <td>null</td>
		///        <td>null</td>
		///      </tr>
		///      <tr>
		///        <td>Notation</td>
		///        <td>notation name</td>
		///        <td>null</td>
		///        <td>null</td>
		///      </tr>
		///    </table>
		///  </p>
		///      </remarks>		<short>    An integer indicating which type of node this is.</short>
		public enum NodeType {
			ELEMENT_NODE = 1,
			ATTRIBUTE_NODE = 2,
			TEXT_NODE = 3,
			CDATA_SECTION_NODE = 4,
			ENTITY_REFERENCE_NODE = 5,
			ENTITY_NODE = 6,
			PROCESSING_INSTRUCTION_NODE = 7,
			COMMENT_NODE = 8,
			DOCUMENT_NODE = 9,
			DOCUMENT_TYPE_NODE = 10,
			DOCUMENT_FRAGMENT_NODE = 11,
			NOTATION_NODE = 12,
		}
		// DOM::Node* Node(DOM::NodeImpl* arg1); >>>> NOT CONVERTED
		public Node() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("Node", "Node()", typeof(void));
		}
		public Node(DOM.Node other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("Node#", "Node(const DOM::Node&)", typeof(void), typeof(DOM.Node), other);
		}
		public override bool Equals(object o) {
			if (!(o is Node)) { return false; }
			return this == (Node) o;
		}
		public override int GetHashCode() {
			return interceptor.GetHashCode();
		}
		/// <remarks>
		///  The name of this node, depending on its type; see the table
		///  above.
		///      </remarks>		<short>    The name of this node, depending on its type; see the table  above.</short>
		public DOM.DOMString NodeName() {
			return (DOM.DOMString) interceptor.Invoke("nodeName", "nodeName() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  The value of this node, depending on its type; see the table
		///  above.
		///      </remarks>		<short>    The value of this node, depending on its type; see the table  above.</short>
		public DOM.DOMString NodeValue() {
			return (DOM.DOMString) interceptor.Invoke("nodeValue", "nodeValue() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see nodeValue
		///      </remarks>		<short>    see nodeValue </short>
		public void SetNodeValue(DOM.DOMString arg1) {
			interceptor.Invoke("setNodeValue#", "setNodeValue(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  A code representing the type of the underlying object, as
		///  defined above.
		///      </remarks>		<short>    A code representing the type of the underlying object, as  defined above.</short>
		public ushort nodeType() {
			return (ushort) interceptor.Invoke("nodeType", "nodeType() const", typeof(ushort));
		}
		/// <remarks>
		///  The parent of this node. All nodes, except <code>Document</code>
		///  , <code>DocumentFragment</code> , and <code>Attr</code>
		///  may have a parent. However, if a node has just been
		///  created and not yet added to the tree, or if it has been
		///  removed from the tree, this is <code>null</code> .
		///      </remarks>		<short>    The parent of this node.</short>
		public DOM.Node ParentNode() {
			return (DOM.Node) interceptor.Invoke("parentNode", "parentNode() const", typeof(DOM.Node));
		}
		/// <remarks>
		///  A <code>ArrayList</code> that contains all children of this
		///  node. If there are no children, this is a <code>ArrayList</code>
		///  containing no nodes. The content of the returned
		///  <code>ArrayList</code> is &quot;live&quot; in the sense that, for
		///  instance, changes to the children of the node object that it
		///  was created from are immediately reflected in the nodes
		///  returned by the <code>ArrayList</code> accessors; it is not a
		///  static snapshot of the content of the node. This is true for
		///  every <code>ArrayList</code> , including the ones returned by
		///  the <code>getElementsByTagName</code> method.
		///      </remarks>		<short>    A <code>NodeList</code> that contains all children of this  node.</short>
		public DOM.NodeList ChildNodes() {
			return (DOM.NodeList) interceptor.Invoke("childNodes", "childNodes() const", typeof(DOM.NodeList));
		}
		/// <remarks>
		///  The first child of this node. If there is no such node, this
		///  returns <code>null</code> .
		///      </remarks>		<short>    The first child of this node.</short>
		public DOM.Node FirstChild() {
			return (DOM.Node) interceptor.Invoke("firstChild", "firstChild() const", typeof(DOM.Node));
		}
		/// <remarks>
		///  The last child of this node. If there is no such node, this
		///  returns <code>null</code> .
		///      </remarks>		<short>    The last child of this node.</short>
		public DOM.Node LastChild() {
			return (DOM.Node) interceptor.Invoke("lastChild", "lastChild() const", typeof(DOM.Node));
		}
		/// <remarks>
		///  The node immediately preceding this node. If there is no such
		///  node, this returns <code>null</code> .
		///      </remarks>		<short>    The node immediately preceding this node.</short>
		public DOM.Node PreviousSibling() {
			return (DOM.Node) interceptor.Invoke("previousSibling", "previousSibling() const", typeof(DOM.Node));
		}
		/// <remarks>
		///  The node immediately following this node. If there is no such
		///  node, this returns <code>null</code> .
		///      </remarks>		<short>    The node immediately following this node.</short>
		public DOM.Node NextSibling() {
			return (DOM.Node) interceptor.Invoke("nextSibling", "nextSibling() const", typeof(DOM.Node));
		}
		/// <remarks>
		///  A <code>NamedNodeMap</code> containing the attributes of this
		///  node (if it is an <code>Element</code> ) or <code>null</code>
		///  otherwise.
		///      </remarks>		<short>    A <code>NamedNodeMap</code> containing the attributes of this  node (if it is an <code>Element</code> ) or <code>null</code>  otherwise.</short>
		public DOM.NamedNodeMap Attributes() {
			return (DOM.NamedNodeMap) interceptor.Invoke("attributes", "attributes() const", typeof(DOM.NamedNodeMap));
		}
		/// <remarks>
		///  The <code>Document</code> object associated with this node.
		///  This is also the <code>Document</code> object used to create
		///  new nodes. When this node is a <code>Document</code> this is
		///  <code>null</code> .
		///      </remarks>		<short>    The <code>Document</code> object associated with this node.</short>
		public DOM.Document OwnerDocument() {
			return (DOM.Document) interceptor.Invoke("ownerDocument", "ownerDocument() const", typeof(DOM.Document));
		}
		/// <remarks>
		///  Inserts the node <code>newChild</code> before the existing
		///  child node <code>refChild</code> . If <code>refChild</code>
		///  is <code>null</code> , insert <code>newChild</code> at the
		///  end of the list of children.
		///   If <code>newChild</code> is a <code>DocumentFragment</code>
		///  object, all of its children are inserted, in the same
		///  order, before <code>refChild</code> . If the <code>newChild</code>
		///  is already in the tree, it is first removed.
		/// <param> name="newChild" The node to insert.
		/// </param><param> name="refChild" The reference node, i.e., the node before which
		///  the new node must be inserted.
		/// </param>  WRONG_DOCUMENT_ERR: Raised if <code>newChild</code> was
		///  created from a different document than the one that created
		///  this node.
		///   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
		///   NOT_FOUND_ERR: Raised if <code>refChild</code> is not a
		///  child of this node.
		///      </remarks>		<return> The node being inserted.
		/// </return>
		/// 		<short>    Inserts the node <code>newChild</code> before the existing  child node <code>refChild</code> .</short>
		public DOM.Node InsertBefore(DOM.Node newChild, DOM.Node refChild) {
			return (DOM.Node) interceptor.Invoke("insertBefore##", "insertBefore(const DOM::Node&, const DOM::Node&)", typeof(DOM.Node), typeof(DOM.Node), newChild, typeof(DOM.Node), refChild);
		}
		/// <remarks>
		///  Replaces the child node <code>oldChild</code> with
		///  <code>newChild</code> in the list of children, and returns the
		///  <code>oldChild</code> node. If the <code>newChild</code> is
		///  already in the tree, it is first removed.
		/// <param> name="newChild" The new node to put in the child list.
		/// </param><param> name="oldChild" The node being replaced in the list.
		/// </param>  WRONG_DOCUMENT_ERR: Raised if <code>newChild</code> was
		///  created from a different document than the one that created
		///  this node.
		///   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
		///   NOT_FOUND_ERR: Raised if <code>oldChild</code> is not a
		///  child of this node.
		///      </remarks>		<return> The node replaced.
		/// </return>
		/// 		<short>    Replaces the child node <code>oldChild</code> with  <code>newChild</code> in the list of children, and returns the  <code>oldChild</code> node.</short>
		public DOM.Node ReplaceChild(DOM.Node newChild, DOM.Node oldChild) {
			return (DOM.Node) interceptor.Invoke("replaceChild##", "replaceChild(const DOM::Node&, const DOM::Node&)", typeof(DOM.Node), typeof(DOM.Node), newChild, typeof(DOM.Node), oldChild);
		}
		/// <remarks>
		///  Removes the child node indicated by <code>oldChild</code>
		///  from the list of children, and returns it.
		/// <param> name="oldChild" The node being removed.
		/// </param>  NOT_FOUND_ERR: Raised if <code>oldChild</code> is not a
		///  child of this node.
		///      </remarks>		<return> The node removed.
		/// </return>
		/// 		<short>    Removes the child node indicated by <code>oldChild</code>  from the list of children, and returns it.</short>
		public DOM.Node RemoveChild(DOM.Node oldChild) {
			return (DOM.Node) interceptor.Invoke("removeChild#", "removeChild(const DOM::Node&)", typeof(DOM.Node), typeof(DOM.Node), oldChild);
		}
		/// <remarks>
		///  Adds the node <code>newChild</code> to the end of the list of
		///  children of this node. If the <code>newChild</code> is
		///  already in the tree, it is first removed.
		/// <param> name="newChild" The node to add.
		/// </param>  If it is a <code>DocumentFragment</code> object, the entire
		///  contents of the document fragment are moved into the child list
		///  of this node
		///   WRONG_DOCUMENT_ERR: Raised if <code>newChild</code> was
		///  created from a different document than the one that created
		///  this node.
		///   NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
		///      </remarks>		<return> The node added.
		/// </return>
		/// 		<short>    Adds the node <code>newChild</code> to the end of the list of  children of this node.</short>
		public DOM.Node AppendChild(DOM.Node newChild) {
			return (DOM.Node) interceptor.Invoke("appendChild#", "appendChild(const DOM::Node&)", typeof(DOM.Node), typeof(DOM.Node), newChild);
		}
		/// <remarks>
		///  This is a convenience method to allow easy determination of
		///  whether a node has any children.
		///      </remarks>		<return> <code>true</code> if the node has any children,
		///  <code>false</code> if the node has no children.
		/// </return>
		/// 		<short>    This is a convenience method to allow easy determination of  whether a node has any children.</short>
		public bool HasChildNodes() {
			return (bool) interceptor.Invoke("hasChildNodes", "hasChildNodes()", typeof(bool));
		}
		/// <remarks>
		///  Returns a duplicate of this node, i.e., serves as a generic
		///  copy constructor for nodes. The duplicate node has no parent (
		///  <code>parentNode</code> returns <code>null</code> .).
		///   Cloning an <code>Element</code> copies all attributes and
		///  their values, including those generated by the XML processor to
		///  represent defaulted attributes, but this method does not copy
		///  any text it contains unless it is a deep clone, since the text
		///  is contained in a child <code>Text</code> node. Cloning any
		///  other type of node simply returns a copy of this node.
		/// <param> name="deep" If <code>true</code> , recursively clone the
		///  subtree under the specified node; if <code>false</code> ,
		///  clone only the node itself (and its attributes, if it is an
		///  <code>Element</code> ).
		/// </param>     </remarks>		<return> The duplicate node.
		/// </return>
		/// 		<short>    Returns a duplicate of this node, i.</short>
		public DOM.Node CloneNode(bool deep) {
			return (DOM.Node) interceptor.Invoke("cloneNode$", "cloneNode(bool)", typeof(DOM.Node), typeof(bool), deep);
		}
		/// <remarks>
		///  Modified in DOM Level 2
		///  Puts all Text nodes in the full depth of the sub-tree underneath this
		///  Node, including attribute nodes, into a "normal" form where only
		///  structure (e.g., elements, comments, processing instructions, CDATA
		///  sections, and entity references) separates Text nodes, i.e., there are
		///  neither adjacent Text nodes nor empty Text nodes. This can be used to
		///  ensure that the DOM view of a document is the same as if it were saved
		///  and re-loaded, and is useful when operations (such as XPointer
		///  [XPointer] lookups) that depend on a particular document tree structure
		///  are to be used.
		///  Note: In cases where the document contains CDATASections, the normalize
		///  operation alone may not be sufficient, since XPointers do not
		///  differentiate between Text nodes and CDATASection nodes.
		///      </remarks>		<short>    Modified in DOM Level 2 </short>
		public void Normalize() {
			interceptor.Invoke("normalize", "normalize()", typeof(void));
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  Tests whether the DOM implementation implements a specific feature and
		///  that feature is supported by this node.
		/// <param> name="feature" The name of the feature to test. This is the same name
		///  which can be passed to the method hasFeature on DOMImplementation.
		/// </param><param> name="version" This is the version number of the feature to test. In
		///  Level 2, version 1, this is the string "2.0". If the version is not
		///  specified, supporting any version of the feature will cause the method
		///  to return true.
		/// </param></remarks>		<return> Returns true if the specified feature is supported on this node,
		///  false otherwise.
		///      </return>
		/// 		<short>    Introduced in DOM Level 2 </short>
		public bool IsSupported(DOM.DOMString feature, DOM.DOMString version) {
			return (bool) interceptor.Invoke("isSupported##", "isSupported(const DOM::DOMString&, const DOM::DOMString&) const", typeof(bool), typeof(DOM.DOMString), feature, typeof(DOM.DOMString), version);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  The namespace URI of this node, or null if it is unspecified.
		///  This is not a computed value that is the result of a namespace lookup
		///  based on an examination of the namespace declarations in scope. It is
		///  merely the namespace URI given at creation time. For nodes of any type
		///  other than ELEMENT_NODE and ATTRIBUTE_NODE and nodes created with a DOM
		///  Level 1 method, such as createElement from the Document interface, this
		///  is always null.
		///  Note: Per the Namespaces in XML Specification [Namespaces] an attribute
		///  does not inherit its namespace from the element it is attached to. If an
		///  attribute is not explicitly given a namespace, it simply has no
		///  namespace.
		///      </remarks>		<short>    Introduced in DOM Level 2 </short>
		public DOM.DOMString NamespaceURI() {
			return (DOM.DOMString) interceptor.Invoke("namespaceURI", "namespaceURI() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  The namespace prefix of this node, or null if it is unspecified.
		///  Note that setting this attribute, when permitted, changes the nodeName
		///  attribute, which holds the qualified name, as well as the tagName and
		///  name attributes of the Element and Attr interfaces, when applicable.
		///  Note also that changing the prefix of an attribute that is known to have
		///  a default value, does not make a new attribute with the default value
		///  and the original prefix appear, since the namespaceURI and localName do
		///  not change.
		///  For nodes of any type other than ELEMENT_NODE and ATTRIBUTE_NODE and
		///  nodes created with a DOM Level 1 method, such as createElement from the
		///  Document interface, this is always null.
		///      </remarks>		<short>    Introduced in DOM Level 2 </short>
		public DOM.DOMString Prefix() {
			return (DOM.DOMString) interceptor.Invoke("prefix", "prefix() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see prefix
		///  NO_MODIFICATION_ALLOWED_ERR: Raised if this node is readonly.
		///  NAMESPACE_ERR: Raised if the specified prefix is malformed, if the
		///  namespaceURI of this node is null, if the specified prefix is "xml" and
		///  the namespaceURI of this node is different from
		///  "http://www.w3.org/XML/1998/namespace", if this node is an attribute and
		///  the specified prefix is "xmlns" and the namespaceURI of this node is
		///  different from "http://www.w3.org/2000/xmlns/", or if this node is an
		///  attribute and the qualifiedName of this node is "xmlns" [Namespaces].
		///      </remarks>		<short>    see prefix </short>
		public void SetPrefix(DOM.DOMString prefix) {
			interceptor.Invoke("setPrefix#", "setPrefix(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), prefix);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  Returns the local part of the qualified name of this node.
		///  For nodes of any type other than ELEMENT_NODE and ATTRIBUTE_NODE and
		///  nodes created with a DOM Level 1 method, such as createElement from the
		///  Document interface, this is always null.
		///      </remarks>		<short>    Introduced in DOM Level 2 </short>
		public DOM.DOMString LocalName() {
			return (DOM.DOMString) interceptor.Invoke("localName", "localName() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  Returns whether this node (if it is an element) has any attributes.
		/// </remarks>		<return> a boolean. True if this node has any attributes, false otherwise.
		///   Introduced in DOM Level 2
		///      </return>
		/// 		<short>    Returns whether this node (if it is an element) has any attributes.</short>
		public bool HasAttributes() {
			return (bool) interceptor.Invoke("hasAttributes", "hasAttributes()", typeof(bool));
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  This method is from the EventTarget interface
		///  This method allows the registration of event listeners on the event
		///  target. If an EventListener is added to an EventTarget while it is
		///  processing an event, it will not be triggered by the current actions but
		///  may be triggered during a later stage of event flow, such as the
		///  bubbling phase.
		///  If multiple identical EventListeners are registered on the same
		///  EventTarget with the same parameters the duplicate instances are
		///  discarded. They do not cause the EventListener to be called twice and
		///  since they are discarded they do not need to be removed with the
		///  removeEventListener method. Parameters
		/// <param> name="type" The event type for which the user is registering
		/// </param><param> name="listener" The listener parameter takes an interface implemented by
		///  the user which contains the methods to be called when the event occurs.
		/// </param><param> name="useCapture" If true, useCapture indicates that the user wishes to
		///  initiate capture. After initiating capture, all events of the specified
		///  type will be dispatched to the registered EventListener before being
		///  dispatched to any EventTargets beneath them in the tree. Events which
		///  are bubbling upward through the tree will not trigger an EventListener
		///  designated to use capture.
		///      </param></remarks>		<short>    Introduced in DOM Level 2  This method is from the EventTarget interface </short>
		public void AddEventListener(DOM.DOMString type, DOM.EventListener listener, bool useCapture) {
			interceptor.Invoke("addEventListener##$", "addEventListener(const DOM::DOMString&, DOM::EventListener*, const bool)", typeof(void), typeof(DOM.DOMString), type, typeof(DOM.EventListener), listener, typeof(bool), useCapture);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  This method is from the EventTarget interface
		///  This method allows the removal of event listeners from the event target.
		///  If an EventListener is removed from an EventTarget while it is
		///  processing an event, it will not be triggered by the current actions.
		///  EventListeners can never be invoked after being removed.
		///  Calling removeEventListener with arguments which do not identify any
		///  currently registered EventListener on the EventTarget has no effect.
		/// <param> name="type" Specifies the event type of the EventListener being removed.
		/// </param><param> name="listener" The EventListener parameter indicates the EventListener
		///  to be removed.
		/// </param><param> name="useCapture" Specifies whether the EventListener being removed was
		///  registered as a capturing listener or not. If a listener was registered
		///  twice, one with capture and one without, each must be removed
		///  separately. Removal of a capturing listener does not affect a
		///  non-capturing version of the same listener, and vice versa.
		///      </param></remarks>		<short>    Introduced in DOM Level 2  This method is from the EventTarget interface </short>
		public void RemoveEventListener(DOM.DOMString type, DOM.EventListener listener, bool useCapture) {
			interceptor.Invoke("removeEventListener##$", "removeEventListener(const DOM::DOMString&, DOM::EventListener*, bool)", typeof(void), typeof(DOM.DOMString), type, typeof(DOM.EventListener), listener, typeof(bool), useCapture);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  This method is from the EventTarget interface
		///  This method allows the dispatch of events into the implementations event
		///  model. Events dispatched in this manner will have the same capturing and
		///  bubbling behavior as events dispatched directly by the implementation.
		///  The target of the event is the EventTarget on which dispatchEvent is
		///  called.
		/// <param> name="evt" Specifies the event type, behavior, and contextual
		///  information to be used in processing the event.
		/// </param></remarks>		<return> The return value of dispatchEvent indicates whether any of the
		///  listeners which handled the event called preventDefault. If
		///  preventDefault was called the value is false, else the value is true.
		/// </return>
		/// 		<short>    Introduced in DOM Level 2  This method is from the EventTarget interface </short>
		public bool DispatchEvent(DOM.Event evt) {
			return (bool) interceptor.Invoke("dispatchEvent#", "dispatchEvent(const DOM::Event&)", typeof(bool), typeof(DOM.Event), evt);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  This attribute returns the text content of this node and its
		///  descendants. When it is defined to be null, setting it has no
		///  effect. On setting, any possible children this node may have
		///  are removed and, if it the new string is not empty or null,
		///  replaced by a single Text node containing the string this
		///  attribute is set to.
		///  On getting, no serialization is performed, the returned string
		///  does not contain any markup. No whitespace normalization is
		///  performed and the returned string does not contain the white
		///  spaces in element content (see the attribute
		///  Text.isElementContentWhitespace). Similarly, on setting, no
		///  parsing is performed either, the input string is taken as pure
		///  textual content.
		///      </remarks>		<short>    Introduced in DOM Level 2 </short>
		public DOM.DOMString TextContent() {
			return (DOM.DOMString) interceptor.Invoke("textContent", "textContent() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see textContent()
		/// </remarks>		<short>    see textContent() </short>
		public void SetTextContent(DOM.DOMString text) {
			interceptor.Invoke("setTextContent#", "setTextContent(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), text);
		}
		/// <remarks>
		///  not part of the DOM.
		/// </remarks>		<return> the element id, in case this is an element, 0 otherwise
		///      </return>
		/// 		<short>   </short>
		public uint ElementId() {
			return (uint) interceptor.Invoke("elementId", "elementId() const", typeof(uint));
		}
		/// <remarks>
		///  tests if this Node is 0. Useful especially, if casting to a derived
		///  class:
		///  <pre>
		///  Node n = .....;
		///  // try to convert into an Element:
		///  Element e = n;
		///  if( e.isNull() )
		///    kDebug(300) << "node isn't an element node";
		///  </pre>
		///      </remarks>		<short>    tests if this Node is 0.</short>
		public bool IsNull() {
			return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
		}
		/// <remarks>
		///      </remarks>		<short>   </short>
		public ulong Index() {
			return (ulong) interceptor.Invoke("index", "index() const", typeof(ulong));
		}
		public void ApplyChanges() {
			interceptor.Invoke("applyChanges", "applyChanges()", typeof(void));
		}
		/// <remarks>
		///  not part of the DOM.
		/// </remarks>		<return> the exact coordinates and size of this element.
		///      </return>
		/// 		<short>    not part of the DOM.</short>
		public QRect GetRect() {
			return (QRect) interceptor.Invoke("getRect", "getRect()", typeof(QRect));
		}
		~Node() {
			interceptor.Invoke("~Node", "~Node()", typeof(void));
		}
		public void Dispose() {
			interceptor.Invoke("~Node", "~Node()", typeof(void));
		}
		public static bool operator==(Node lhs, DOM.Node other) {
			return (bool) staticInterceptor.Invoke("operator==#", "operator==(const DOM::Node&) const", typeof(bool), typeof(Node), lhs, typeof(DOM.Node), other);
		}
		public static bool operator!=(Node lhs, DOM.Node other) {
			return !(bool) staticInterceptor.Invoke("operator==#", "operator==(const DOM::Node&) const", typeof(bool), typeof(Node), lhs, typeof(DOM.Node), other);
		}
	}
}
