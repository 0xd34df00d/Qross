//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  <code>TreeWalker</code> objects are used to navigate a document
	///  tree or subtree using the view of the document defined by its
	///  <code>whatToShow</code> flags and any filters that are defined
	///  for the <code>TreeWalker</code> . Any function which performs
	///  navigation using a <code>TreeWalker</code> will automatically
	///  support any view defined by a <code>TreeWalker</code> .
	///   Omitting nodes from the logical view of a subtree can result in a
	///  structure that is substantially different from the same subtree in
	///  the complete, unfiltered document. Nodes that are siblings in the
	///  TreeWalker view may be children of different, widely separated
	///  nodes in the original view. For instance, consider a Filter that
	///  skips all nodes except for Text nodes and the root node of a
	///  document. In the logical view that results, all text nodes will be
	///  siblings and appear as direct children of the root node, no matter
	///  how deeply nested the structure of the original document.
	///  </remarks>		<short>    <code>TreeWalker</code> objects are used to navigate a document  tree or subtree using the view of the document defined by its  <code>whatToShow</code> flags and any filters that are defined  for the <code>TreeWalker</code> .</short>
	[SmokeClass("DOM::TreeWalker")]
	public class TreeWalker : Object, IDisposable {
		protected SmokeInvocation interceptor = null;
		private IntPtr smokeObject;
		protected TreeWalker(Type dummy) {}
		protected void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(TreeWalker), this);
		}
		// DOM::TreeWalker* TreeWalker(DOM::TreeWalkerImpl* arg1); >>>> NOT CONVERTED
		public TreeWalker() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("TreeWalker", "TreeWalker()", typeof(void));
		}
		public TreeWalker(DOM.TreeWalker other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("TreeWalker#", "TreeWalker(const DOM::TreeWalker&)", typeof(void), typeof(DOM.TreeWalker), other);
		}
		/// <remarks>
		///  The root node of the TreeWalker, as specified when it was created.
		///      </remarks>		<short>    The root node of the TreeWalker, as specified when it was created.</short>
		public DOM.Node Root() {
			return (DOM.Node) interceptor.Invoke("root", "root()", typeof(DOM.Node));
		}
		/// <remarks>
		///  This attribute determines which node types are presented via the
		///  TreeWalker. The available set of constants is defined in the NodeFilter
		///  interface. Nodes not accepted by whatToShow will be skipped, but their
		///  children may still be considered. Note that this skip takes precedence
		///  over the filter, if any.
		///      </remarks>		<short>    This attribute determines which node types are presented via the  TreeWalker.</short>
		public ulong WhatToShow() {
			return (ulong) interceptor.Invoke("whatToShow", "whatToShow()", typeof(ulong));
		}
		/// <remarks>
		///  The filter used to screen nodes.
		///      </remarks>		<short>    The filter used to screen nodes.</short>
		public DOM.NodeFilter Filter() {
			return (DOM.NodeFilter) interceptor.Invoke("filter", "filter()", typeof(DOM.NodeFilter));
		}
		/// <remarks>
		///  The value of this flag determines whether the children of entity
		///  reference nodes are visible to the TreeWalker. If false, they and their
		///  descendents will be rejected. Note that this rejection takes precedence
		///  over whatToShow and the filter, if any.
		///  To produce a view of the document that has entity references expanded
		///  and does not expose the entity reference node itself, use the whatToShow
		///  flags to hide the entity reference node and set expandEntityReferences
		///  to true when creating the TreeWalker. To produce a view of the document
		///  that has entity reference nodes but no entity expansion, use the
		///  whatToShow flags to show the entity reference node and set
		///  expandEntityReferences to false.
		///      </remarks>		<short>    The value of this flag determines whether the children of entity  reference nodes are visible to the TreeWalker.</short>
		public bool ExpandEntityReferences() {
			return (bool) interceptor.Invoke("expandEntityReferences", "expandEntityReferences()", typeof(bool));
		}
		/// <remarks>
		///  The node at which the TreeWalker is currently positioned.
		///  Alterations to the DOM tree may cause the current node to no longer be
		///  accepted by the TreeWalker's associated filter. currentNode may also be
		///  explicitly set to any node, whether or not it is within the subtree
		///  specified by the root node or would be accepted by the filter and
		///  whatToShow flags. Further traversal occurs relative to currentNode even
		///  if it is not part of the current view, by applying the filters in the
		///  requested direction; if no traversal is possible, currentNode is not changed.
		/// </remarks>		<short>    The node at which the TreeWalker is currently positioned.</short>
		public DOM.Node CurrentNode() {
			return (DOM.Node) interceptor.Invoke("currentNode", "currentNode()", typeof(DOM.Node));
		}
		/// <remarks>
		///  see currentNode
		///      </remarks>		<short>    see currentNode      </short>
		public void SetCurrentNode(DOM.Node _currentNode) {
			interceptor.Invoke("setCurrentNode#", "setCurrentNode(const DOM::Node&)", typeof(void), typeof(DOM.Node), _currentNode);
		}
		/// <remarks>
		///  Moves to and returns the parent node of the current node. If
		///  there is no parent node, or if the current node is the root
		///  node from which this TreeWalker was created, retains the
		///  current position and returns null.
		///      </remarks>		<return> The new parent node, or null if the current node has no
		///  parent in the TreeWalker's logical view.
		/// </return>
		/// 		<short>    Moves to and returns the parent node of the current node.</short>
		public DOM.Node ParentNode() {
			return (DOM.Node) interceptor.Invoke("parentNode", "parentNode()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the first child of the
		///  current node, and returns the new node. If the current node has
		///  no children, returns <code>null</code> , and retains the
		///  current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no children.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the first child of the  current node, and returns the new node.</short>
		public DOM.Node FirstChild() {
			return (DOM.Node) interceptor.Invoke("firstChild", "firstChild()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the last child of the
		///  current node, and returns the new node. If the current node has
		///  no children, returns <code>null</code> , and retains the
		///  current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no children.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the last child of the  current node, and returns the new node.</short>
		public DOM.Node LastChild() {
			return (DOM.Node) interceptor.Invoke("lastChild", "lastChild()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the previous sibling of
		///  the current node, and returns the new node. If the current node
		///  has no previous sibling, returns <code>null</code> , and
		///  retains the current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no previous sibling.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the previous sibling of  the current node, and returns the new node.</short>
		public DOM.Node PreviousSibling() {
			return (DOM.Node) interceptor.Invoke("previousSibling", "previousSibling()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the next sibling of the
		///  current node, and returns the new node. If the current node has
		///  no next sibling, returns <code>null</code> , and retains the
		///  current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no next sibling.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the next sibling of the  current node, and returns the new node.</short>
		public DOM.Node NextSibling() {
			return (DOM.Node) interceptor.Invoke("nextSibling", "nextSibling()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the previous node in
		///  document order relative to the current node, and returns the
		///  new node. If the current node has no previous node, returns
		///  <code>null</code> , and retains the current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no previous node.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the previous node in  document order relative to the current node, and returns the  new node.</short>
		public DOM.Node PreviousNode() {
			return (DOM.Node) interceptor.Invoke("previousNode", "previousNode()", typeof(DOM.Node));
		}
		/// <remarks>
		///  Moves the <code>TreeWalker</code> to the next node in
		///  document order relative to the current node, and returns the
		///  new node. If the current node has no next node, returns
		///  <code>null</code> , and retains the current node.
		///      </remarks>		<return> The new node, or <code>null</code> if the current
		///  node has no next node.
		/// </return>
		/// 		<short>    Moves the <code>TreeWalker</code> to the next node in  document order relative to the current node, and returns the  new node.</short>
		public DOM.Node NextNode() {
			return (DOM.Node) interceptor.Invoke("nextNode", "nextNode()", typeof(DOM.Node));
		}
		public bool IsNull() {
			return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
		}
		~TreeWalker() {
			interceptor.Invoke("~TreeWalker", "~TreeWalker()", typeof(void));
		}
		public void Dispose() {
			interceptor.Invoke("~TreeWalker", "~TreeWalker()", typeof(void));
		}
	}
}
