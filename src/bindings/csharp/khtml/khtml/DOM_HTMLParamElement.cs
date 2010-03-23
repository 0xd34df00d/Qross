//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  Parameters fed to the <code>OBJECT</code> element. See the <a
	///  href="http://www.w3.org/TR/REC-html40/struct/objects.html#edef-PARAM">
	///  PARAM element definition </a> in HTML 4.0.
	///  </remarks>		<short>    Parameters fed to the <code>OBJECT</code> element.</short>
	[SmokeClass("DOM::HTMLParamElement")]
	public class HTMLParamElement : DOM.HTMLElement, IDisposable {
 		protected HTMLParamElement(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(HTMLParamElement), this);
		}
		// DOM::HTMLParamElement* HTMLParamElement(DOM::HTMLParamElementImpl* arg1); >>>> NOT CONVERTED
		public HTMLParamElement() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLParamElement", "HTMLParamElement()", typeof(void));
		}
		public HTMLParamElement(DOM.HTMLParamElement other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLParamElement#", "HTMLParamElement(const DOM::HTMLParamElement&)", typeof(void), typeof(DOM.HTMLParamElement), other);
		}
		public HTMLParamElement(DOM.Node other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("HTMLParamElement#", "HTMLParamElement(const DOM::Node&)", typeof(void), typeof(DOM.Node), other);
		}
		/// <remarks>
		///  The name of a run-time parameter. See the <a
		///  href="http://www.w3.org/TR/REC-html40/struct/objects.html#adef-name-PARAM">
		///  name attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    The name of a run-time parameter.</short>
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
		///  Content type for the <code>value</code> attribute when
		///  <code>valuetype</code> has the value "ref". See the <a
		///  href="http://www.w3.org/TR/REC-html40/struct/objects.html#adef-type-PARAM">
		///  type attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    Content type for the <code>value</code> attribute when  <code>valuetype</code> has the value "ref".</short>
		public DOM.DOMString type() {
			return (DOM.DOMString) interceptor.Invoke("type", "type() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see type
		///      </remarks>		<short>    see type      </short>
		public void SetType(DOM.DOMString arg1) {
			interceptor.Invoke("setType#", "setType(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  The value of a run-time parameter. See the <a
		///  href="http://www.w3.org/TR/REC-html40/struct/objects.html#adef-value-PARAM">
		///  value attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    The value of a run-time parameter.</short>
		public DOM.DOMString Value() {
			return (DOM.DOMString) interceptor.Invoke("value", "value() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see value
		///      </remarks>		<short>    see value      </short>
		public void SetValue(DOM.DOMString arg1) {
			interceptor.Invoke("setValue#", "setValue(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  Information about the meaning of the <code>value</code>
		///  attribute value. See the <a
		///  href="http://www.w3.org/TR/REC-html40/struct/objects.html#adef-valuetype">
		///  valuetype attribute definition </a> in HTML 4.0.
		///      </remarks>		<short>    Information about the meaning of the <code>value</code>  attribute value.</short>
		public DOM.DOMString ValueType() {
			return (DOM.DOMString) interceptor.Invoke("valueType", "valueType() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see valueType
		///      </remarks>		<short>    see valueType      </short>
		public void SetValueType(DOM.DOMString arg1) {
			interceptor.Invoke("setValueType#", "setValueType(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		~HTMLParamElement() {
			interceptor.Invoke("~HTMLParamElement", "~HTMLParamElement()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~HTMLParamElement", "~HTMLParamElement()", typeof(void));
		}
	}
}
