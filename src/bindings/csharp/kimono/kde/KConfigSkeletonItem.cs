//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  \class KConfigSkeletonItem kcoreconfigskeleton.h <KConfigSkeletonItem>
    ///  This class represents one preferences setting as used by <see cref="KCoreConfigSkeleton"></see>.
    ///  Subclasses of KConfigSkeletonItem implement storage functions for a certain type of
    ///  setting. Normally you don't have to use this class directly. Use the special
    ///  addItem() functions of KCoreConfigSkeleton instead. If you subclass this class you will
    ///  have to register instances with the function KCoreConfigSkeleton.AddItem().
    ///    </remarks>        <author> Cornelius Schumacher
    /// </author>
    ///         <short> Class for storing a preferences setting.</short>
    ///         <see> KCoreConfigSkeleton</see>
    [SmokeClass("KConfigSkeletonItem")]
    public abstract class KConfigSkeletonItem : Object {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected KConfigSkeletonItem(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KConfigSkeletonItem), this);
        }
        /// <remarks>
        ///  Constructor.
        /// <param> name="_group" Config file group.
        /// </param><param> name="_key" Config file key.
        ///      </param></remarks>        <short>    Constructor.</short>
        public KConfigSkeletonItem(string _group, string _key) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KConfigSkeletonItem$$", "KConfigSkeletonItem(const QString&, const QString&)", typeof(void), typeof(string), _group, typeof(string), _key);
        }
        /// <remarks>
        ///  Set config file group.
        ///      </remarks>        <short>    Set config file group.</short>
        public void SetGroup(string _group) {
            interceptor.Invoke("setGroup$", "setGroup(const QString&)", typeof(void), typeof(string), _group);
        }
        /// <remarks>
        ///  Return config file group.
        ///      </remarks>        <short>    Return config file group.</short>
        public string Group() {
            return (string) interceptor.Invoke("group", "group() const", typeof(string));
        }
        /// <remarks>
        ///  Set config file key.
        ///      </remarks>        <short>    Set config file key.</short>
        public void SetKey(string _key) {
            interceptor.Invoke("setKey$", "setKey(const QString&)", typeof(void), typeof(string), _key);
        }
        /// <remarks>
        ///  Return config file key.
        ///      </remarks>        <short>    Return config file key.</short>
        public string Key() {
            return (string) interceptor.Invoke("key", "key() const", typeof(string));
        }
        /// <remarks>
        ///  Set internal name of entry.
        ///      </remarks>        <short>    Set internal name of entry.</short>
        public void SetName(string _name) {
            interceptor.Invoke("setName$", "setName(const QString&)", typeof(void), typeof(string), _name);
        }
        /// <remarks>
        ///  Return internal name of entry.
        ///      </remarks>        <short>    Return internal name of entry.</short>
        public string Name() {
            return (string) interceptor.Invoke("name", "name() const", typeof(string));
        }
        /// <remarks>
        ///       Set label providing a translated one-line description of the item.
        ///     </remarks>        <short>         Set label providing a translated one-line description of the item.</short>
        public void SetLabel(string l) {
            interceptor.Invoke("setLabel$", "setLabel(const QString&)", typeof(void), typeof(string), l);
        }
        /// <remarks>
        ///       Return label of item. See setLabel().
        ///     </remarks>        <short>         Return label of item.</short>
        public string Label() {
            return (string) interceptor.Invoke("label", "label() const", typeof(string));
        }
        /// <remarks>
        ///       Set WhatsThis description of item.
        ///     </remarks>        <short>         Set WhatsThis description of item.</short>
        public void SetWhatsThis(string w) {
            interceptor.Invoke("setWhatsThis$", "setWhatsThis(const QString&)", typeof(void), typeof(string), w);
        }
        /// <remarks>
        ///       Return WhatsThis description of item. See setWhatsThis().
        ///     </remarks>        <short>         Return WhatsThis description of item.</short>
        public string WhatsThis() {
            return (string) interceptor.Invoke("whatsThis", "whatsThis() const", typeof(string));
        }
        /// <remarks>
        ///  This function is called by <see cref="KCoreConfigSkeleton"></see> to read the value for this setting
        ///  from a config file.
        ///      </remarks>        <short>    This function is called by @ref KCoreConfigSkeleton to read the value for this setting  from a config file.</short>
        [SmokeMethod("readConfig(KConfig*)")]
        public abstract void ReadConfig(KConfig arg1);
        /// <remarks>
        ///  This function is called by <see cref="KCoreConfigSkeleton"></see> to write the value of this setting
        ///  to a config file.
        ///      </remarks>        <short>    This function is called by @ref KCoreConfigSkeleton to write the value of this setting  to a config file.</short>
        [SmokeMethod("writeConfig(KConfig*)")]
        public abstract void WriteConfig(KConfig arg1);
        /// <remarks>
        ///  Read global default value.
        ///      </remarks>        <short>    Read global default value.</short>
        [SmokeMethod("readDefault(KConfig*)")]
        public abstract void ReadDefault(KConfig arg1);
        /// <remarks>
        ///  Set item to <code>p</code>
        ///      </remarks>        <short>    Set item to <code>p</code>      </short>
        [SmokeMethod("setProperty(const QVariant&)")]
        public abstract void SetProperty(QVariant p);
        /// <remarks>
        ///  Check whether the item is equal to v.
        ///  Use this function to compare items that use custom types such as KUrl,
        ///  because QVariant.Operator== will not work for those.
        /// <param> name="v" QVariant to compare to
        /// </param></remarks>        <return> true if the item is equal to v, false otherwise
        ///      </return>
        ///         <short>    Check whether the item is equal to v.</short>
        [SmokeMethod("isEqual(const QVariant&) const")]
        public abstract bool IsEqual(QVariant v);
        /// <remarks>
        ///  Return item as property
        ///      </remarks>        <short>    Return item as property      </short>
        [SmokeMethod("property() const")]
        public abstract QVariant Property();
        /// <remarks>
        ///  Return minimum value of item or invalid if not specified
        ///      </remarks>        <short>    Return minimum value of item or invalid if not specified      </short>
        [SmokeMethod("minValue() const")]
        public virtual QVariant MinValue() {
            return (QVariant) interceptor.Invoke("minValue", "minValue() const", typeof(QVariant));
        }
        /// <remarks>
        ///  Return maximum value of item or invalid if not specified
        ///      </remarks>        <short>    Return maximum value of item or invalid if not specified      </short>
        [SmokeMethod("maxValue() const")]
        public virtual QVariant MaxValue() {
            return (QVariant) interceptor.Invoke("maxValue", "maxValue() const", typeof(QVariant));
        }
        /// <remarks>
        ///  Sets the current value to the default value.
        ///      </remarks>        <short>    Sets the current value to the default value.</short>
        [SmokeMethod("setDefault()")]
        public abstract void SetDefault();
        /// <remarks>
        ///  Exchanges the current value with the default value
        ///  Used by KCoreConfigSkeleton.UseDefaults(bool);
        ///      </remarks>        <short>    Exchanges the current value with the default value  Used by KCoreConfigSkeleton.UseDefaults(bool);      </short>
        [SmokeMethod("swapDefault()")]
        public abstract void SwapDefault();
        /// <remarks>
        ///  Return if the entry can be modified.
        ///      </remarks>        <short>    Return if the entry can be modified.</short>
        public bool IsImmutable() {
            return (bool) interceptor.Invoke("isImmutable", "isImmutable() const", typeof(bool));
        }
        /// <remarks>
        ///  sets mIsImmutable to true if mKey in config is immutable
        /// <param> name="group" KConfigGroup to check if mKey is immutable in
        ///      </param></remarks>        <short>    sets mIsImmutable to true if mKey in config is immutable </short>
        protected void ReadImmutability(KConfigGroup group) {
            interceptor.Invoke("readImmutability#", "readImmutability(const KConfigGroup&)", typeof(void), typeof(KConfigGroup), group);
        }
    }
}
