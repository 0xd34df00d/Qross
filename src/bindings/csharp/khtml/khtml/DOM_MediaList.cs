//Auto-generated by kalyptus. DO NOT EDIT.
namespace DOM {
	using Kimono;
	using System;
	using Qyoto;
	/// <remarks>
	///  The <code>MediaList</code> interface provides the abstraction of
	///  an ordered collection of media, without defining or constraining
	///  how this collection is implemented. All media are lowercase
	///  strings.
	///  </remarks>		<short>    The <code>MediaList</code> interface provides the abstraction of  an ordered collection of media, without defining or constraining  how this collection is implemented.</short>
	[SmokeClass("DOM::MediaList")]
	public class MediaList : Object, IDisposable {
		protected SmokeInvocation interceptor = null;
		private IntPtr smokeObject;
		protected MediaList(Type dummy) {}
		protected void CreateProxy() {
			interceptor = new SmokeInvocation(typeof(MediaList), this);
		}
		// DOM::MediaList* MediaList(DOM::MediaListImpl* arg1); >>>> NOT CONVERTED
		public MediaList() : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("MediaList", "MediaList()", typeof(void));
		}
		public MediaList(DOM.MediaList other) : this((Type) null) {
			CreateProxy();
			interceptor.Invoke("MediaList#", "MediaList(const DOM::MediaList&)", typeof(void), typeof(DOM.MediaList), other);
		}
		/// <remarks>
		///  The parsable textual representation of the media list. This is a
		///  comma-separated list of media.
		///  NO_MODIFICATION_ALLOWED_ERR: Raised if this media list is readonly.
		///      </remarks>		<short>    The parsable textual representation of the media list.</short>
		public DOM.DOMString MediaText() {
			return (DOM.DOMString) interceptor.Invoke("mediaText", "mediaText() const", typeof(DOM.DOMString));
		}
		/// <remarks>
		///  see mediaText
		///      </remarks>		<short>    see mediaText      </short>
		public void SetMediaText(DOM.DOMString value) {
			interceptor.Invoke("setMediaText#", "setMediaText(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), value);
		}
		/// <remarks>
		///  The number of media in the list. The range of valid media is 0 to length-1 inclusive.
		///      </remarks>		<short>    The number of media in the list.</short>
		public ulong Length() {
			return (ulong) interceptor.Invoke("length", "length() const", typeof(ulong));
		}
		/// <remarks>
		///  Returns the indexth in the list. If index is greater than or equal to
		///  the number of media in the list, this returns null.
		/// <param> name="index" Index into the collection.
		/// </param></remarks>		<return> The medium at the indexth position in the MediaList, or null if
		///  that is not a valid index.
		///      </return>
		/// 		<short>    Returns the indexth in the list.</short>
		public DOM.DOMString Item(ulong index) {
			return (DOM.DOMString) interceptor.Invoke("item$", "item(unsigned long) const", typeof(DOM.DOMString), typeof(ulong), index);
		}
		/// <remarks>
		///  Deletes the medium indicated by oldMedium from the list.
		/// <param> name="oldMedium" The medium to delete in the media list.
		/// </param> NOT_FOUND_ERR: Raised if oldMedium is not in the list.
		///      </remarks>		<short>    Deletes the medium indicated by oldMedium from the list.</short>
		public void DeleteMedium(DOM.DOMString oldMedium) {
			interceptor.Invoke("deleteMedium#", "deleteMedium(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), oldMedium);
		}
		/// <remarks>
		///  Adds the medium newMedium to the end of the list. If the newMedium is
		///  already used, it is first removed.
		/// <param> name="newMedium" The new medium to add.
		/// </param> NO_MODIFICATION_ALLOWED_ERR: Raised if this list is readonly.
		///      </remarks>		<short>    Adds the medium newMedium to the end of the list.</short>
		public void AppendMedium(DOM.DOMString newMedium) {
			interceptor.Invoke("appendMedium#", "appendMedium(const DOM::DOMString&)", typeof(void), typeof(DOM.DOMString), newMedium);
		}
		public bool IsNull() {
			return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
		}
		~MediaList() {
			interceptor.Invoke("~MediaList", "~MediaList()", typeof(void));
		}
		public void Dispose() {
			interceptor.Invoke("~MediaList", "~MediaList()", typeof(void));
		}
	}
}
