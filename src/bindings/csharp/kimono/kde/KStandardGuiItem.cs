//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  The various KDEUI_EXPORT methods returns standardized <see cref="KGuiItem"></see>'s
    ///  conforming to the KDE UI Standards. Use them instead of creating
    ///  your own.
    /// </remarks>        <author> Holger Freyther <freyther@kde.org>
    ///  </author>
    ///         <short> Provides a set of standardized KGuiItems. </short>
    [SmokeClass("KStandardGuiItem")]
    public class KStandardGuiItem {
        private static SmokeInvocation staticInterceptor = null;
        static KStandardGuiItem() {
            staticInterceptor = new SmokeInvocation(typeof(KStandardGuiItem), null);
        }
        /// <remarks>
        ///  The back and forward items by default use the RTL settings for Hebrew
        ///  and Arab countries. If you want those actions to ignore the RTL value
        ///  and force 'Western' behavior instead, use the IgnoreRTL value instead.
        ///      </remarks>        <short>    The back and forward items by default use the RTL settings for Hebrew  and Arab countries.</short>
        public enum BidiMode {
            UseRTL = 0,
            IgnoreRTL = 1,
        }
        public enum StandardItem {
            Ok = 1,
            Cancel = 2,
            Yes = 3,
            No = 4,
            Discard = 5,
            Save = 6,
            DontSave = 7,
            SaveAs = 8,
            Apply = 9,
            Clear = 10,
            Help = 11,
            Defaults = 12,
            Close = 13,
            Back = 14,
            Forward = 15,
            Print = 16,
            Continue = 17,
            Open = 18,
            Quit = 19,
            AdminMode = 20,
            Reset = 21,
            Delete = 22,
            Insert = 23,
            Configure = 24,
            Find = 25,
            Stop = 26,
            Add = 27,
            Remove = 28,
            Test = 29,
            Properties = 30,
            Overwrite = 31,
        }
        /// <remarks>
        ///  Returns the gui item for the given identifier @param id.
        /// <param> name="id" the identifier to search for
        ///      </param></remarks>        <short>    Returns the gui item for the given identifier @param id.</short>
        public static KGuiItem GuiItem(KStandardGuiItem.StandardItem id) {
            return (KGuiItem) staticInterceptor.Invoke("guiItem$", "guiItem(KStandardGuiItem::StandardItem)", typeof(KGuiItem), typeof(KStandardGuiItem.StandardItem), id);
        }
        /// <remarks>
        ///  Returns the name of the gui item for the given identifier @param id.
        /// <param> name="id" the identifier to search for
        ///      </param></remarks>        <short>    Returns the name of the gui item for the given identifier @param id.</short>
        public static string standardItem(KStandardGuiItem.StandardItem id) {
            return (string) staticInterceptor.Invoke("standardItem$", "standardItem(KStandardGuiItem::StandardItem)", typeof(string), typeof(KStandardGuiItem.StandardItem), id);
        }
        /// <remarks>
        ///  Returns the 'Ok' gui item.
        ///      </remarks>        <short>    Returns the 'Ok' gui item.</short>
        public static KGuiItem Ok() {
            return (KGuiItem) staticInterceptor.Invoke("ok", "ok()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Cancel' gui item.
        ///      </remarks>        <short>    Returns the 'Cancel' gui item.</short>
        public static KGuiItem Cancel() {
            return (KGuiItem) staticInterceptor.Invoke("cancel", "cancel()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Yes' gui item.
        ///      </remarks>        <short>    Returns the 'Yes' gui item.</short>
        public static KGuiItem Yes() {
            return (KGuiItem) staticInterceptor.Invoke("yes", "yes()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'No' gui item.
        ///      </remarks>        <short>    Returns the 'No' gui item.</short>
        public static KGuiItem No() {
            return (KGuiItem) staticInterceptor.Invoke("no", "no()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Insert' gui item.
        ///      </remarks>        <short>    Returns the 'Insert' gui item.</short>
        public static KGuiItem Insert() {
            return (KGuiItem) staticInterceptor.Invoke("insert", "insert()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Discard' gui item.
        ///      </remarks>        <short>    Returns the 'Discard' gui item.</short>
        public static KGuiItem Discard() {
            return (KGuiItem) staticInterceptor.Invoke("discard", "discard()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Save' gui item.
        ///      </remarks>        <short>    Returns the 'Save' gui item.</short>
        public static KGuiItem Save() {
            return (KGuiItem) staticInterceptor.Invoke("save", "save()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Help' gui item.
        ///      </remarks>        <short>    Returns the 'Help' gui item.</short>
        public static KGuiItem Help() {
            return (KGuiItem) staticInterceptor.Invoke("help", "help()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'DontSave' gui item.
        ///      </remarks>        <short>    Returns the 'DontSave' gui item.</short>
        public static KGuiItem DontSave() {
            return (KGuiItem) staticInterceptor.Invoke("dontSave", "dontSave()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'SaveAs' gui item.
        ///      </remarks>        <short>    Returns the 'SaveAs' gui item.</short>
        public static KGuiItem SaveAs() {
            return (KGuiItem) staticInterceptor.Invoke("saveAs", "saveAs()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Apply' gui item.
        ///      </remarks>        <short>    Returns the 'Apply' gui item.</short>
        public static KGuiItem Apply() {
            return (KGuiItem) staticInterceptor.Invoke("apply", "apply()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Clear' gui item.
        ///      </remarks>        <short>    Returns the 'Clear' gui item.</short>
        public static KGuiItem Clear() {
            return (KGuiItem) staticInterceptor.Invoke("clear", "clear()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Defaults' gui item.
        ///      </remarks>        <short>    Returns the 'Defaults' gui item.</short>
        public static KGuiItem Defaults() {
            return (KGuiItem) staticInterceptor.Invoke("defaults", "defaults()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Close' gui item.
        ///      </remarks>        <short>    Returns the 'Close' gui item.</short>
        public static KGuiItem Close() {
            return (KGuiItem) staticInterceptor.Invoke("close", "close()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Print' gui item.
        ///      </remarks>        <short>    Returns the 'Print' gui item.</short>
        public static KGuiItem Print() {
            return (KGuiItem) staticInterceptor.Invoke("print", "print()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Properties' gui item.
        ///      </remarks>        <short>    Returns the 'Properties' gui item.</short>
        public static KGuiItem Properties() {
            return (KGuiItem) staticInterceptor.Invoke("properties", "properties()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Reset' gui item.
        ///      </remarks>        <short>    Returns the 'Reset' gui item.</short>
        public static KGuiItem Reset() {
            return (KGuiItem) staticInterceptor.Invoke("reset", "reset()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Overwrite' gui item.
        ///      </remarks>        <short>    Returns the 'Overwrite' gui item.</short>
        public static KGuiItem Overwrite() {
            return (KGuiItem) staticInterceptor.Invoke("overwrite", "overwrite()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns a KGuiItem suiting for cases where code or functionality
        ///  runs under root privileges. Used in conjunction with KConfig Modules.
        ///      </remarks>        <short>    Returns a KGuiItem suiting for cases where code or functionality  runs under root privileges.</short>
        public static KGuiItem AdminMode() {
            return (KGuiItem) staticInterceptor.Invoke("adminMode", "adminMode()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Continue' gui item. The short name is due to 'continue' being a
        ///  reserved word in the C++ language.
        ///      </remarks>        <short>    Returns the 'Continue' gui item.</short>
        public static KGuiItem Cont() {
            return (KGuiItem) staticInterceptor.Invoke("cont", "cont()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Delete' gui item. The short name is due to 'delete' being a
        ///  reserved word in the C++ language.
        ///      </remarks>        <short>    Returns the 'Delete' gui item.</short>
        public static KGuiItem Del() {
            return (KGuiItem) staticInterceptor.Invoke("del", "del()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Open' gui item.
        ///      </remarks>        <short>    Returns the 'Open' gui item.</short>
        public static KGuiItem Open() {
            return (KGuiItem) staticInterceptor.Invoke("open", "open()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Back' gui item, like Konqueror's back button.
        ///  This GUI item can optionally honor the user's setting for BiDi, so the
        ///  icon for right-to-left languages (Hebrew and Arab) has the arrow
        ///  pointing in the opposite direction.
        ///  By default the arrow points in the Western 'back' direction (i.e.
        ///  to the left). This is because usually you only want the Bidi aware
        ///  GUI item if you also want the 'forward' item. Those two are available
        ///  in the separate backAndForward() method.
        ///      </remarks>        <short>    Returns the 'Back' gui item, like Konqueror's back button.</short>
        public static KGuiItem Back(KStandardGuiItem.BidiMode useBidi) {
            return (KGuiItem) staticInterceptor.Invoke("back$", "back(KStandardGuiItem::BidiMode)", typeof(KGuiItem), typeof(KStandardGuiItem.BidiMode), useBidi);
        }
        public static KGuiItem Back() {
            return (KGuiItem) staticInterceptor.Invoke("back", "back()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Forward' gui item, like Konqueror's forward
        ///  button. This GUI item can optionally honor the user's setting for BiDi,
        ///  so the icon for right-to-left languages (Hebrew and Arab) has the arrow
        ///  pointing in the opposite direction.
        ///  By default the arrow points in the Western 'forward' direction (i.e.
        ///  to the right). This is because usually you only want the Bidi aware
        ///  GUI item if you also want the 'back' item. Those two are available
        ///  in the separate backAndForward() method.
        ///      </remarks>        <short>    Returns the 'Forward' gui item, like Konqueror's forward  button.</short>
        public static KGuiItem Forward(KStandardGuiItem.BidiMode useBidi) {
            return (KGuiItem) staticInterceptor.Invoke("forward$", "forward(KStandardGuiItem::BidiMode)", typeof(KGuiItem), typeof(KStandardGuiItem.BidiMode), useBidi);
        }
        public static KGuiItem Forward() {
            return (KGuiItem) staticInterceptor.Invoke("forward", "forward()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Configure' gui item.
        ///      </remarks>        <short>    Returns the 'Configure' gui item.</short>
        public static KGuiItem Configure() {
            return (KGuiItem) staticInterceptor.Invoke("configure", "configure()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Return both a back and a forward gui item. This function always returns
        ///  items that are aware of the Right-to-Left setting for Arab and Hebrew
        ///  locales. If you have a reason for wanting the 'Western' back/forward
        ///  buttons, please use the back() and forward() items instead.
        ///      </remarks>        <short>    Return both a back and a forward gui item.</short>
        public static QPair<KGuiItem, KGuiItem> BackAndForward() {
            return (QPair<KGuiItem, KGuiItem>) staticInterceptor.Invoke("backAndForward", "backAndForward()", typeof(QPair<KGuiItem, KGuiItem>));
        }
        /// <remarks>
        ///  Returns the 'Quit' gui item.
        ///      </remarks>        <short>    Returns the 'Quit' gui item.</short>
        public static KGuiItem Quit() {
            return (KGuiItem) staticInterceptor.Invoke("quit", "quit()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Find' gui item.
        ///      </remarks>        <short>    Returns the 'Find' gui item.</short>
        public static KGuiItem Find() {
            return (KGuiItem) staticInterceptor.Invoke("find", "find()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Stop' gui item.
        ///      </remarks>        <short>    Returns the 'Stop' gui item.</short>
        public static KGuiItem Stop() {
            return (KGuiItem) staticInterceptor.Invoke("stop", "stop()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Add' gui item.
        ///      </remarks>        <short>    Returns the 'Add' gui item.</short>
        public static KGuiItem Add() {
            return (KGuiItem) staticInterceptor.Invoke("add", "add()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Remove' gui item.
        ///      </remarks>        <short>    Returns the 'Remove' gui item.</short>
        public static KGuiItem Remove() {
            return (KGuiItem) staticInterceptor.Invoke("remove", "remove()", typeof(KGuiItem));
        }
        /// <remarks>
        ///  Returns the 'Test' gui item.
        ///      </remarks>        <short>    Returns the 'Test' gui item.</short>
        public static KGuiItem Test() {
            return (KGuiItem) staticInterceptor.Invoke("test", "test()", typeof(KGuiItem));
        }
    }
}
