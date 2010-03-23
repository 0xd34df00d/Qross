//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  Base class representing a source of time zone information.
    ///  Derive subclasses from KTimeZoneSource to read and parse time zone details
    ///  from a time zone database or other source of time zone information. If can know
    ///  in advance what KTimeZone instances to create without having to parse the source
    ///  data, you should reimplement the method parse(KTimeZone). Otherwise,
    ///  you need to define your own parse() methods with appropriate signatures, to both
    ///  read and parse the new data, and create new KTimeZone instances.
    ///  KTimeZoneSource itself may be used as a dummy source which returns empty
    ///  time zone details.
    /// </remarks>        <author> S.R.Haque <srhaque@iee.org>.
    ///  </author>
    ///         <short> Base class representing a source of time zone information.</short>
    ///         <see> KTimeZone</see>
    ///         <see> KTimeZoneData</see>
    ///         <see> @ingroup</see>
    ///         <see> timezones</see>
    [SmokeClass("KTimeZoneSource")]
    public class KTimeZoneSource : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected KTimeZoneSource(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KTimeZoneSource), this);
        }
        public KTimeZoneSource() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KTimeZoneSource", "KTimeZoneSource()", typeof(void));
        }
        /// <remarks>
        ///  Extracts detail information for one time zone from the source database.
        ///  In this base class, the method always succeeds and returns an empty data
        ///  instance. Derived classes should reimplement this method to return an
        ///  appropriate data class derived from KTimeZoneData. Some source databases
        ///  may not be compatible with this method of parsing. In these cases, they
        ///  should use the constructor KTimeZoneSource(false) and calling this method
        ///  will produce a fatal error.
        /// <param> name="zone" the time zone for which data is to be extracted.
        /// </param></remarks>        <return> an instance of a class derived from KTimeZoneData containing
        ///          the parsed data. The caller is responsible for deleting the
        ///          KTimeZoneData instance.
        ///          Null is returned on error.
        ///      </return>
        ///         <short>    Extracts detail information for one time zone from the source database.</short>
        [SmokeMethod("parse(const KTimeZone&) const")]
        public virtual KTimeZoneData Parse(KTimeZone zone) {
            return (KTimeZoneData) interceptor.Invoke("parse#", "parse(const KTimeZone&) const", typeof(KTimeZoneData), typeof(KTimeZone), zone);
        }
        /// <remarks>
        ///  Return whether the source database supports the ad hoc extraction of data for
        ///  individual time zones using parse(KTimeZone).
        /// </remarks>        <return> true if parse(KTimeZone) works, false if parsing must be
        ///          performed by other methods
        ///      </return>
        ///         <short>    Return whether the source database supports the ad hoc extraction of data for  individual time zones using parse(KTimeZone).</short>
        public bool UseZoneParse() {
            return (bool) interceptor.Invoke("useZoneParse", "useZoneParse() const", typeof(bool));
        }
        /// <remarks>
        ///  Constructor for use by derived classes, which specifies whether the
        ///  source database supports the ad hoc extraction of data for individual
        ///  time zones using parse(KTimeZone).
        ///  If parse(KTimeZone) cannot be used, KTimeZone derived classes
        ///  which use this KTimeZoneSource derived class must create a
        ///  KTimeZoneData object at construction time so that KTimeZone.Data()
        ///  will always return a data object.
        ///  Note the default constructor is equivalent to KTimeZoneSource(true), i.e.
        ///  it is only necessary to use this constructor if parse(KTimeZone)
        ///  does not work.
        /// <param> name="useZoneParse" true if parse(KTimeZone) works, false if
        ///                      parsing must be performed by other methods
        ///      </param></remarks>        <short>    Constructor for use by derived classes, which specifies whether the  source database supports the ad hoc extraction of data for individual  time zones using parse(KTimeZone).</short>
        public KTimeZoneSource(bool useZoneParse) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KTimeZoneSource$", "KTimeZoneSource(bool)", typeof(void), typeof(bool), useZoneParse);
        }
        ~KTimeZoneSource() {
            interceptor.Invoke("~KTimeZoneSource", "~KTimeZoneSource()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~KTimeZoneSource", "~KTimeZoneSource()", typeof(void));
        }
    }
}
