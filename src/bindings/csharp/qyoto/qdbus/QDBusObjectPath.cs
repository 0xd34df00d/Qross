namespace Qyoto {

	using System;

	public class QDBusObjectPath {
		private string text;
		public QDBusObjectPath() : this((string) null) {}
		public QDBusObjectPath(string text) {
			this.text = text;
		}
		public new string ToString() {
			return text;
		}
	}
}
