//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>ProcessingInstruction</code> interface represents a
	///  &quot;processing instruction&quot;, used in XML as a way to keep
	///  processor-specific information in the text of the document.
	///  </remarks>		<short>    The <code>ProcessingInstruction</code> interface represents a  &quot;processing instruction&quot;, used in XML as a way to keep  processor-specific information in the text of the document.</short>
	[SmokeClass("DOM::ProcessingInstruction")]
	public class ProcessingInstruction : DOM.Node, IDisposable {
 		protected ProcessingInstruction(Type dummy) : base((Type) null) {}
		protected new void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(ProcessingInstruction), this);
		}
		// DOM::ProcessingInstruction* ProcessingInstruction(DOM::ProcessingInstructionImpl* arg1); >>>> NOT CONVERTED
		public ProcessingInstruction() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("ProcessingInstruction", "ProcessingInstruction()", typeof(void));
		}
		public ProcessingInstruction(DOM.ProcessingInstruction other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("ProcessingInstruction#", "ProcessingInstruction(const DOM::ProcessingInstruction&)", typeof(void), typeof(DOM.ProcessingInstruction), other);
		}
		public ProcessingInstruction(DOM.Node other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("ProcessingInstruction#", "ProcessingInstruction(const DOM::Node&)", typeof(void), typeof(DOM.Node), other);
		}
		/// <remarks>
		///  The target of this processing instruction. XML defines this as
		///  being the first token following the markup that begins the
		///  processing instruction.
		///      </remarks>		<short>    The target of this processing instruction.</short>
		public DOM.DOMString Target() {
			return (DOM.DOMString) interceptor.Invoke("target", "target() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  The content of this processing instruction. This is from the
		///  first non white space character after the target to the
		///  character immediately preceding the <code>?&gt;</code> .
		///      </remarks>		<short>    The content of this processing instruction.</short>
		public DOM.DOMString Data() {
			return (DOM.DOMString) interceptor.Invoke("data", "data() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see data
		///      </remarks>		<short>    see data </short>
		public void SetData(DOM.DOMString arg1) {
			interceptor.Invoke("setData#", "setData(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), arg1);
		}
		/// <remarks>
		///  Introduced in DOM Level 2
		///  This method is from the LinkStyle interface
		///  The style sheet.
		///      </remarks>		<short>    Introduced in DOM Level 2  This method is from the LinkStyle interface </short>
		public DOM.StyleSheet Sheet() {
			return (DOM.StyleSheet) interceptor.Invoke("sheet", "sheet() const", typeof(DOM.StyleSheet));
		}
		~ProcessingInstruction() {
			interceptor.Invoke("~ProcessingInstruction", "~ProcessingInstruction()", typeof(void));
		}
		public new void Dispose() {
			interceptor.Invoke("~ProcessingInstruction", "~ProcessingInstruction()", typeof(void));
		}
	}
}
