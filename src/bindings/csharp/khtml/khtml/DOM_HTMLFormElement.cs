//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>FORM</code> element encompasses behavior similar to a
	///  collection and an element. It provides direct access to the
	///  contained input elements as well as the attributes of the form
	///  element. See the <a
	///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#edef-FORM">
	///  FORM element definition </a> in HTML 4.0.
	///  </remarks>		<short>    The <code>FORM</code> element encompasses behavior similar to a  collection and an element.</short>
	[SmokeClass("DOM::HTMLFormElement")]
	public class HTMLFormElement : DOM.HTMLElement, IDisposable {
 		protected HTMLFormElement(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(HTMLFormElement), this);
		}
		// DOM::HTMLFormElement* HTMLFormElement(DOM::HTMLFormElementImpl* arg1); >>>> NOT CONVERTED
		public HTMLFormElement() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLFormElement", "HTMLFormElement()", typeof(void));
		}
		public HTMLFormElement(DOM.HTMLFormElement other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLFormElement#", "HTMLFormElement(const DOM::HTMLFormElement&)", typeof(void), typeof(DOM.HTMLFormElement), other);
		}
		public HTMLFormElement(DOM.Node other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLFormElement#", "HTMLFormElement(const DOM::Node&)", typeof(void), typeof(DOM.Node), other);
		}
		/// <remarks>
		///  Returns a collection of all control elements in the form.
		///      </remarks>		<short>    Returns a collection of all control elements in the form.</short>
		public DOM.HTMLCollection Elements() {
			return (DOM.HTMLCollection) interceptor.Invoke("elements", "elements() const", typeof(DOM.HTMLCollection));
		}
		/// <remarks>
		///  The number of form controls in the form.
		///      </remarks>		<short>    The number of form controls in the form.</short>
		public long Length() {
			return (long) interceptor.Invoke("length", "length() const", typeof(long));
		}
		/// <remarks>
		///  Names the form.
		///      </remarks>		<short>    Names the form.</short>
		public DOM.DOMString Name() {
			return (DOM.DOMString) interceptor.Invoke("name", "name() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see name
		///      </remarks>		<short>    see name      </short>
		public void SetName(DOM.DOMString arg1) {
			interceptor.Invoke("setName#", "setName(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  List of character sets supported by the server. See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-accept-charset">
		///  accept-charset attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    List of character sets supported by the server.</short>
		public DOM.DOMString AcceptCharset() {
			return (DOM.DOMString) interceptor.Invoke("acceptCharset", "acceptCharset() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see acceptCharset
		///      </remarks>		<short>    see acceptCharset      </short>
		public void SetAcceptCharset(DOM.DOMString arg1) {
			interceptor.Invoke("setAcceptCharset#", "setAcceptCharset(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  Server-side form handler. See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-action">
		///  action attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    Server-side form handler.</short>
		public DOM.DOMString Action() {
			return (DOM.DOMString) interceptor.Invoke("action", "action() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see action
		///      </remarks>		<short>    see action      </short>
		public void SetAction(DOM.DOMString arg1) {
			interceptor.Invoke("setAction#", "setAction(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  The content type of the submitted form, generally
		///  "application/x-www-form-urlencoded". See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-enctype">
		///  enctype attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    The content type of the submitted form, generally  "application/x-www-form-urlencoded".</short>
		public DOM.DOMString Enctype() {
			return (DOM.DOMString) interceptor.Invoke("enctype", "enctype() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see enctype
		///      </remarks>		<short>    see enctype      </short>
		public void SetEnctype(DOM.DOMString arg1) {
			interceptor.Invoke("setEnctype#", "setEnctype(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  HTTP method used to submit form. See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-method">
		///  method attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    HTTP method used to submit form.</short>
		public DOM.DOMString Method() {
			return (DOM.DOMString) interceptor.Invoke("method", "method() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see method
		///      </remarks>		<short>    see method      </short>
		public void SetMethod(DOM.DOMString arg1) {
			interceptor.Invoke("setMethod#", "setMethod(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  Frame to render the resource in. See the <a
		///  href="http://www.w3.org/TR/REC-html40/present/frames.html#adef-target">
		///  target attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    Frame to render the resource in.</short>
		public DOM.DOMString Target() {
			return (DOM.DOMString) interceptor.Invoke("target", "target() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see target
		///      </remarks>		<short>    see target      </short>
		public void SetTarget(DOM.DOMString arg1) {
			interceptor.Invoke("setTarget#", "setTarget(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  Submits the form. It performs the same action as a submit
		///  button.
		///      </remarks>		<short>    Submits the form.</short>
		public void Submit() {
			interceptor.Invoke("submit", "submit()", typeof(void));
		}
		/// <remarks>
		///  Restores a form element's default values. It performs the same
		///  action as a reset button.
		///      </remarks>		<short>    Restores a form element's default values.</short>
		public void Reset() {
			interceptor.Invoke("reset", "reset()", typeof(void));
		}
		~HTMLFormElement() {
			interceptor.Invoke("~HTMLFormElement", "~HTMLFormElement()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~HTMLFormElement", "~HTMLFormElement()", typeof(void));
		}
	}
}
