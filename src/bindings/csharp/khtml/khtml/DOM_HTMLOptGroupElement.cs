//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  Group options together in logical subdivisions. See the <a
	///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#edef-OPTGROUP">
	///  OPTGROUP element definition </a> in HTML 4.0.
	///  </remarks>		<short>    Group options together in logical subdivisions.</short>
	[SmokeClass("DOM::HTMLOptGroupElement")]
	public class HTMLOptGroupElement : DOM.HTMLElement, IDisposable {
 		protected HTMLOptGroupElement(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(HTMLOptGroupElement), this);
		}
		// DOM::HTMLOptGroupElement* HTMLOptGroupElement(DOM::HTMLOptGroupElementImpl* arg1); >>>> NOT CONVERTED
		public HTMLOptGroupElement() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLOptGroupElement", "HTMLOptGroupElement()", typeof(void));
		}
		public HTMLOptGroupElement(DOM.HTMLOptGroupElement other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLOptGroupElement#", "HTMLOptGroupElement(const DOM::HTMLOptGroupElement&)", typeof(void), typeof(DOM.HTMLOptGroupElement), other);
		}
		public HTMLOptGroupElement(DOM.Node other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLOptGroupElement#", "HTMLOptGroupElement(const DOM::Node&)", typeof(void), typeof(DOM.Node), other);
		}
		/// <remarks>
		///  The control is unavailable in this context. See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-disabled">
		///  disabled attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    The control is unavailable in this context.</short>
		public bool Disabled() {
			return (bool) interceptor.Invoke("disabled", "disabled() const", typeof(bool));
		}
		/// <remarks>
		///  see disabled
		///      </remarks>		<short>    see disabled      </short>
		public void SetDisabled(bool arg1) {
			interceptor.Invoke("setDisabled$", "setDisabled(bool)", typeof(void), typeof(bool), arg1);
		}
		/// <remarks>
		///  Assigns a label to this option group. See the <a
		///  href="http://www.w3.org/TR/REC-html40/interact/forms.html#adef-label-OPTGROUP">
		///  label attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    Assigns a label to this option group.</short>
		public DOM.DOMString Label() {
			return (DOM.DOMString) interceptor.Invoke("label", "label() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see label
		///      </remarks>		<short>    see label      </short>
		public void SetLabel(DOM.DOMString arg1) {
			interceptor.Invoke("setLabel#", "setLabel(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		~HTMLOptGroupElement() {
			interceptor.Invoke("~HTMLOptGroupElement", "~HTMLOptGroupElement()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~HTMLOptGroupElement", "~HTMLOptGroupElement()", typeof(void));
		}
	}
}
