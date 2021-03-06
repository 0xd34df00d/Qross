//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  Searches for encoding declaration inside raw data -- meta and xml tags. 
    ///  In the case it can't find it, uses heuristics for specified language.
    ///  If it finds unicode BOM marks, it changes encoding regardless of what the user has told
    ///  Intended lifetime of the object: one instance per document.
    ///  Typical use:
    ///  <pre>
    ///  QByteArray data;
    ///  ...
    ///  KEncodingDetector detector;
    ///  detector.setAutoDetectLanguage(KEncodingDetector.Cyrillic);
    ///  string out=detector.decode(data);
    ///  </pre>
    ///  Do not mix decode() with decodeWithBuffering()
    ///  </remarks>        <short> Guess encoding of char array.</short>
    [SmokeClass("KEncodingDetector")]
    public class KEncodingDetector : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected KEncodingDetector(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KEncodingDetector), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static KEncodingDetector() {
            staticInterceptor = new SmokeInvocation(typeof(KEncodingDetector), null);
        }
        public enum EncodingChoiceSource {
            DefaultEncoding = 0,
            AutoDetectedEncoding = 1,
            BOM = 2,
            EncodingFromXMLHeader = 3,
            EncodingFromMetaTag = 4,
            EncodingFromHTTPHeader = 5,
            UserChosenEncoding = 6,
        }
        public enum AutoDetectScript {
            None = 0,
            SemiautomaticDetection = 1,
            Arabic = 2,
            Baltic = 3,
            CentralEuropean = 4,
            ChineseSimplified = 5,
            ChineseTraditional = 6,
            Cyrillic = 7,
            Greek = 8,
            Hebrew = 9,
            Japanese = 10,
            Korean = 11,
            NorthernSaami = 12,
            SouthEasternEurope = 13,
            Thai = 14,
            Turkish = 15,
            Unicode = 16,
            WesternEuropean = 17,
        }
        /// <remarks>
        ///  Default codec is latin1 (as html spec says), EncodingChoiceSource is default, AutoDetectScript=Semiautomatic
        ///      </remarks>        <short>    Default codec is latin1 (as html spec says), EncodingChoiceSource is default, AutoDetectScript=Semiautomatic      </short>
        public KEncodingDetector() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KEncodingDetector", "KEncodingDetector()", typeof(void));
        }
        /// <remarks>
        ///  Allows to set Default codec, EncodingChoiceSource, AutoDetectScript
        ///      </remarks>        <short>    Allows to set Default codec, EncodingChoiceSource, AutoDetectScript      </short>
        public KEncodingDetector(QTextCodec codec, KEncodingDetector.EncodingChoiceSource source, KEncodingDetector.AutoDetectScript script) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KEncodingDetector#$$", "KEncodingDetector(QTextCodec*, KEncodingDetector::EncodingChoiceSource, KEncodingDetector::AutoDetectScript)", typeof(void), typeof(QTextCodec), codec, typeof(KEncodingDetector.EncodingChoiceSource), source, typeof(KEncodingDetector.AutoDetectScript), script);
        }
        public KEncodingDetector(QTextCodec codec, KEncodingDetector.EncodingChoiceSource source) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KEncodingDetector#$", "KEncodingDetector(QTextCodec*, KEncodingDetector::EncodingChoiceSource)", typeof(void), typeof(QTextCodec), codec, typeof(KEncodingDetector.EncodingChoiceSource), source);
        }
        /// <remarks>
        /// </remarks>        <return> true if specified encoding was recognized
        ///     </return>
        ///         <short>   </short>
        public bool SetEncoding(string encoding, KEncodingDetector.EncodingChoiceSource type) {
            return (bool) interceptor.Invoke("setEncoding$$", "setEncoding(const char*, KEncodingDetector::EncodingChoiceSource)", typeof(bool), typeof(string), encoding, typeof(KEncodingDetector.EncodingChoiceSource), type);
        }
        /// <remarks>
        ///  Convenience method.
        /// </remarks>        <return> mime name of detected encoding
        ///     </return>
        ///         <short>    Convenience method.</short>
        public string Encoding() {
            return (string) interceptor.Invoke("encoding", "encoding() const", typeof(string));
        }
        public bool VisuallyOrdered() {
            return (bool) interceptor.Invoke("visuallyOrdered", "visuallyOrdered() const", typeof(bool));
        }
        public void SetAutoDetectLanguage(KEncodingDetector.AutoDetectScript arg1) {
            interceptor.Invoke("setAutoDetectLanguage$", "setAutoDetectLanguage(KEncodingDetector::AutoDetectScript)", typeof(void), typeof(KEncodingDetector.AutoDetectScript), arg1);
        }
        public KEncodingDetector.AutoDetectScript AutoDetectLanguage() {
            return (KEncodingDetector.AutoDetectScript) interceptor.Invoke("autoDetectLanguage", "autoDetectLanguage() const", typeof(KEncodingDetector.AutoDetectScript));
        }
        public KEncodingDetector.EncodingChoiceSource encodingChoiceSource() {
            return (KEncodingDetector.EncodingChoiceSource) interceptor.Invoke("encodingChoiceSource", "encodingChoiceSource() const", typeof(KEncodingDetector.EncodingChoiceSource));
        }
        /// <remarks>
        ///  The main class method
        ///  Calls protected analyze() only the first time of the whole object life
        ///  Replaces all null chars with spaces.
        ///     </remarks>        <short>    The main class method </short>
        public string Decode(string data, int len) {
            return (string) interceptor.Invoke("decode$$", "decode(const char*, int)", typeof(string), typeof(string), data, typeof(int), len);
        }
        public string Decode(QByteArray data) {
            return (string) interceptor.Invoke("decode#", "decode(const QByteArray&)", typeof(string), typeof(QByteArray), data);
        }
        /// <remarks>
        ///  Convenience method that uses buffering. It waits for full html head to be buffered
        ///  (i.e. calls analyze every time until it returns true).
        ///  Replaces all null chars with spaces.
        /// </remarks>        <return> Decoded data, or empty string, if there was not enough data for accurate detection
        /// </return>
        ///         <short>    Convenience method that uses buffering.</short>
        ///         <see> flush</see>
        public string DecodeWithBuffering(string data, int len) {
            return (string) interceptor.Invoke("decodeWithBuffering$$", "decodeWithBuffering(const char*, int)", typeof(string), typeof(string), data, typeof(int), len);
        }
        /// <remarks>
        ///  Convenience method to be used with decodeForHtml. Flushes buffer.
        /// </remarks>        <short>    Convenience method to be used with decodeForHtml.</short>
        ///         <see> decodeForHtml</see>
        public string Flush() {
            return (string) interceptor.Invoke("flush", "flush()", typeof(string));
        }
        /// <remarks>
        ///  This nice method will kill all 0 bytes (or double bytes)
        ///  and remember if this was a binary or not ;)
        ///      </remarks>        <short>    This nice method will kill all 0 bytes (or double bytes)  and remember if this was a binary or not ;)      </short>
        protected bool ProcessNull(Pointer<sbyte> data, int length) {
            return (bool) interceptor.Invoke("processNull$$", "processNull(char*, int)", typeof(bool), typeof(Pointer<sbyte>), data, typeof(int), length);
        }
        /// <remarks>
        ///  Check if we are really utf8. Taken from kate
        ///  Please somebody read http://de.wikipedia.org/wiki/UTF-8 and check this code...
        ///      </remarks>        <return> true if current encoding is utf8 and the text cannot be in this encoding
        /// </return>
        ///         <short>    Check if we are really utf8.</short>
        protected bool ErrorsIfUtf8(string data, int length) {
            return (bool) interceptor.Invoke("errorsIfUtf8$$", "errorsIfUtf8(const char*, int)", typeof(bool), typeof(string), data, typeof(int), length);
        }
        /// <remarks>
        ///  Analyze text data.
        /// </remarks>        <return> true if there was enough data for accurate detection
        ///     </return>
        ///         <short>    Analyze text data.</short>
        protected bool Analyze(string data, int len) {
            return (bool) interceptor.Invoke("analyze$$", "analyze(const char*, int)", typeof(bool), typeof(string), data, typeof(int), len);
        }
        /// <remarks>
        /// </remarks>        <return> QTextDecoder for detected encoding
        ///     </return>
        ///         <short>   </short>
        protected QTextDecoder Decoder() {
            return (QTextDecoder) interceptor.Invoke("decoder", "decoder()", typeof(QTextDecoder));
        }
        ~KEncodingDetector() {
            interceptor.Invoke("~KEncodingDetector", "~KEncodingDetector()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~KEncodingDetector", "~KEncodingDetector()", typeof(void));
        }
        /// <remarks>
        ///  Takes lang name _after_ it were i18n()'ed
        ///      </remarks>        <short>    Takes lang name _after_ it were i18n()'ed      </short>
        public static KEncodingDetector.AutoDetectScript ScriptForName(string lang) {
            return (KEncodingDetector.AutoDetectScript) staticInterceptor.Invoke("scriptForName$", "scriptForName(const QString&)", typeof(KEncodingDetector.AutoDetectScript), typeof(string), lang);
        }
        public static string NameForScript(KEncodingDetector.AutoDetectScript arg1) {
            return (string) staticInterceptor.Invoke("nameForScript$", "nameForScript(KEncodingDetector::AutoDetectScript)", typeof(string), typeof(KEncodingDetector.AutoDetectScript), arg1);
        }
        public static bool HasAutoDetectionForScript(KEncodingDetector.AutoDetectScript arg1) {
            return (bool) staticInterceptor.Invoke("hasAutoDetectionForScript$", "hasAutoDetectionForScript(KEncodingDetector::AutoDetectScript)", typeof(bool), typeof(KEncodingDetector.AutoDetectScript), arg1);
        }
    }
}
