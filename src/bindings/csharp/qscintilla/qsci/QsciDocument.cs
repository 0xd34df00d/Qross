//Auto-generated by kalyptus. DO NOT EDIT.
namespace QScintilla {

	using System;
	using Qyoto;

	[SmokeClass("QsciDocument")]
	public class QsciDocument : Object, IDisposable {
		protected SmokeInvocation interceptor = null;
		private IntPtr smokeObject;
		protected QsciDocument(Type dummy) {}
		protected void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(QsciDocument), this);
		}
		public QsciDocument() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("QsciDocument", "QsciDocument()", typeof(void));
		}
		public QsciDocument(QsciDocument arg1) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("QsciDocument#", "QsciDocument(const QsciDocument&)", typeof(void), typeof(QsciDocument), arg1);
		}
		~QsciDocument() {
			interceptor.Invoke("~QsciDocument", "~QsciDocument()", typeof(void));
		}
		public void Dispose() {
			interceptor.Invoke("~QsciDocument", "~QsciDocument()", typeof(void));
		}
	}
}
