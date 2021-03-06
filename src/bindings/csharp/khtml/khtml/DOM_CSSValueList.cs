//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>CSSValueList</code> interface provides the absraction
	///  of an ordered collection of CSS values.
	///  </remarks>		<short>    The <code>CSSValueList</code> interface provides the absraction  of an ordered collection of CSS values.</short>
	[SmokeClass("DOM::CSSValueList")]
	public class CSSValueList : DOM.CSSValue, IDisposable {
 		protected CSSValueList(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(CSSValueList), this);
		}
		// DOM::CSSValueList* CSSValueList(DOM::CSSValueListImpl* arg1); >>>> NOT CONVERTED
		public CSSValueList() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSValueList", "CSSValueList()", typeof(void));
		}
		public CSSValueList(DOM.CSSValueList other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSValueList#", "CSSValueList(const DOM::CSSValueList&)", typeof(void), typeof(DOM.CSSValueList), other);
		}
		public CSSValueList(DOM.CSSValue other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSValueList#", "CSSValueList(const DOM::CSSValue&)", typeof(void), typeof(DOM.CSSValue), other);
		}
		/// <remarks>
		///  The number of <code>CSSValue</code> s in the list. The range
		///  of valid values indices is <code>0</code> to <code>length-1</code>
		///  inclusive.
		///      </remarks>		<short>    The number of <code>CSSValue</code> s in the list.</short>
		public ulong Length() {
			return (ulong) interceptor.Invoke("length", "length() const", typeof(ulong));
		}
		/// <remarks>
		///  Used to retrieve a CSS rule by ordinal index. The order in this
		///  collection represents the order of the values in the CSS style
		///  property.
		/// <param> name="index" Index into the collection.
		/// </param>     </remarks>		<return> The style rule at the <code>index</code> position in
		///  the <code>CSSValueList</code> , or <code>null</code> if
		///  that is not valid index.
		/// </return>
		/// 		<short>    Used to retrieve a CSS rule by ordinal index.</short>
		public DOM.CSSValue Item(ulong index) {
			return (DOM.CSSValue) interceptor.Invoke("item$", "item(unsigned long)", typeof(DOM.CSSValue), typeof(ulong), index);
		}
		~CSSValueList() {
			interceptor.Invoke("~CSSValueList", "~CSSValueList()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~CSSValueList", "~CSSValueList()", typeof(void));
		}
	}
}
