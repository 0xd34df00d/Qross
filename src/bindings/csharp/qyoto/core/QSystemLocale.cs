//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QSystemLocale")]
    public class QSystemLocale : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QSystemLocale(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QSystemLocale), this);
        }
        public enum QueryType {
            LanguageId = 0,
            CountryId = 1,
            DecimalPoint = 2,
            GroupSeparator = 3,
            ZeroDigit = 4,
            NegativeSign = 5,
            DateFormatLong = 6,
            DateFormatShort = 7,
            TimeFormatLong = 8,
            TimeFormatShort = 9,
            DayNameLong = 10,
            DayNameShort = 11,
            MonthNameLong = 12,
            MonthNameShort = 13,
            DateToStringLong = 14,
            DateToStringShort = 15,
            TimeToStringLong = 16,
            TimeToStringShort = 17,
            DateTimeFormatLong = 18,
            DateTimeFormatShort = 19,
            DateTimeToStringLong = 20,
            DateTimeToStringShort = 21,
            MeasurementSystem = 22,
            PositiveSign = 23,
            AMText = 24,
            PMText = 25,
        }
        public QSystemLocale() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QSystemLocale", "QSystemLocale()", typeof(void));
        }
        [SmokeMethod("query(QSystemLocale::QueryType, QVariant) const")]
        public virtual QVariant Query(QSystemLocale.QueryType type, QVariant arg2) {
            return (QVariant) interceptor.Invoke("query$#", "query(QSystemLocale::QueryType, QVariant) const", typeof(QVariant), typeof(QSystemLocale.QueryType), type, typeof(QVariant), arg2);
        }
        [SmokeMethod("fallbackLocale() const")]
        public virtual QLocale FallbackLocale() {
            return (QLocale) interceptor.Invoke("fallbackLocale", "fallbackLocale() const", typeof(QLocale));
        }
        ~QSystemLocale() {
            interceptor.Invoke("~QSystemLocale", "~QSystemLocale()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QSystemLocale", "~QSystemLocale()", typeof(void));
        }
    }
}
