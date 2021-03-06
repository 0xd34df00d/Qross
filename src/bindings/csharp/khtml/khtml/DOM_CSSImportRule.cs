//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>CSSImportRule</code> interface represents a <a
	///  href="http://www.w3.org/TR/REC-CSS2/cascade.html#at-import">
	///  <code>\@import</code> rule </a> within a CSS style sheet. The <code>\@import</code>
	///  rule is used to import style rules from other style sheets.
	///  </remarks>		<short>    The <code>CSSImportRule</code> interface represents a <a  href="http://www.</short>
	[SmokeClass("DOM::CSSImportRule")]
	public class CSSImportRule : DOM.CSSRule, IDisposable {
 		protected CSSImportRule(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(CSSImportRule), this);
		}
		// DOM::CSSImportRule* CSSImportRule(DOM::CSSImportRuleImpl* arg1); >>>> NOT CONVERTED
		public CSSImportRule() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSImportRule", "CSSImportRule()", typeof(void));
		}
		public CSSImportRule(DOM.CSSImportRule other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSImportRule#", "CSSImportRule(const DOM::CSSImportRule&)", typeof(void), typeof(DOM.CSSImportRule), other);
		}
		public CSSImportRule(DOM.CSSRule other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("CSSImportRule#", "CSSImportRule(const DOM::CSSRule&)", typeof(void), typeof(DOM.CSSRule), other);
		}
		/// <remarks>
		///  The location of the style sheet to be imported. The attribute
		///  will not contain the <code>"url</code>(...)" specifier around
		///  the URI.
		///      </remarks>		<short>    The location of the style sheet to be imported.</short>
		public DOM.DOMString Href() {
			return (DOM.DOMString) interceptor.Invoke("href", "href() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  A list of media types for which this style sheet may be used.
		///      </remarks>		<short>    A list of media types for which this style sheet may be used.</short>
		public DOM.MediaList Media() {
			return (DOM.MediaList) interceptor.Invoke("media", "media() const", typeof(DOM.MediaList));
		}
		/// <remarks>
		///  The style sheet referred to by this rule, if it has been
		///  loaded. The value of this attribute is null if the style sheet
		///  has not yet been loaded or if it will not be loaded (e.g. if
		///  the style sheet is for a media type not supported by the user
		///  agent).
		///      </remarks>		<short>    The style sheet referred to by this rule, if it has been  loaded.</short>
		public DOM.CSSStyleSheet StyleSheet() {
			return (DOM.CSSStyleSheet) interceptor.Invoke("styleSheet", "styleSheet() const", typeof(DOM.CSSStyleSheet));
		}
		~CSSImportRule() {
			interceptor.Invoke("~CSSImportRule", "~CSSImportRule()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~CSSImportRule", "~CSSImportRule()", typeof(void));
		}
	}
}
