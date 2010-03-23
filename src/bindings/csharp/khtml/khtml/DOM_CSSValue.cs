//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>CSSValue</code> interface represents a simple or a
	///  complexe value.
	///  </remarks>		<short>    The <code>CSSValue</code> interface represents a simple or a  complexe value.</short>
	[SmokeClass("DOM::CSSValue")]
	public class CSSValue : Object, IDisposable {
		protected SmokeInvocation interceptor = null;
		private IntPtr smokeObject;
		protected CSSValue(Type dummy) {}
		protected void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(CSSValue), this);
		}
		/// <remarks>
		///  An integer indicating which type of unit applies to the value.
		///   All CSS2 constants are not supposed to be required by the
		///  implementation since all CSS2 interfaces are optionals.
		///      </remarks>		<short>    An integer indicating which type of unit applies to the value.</short>
		public enum UnitTypes {
			CSS_INHERIT = 0,
			CSS_PRIMITIVE_VALUE = 1,
			CSS_VALUE_LIST = 2,
			CSS_CUSTOM = 3,
			CSS_INITIAL = 4,
		}
		// DOM::CSSValue* CSSValue(DOM::CSSValueImpl* arg1); >>>> NOT CONVERTED
		public CSSValue() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSValue", "CSSValue()", typeof(void));
		}
		public CSSValue(DOM.CSSValue other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSValue#", "CSSValue(const DOM::CSSValue&)", typeof(void), typeof(DOM.CSSValue), other);
		}
		/// <remarks>
		///  A string representation of the current value.
		///      </remarks>		<short>    A string representation of the current value.</short>
		public DOM.DOMString CssText() {
			return (DOM.DOMString) interceptor.Invoke("cssText", "cssText() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see cssText
		///      </remarks>		<short>    see cssText </short>
		public void SetCssText(DOM.DOMString arg1) {
			interceptor.Invoke("setCssText#", "setCssText(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  A code defining the type of the value as defined above.
		///      </remarks>		<short>    A code defining the type of the value as defined above.</short>
		public ushort CssValueType() {
			return (ushort) interceptor.Invoke("cssValueType", "cssValueType() const", typeof(ushort));
		}
		/// <remarks>
		///  not part of the DOM
		///      </remarks>		<short>   </short>
		public bool IsCSSValueList() {
			return (bool) interceptor.Invoke("isCSSValueList", "isCSSValueList() const", typeof(bool));
		}
		public bool IsCSSPrimitiveValue() {
			return (bool) interceptor.Invoke("isCSSPrimitiveValue", "isCSSPrimitiveValue() const", typeof(bool));
		}
		public bool IsNull() {
			return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
		}
		~CSSValue() {
			interceptor.Invoke("~CSSValue", "~CSSValue()", typeof(void));
		}
		public void Dispose() {
			interceptor.Invoke("~CSSValue", "~CSSValue()", typeof(void));
		}
	}
}
