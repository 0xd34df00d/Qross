//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Runtime.InteropServices;
    using System.Collections.Generic;
    [SmokeClass("QLocale")]
    public class QLocale : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QLocale(Type dummy) {}
        [SmokeClass("QLocale::Data")]
        public class Data : Object, IDisposable {
            protected SmokeInvocation interceptor = null;
            private IntPtr smokeObject;
            protected Data(Type dummy) {}
            protected void CreateProxy() {
                interceptor = new SmokeInvocation(typeof(Data), this);
            }
            public ushort Index {
                get { return (ushort) interceptor.Invoke("index", "index()", typeof(ushort)); }
                set { interceptor.Invoke("setIndex$", "setIndex(unsigned short)", typeof(void), typeof(ushort), value); }
            }
            public ushort NumberOptions {
                get { return (ushort) interceptor.Invoke("numberOptions", "numberOptions()", typeof(ushort)); }
                set { interceptor.Invoke("setNumberOptions$", "setNumberOptions(unsigned short)", typeof(void), typeof(ushort), value); }
            }
            public Data() : this((Type) null) {
                CreateProxy();
                interceptor.Invoke("Data", "Data()", typeof(void));
            }
            ~Data() {
                interceptor.Invoke("~Data", "~Data()", typeof(void));
            }
            public void Dispose() {
                interceptor.Invoke("~Data", "~Data()", typeof(void));
            }
        }
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QLocale), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QLocale() {
            staticInterceptor = new SmokeInvocation(typeof(QLocale), null);
        }
        public enum Language {
            C = 1,
            Abkhazian = 2,
            Afan = 3,
            Afar = 4,
            Afrikaans = 5,
            Albanian = 6,
            Amharic = 7,
            Arabic = 8,
            Armenian = 9,
            Assamese = 10,
            Aymara = 11,
            Azerbaijani = 12,
            Bashkir = 13,
            Basque = 14,
            Bengali = 15,
            Bhutani = 16,
            Bihari = 17,
            Bislama = 18,
            Breton = 19,
            Bulgarian = 20,
            Burmese = 21,
            Byelorussian = 22,
            Cambodian = 23,
            Catalan = 24,
            Chinese = 25,
            Corsican = 26,
            Croatian = 27,
            Czech = 28,
            Danish = 29,
            Dutch = 30,
            English = 31,
            Esperanto = 32,
            Estonian = 33,
            Faroese = 34,
            FijiLanguage = 35,
            Finnish = 36,
            French = 37,
            Frisian = 38,
            Gaelic = 39,
            Galician = 40,
            Georgian = 41,
            German = 42,
            Greek = 43,
            Greenlandic = 44,
            Guarani = 45,
            Gujarati = 46,
            Hausa = 47,
            Hebrew = 48,
            Hindi = 49,
            Hungarian = 50,
            Icelandic = 51,
            Indonesian = 52,
            Interlingua = 53,
            Interlingue = 54,
            Inuktitut = 55,
            Inupiak = 56,
            Irish = 57,
            Italian = 58,
            Japanese = 59,
            Javanese = 60,
            Kannada = 61,
            Kashmiri = 62,
            Kazakh = 63,
            Kinyarwanda = 64,
            Kirghiz = 65,
            Korean = 66,
            Kurdish = 67,
            Kurundi = 68,
            Laothian = 69,
            Latin = 70,
            Latvian = 71,
            Lingala = 72,
            Lithuanian = 73,
            Macedonian = 74,
            Malagasy = 75,
            Malay = 76,
            Malayalam = 77,
            Maltese = 78,
            Maori = 79,
            Marathi = 80,
            Moldavian = 81,
            Mongolian = 82,
            NauruLanguage = 83,
            Nepali = 84,
            Norwegian = 85,
            NorwegianBokmal = Norwegian,
            Occitan = 86,
            Oriya = 87,
            Pashto = 88,
            Persian = 89,
            Polish = 90,
            Portuguese = 91,
            Punjabi = 92,
            Quechua = 93,
            RhaetoRomance = 94,
            Romanian = 95,
            Russian = 96,
            Samoan = 97,
            Sangho = 98,
            Sanskrit = 99,
            Serbian = 100,
            SerboCroatian = 101,
            Sesotho = 102,
            Setswana = 103,
            Shona = 104,
            Sindhi = 105,
            Singhalese = 106,
            Siswati = 107,
            Slovak = 108,
            Slovenian = 109,
            Somali = 110,
            Spanish = 111,
            Sundanese = 112,
            Swahili = 113,
            Swedish = 114,
            Tagalog = 115,
            Tajik = 116,
            Tamil = 117,
            Tatar = 118,
            Telugu = 119,
            Thai = 120,
            Tibetan = 121,
            Tigrinya = 122,
            TongaLanguage = 123,
            Tsonga = 124,
            Turkish = 125,
            Turkmen = 126,
            Twi = 127,
            Uigur = 128,
            Ukrainian = 129,
            Urdu = 130,
            Uzbek = 131,
            Vietnamese = 132,
            Volapuk = 133,
            Welsh = 134,
            Wolof = 135,
            Xhosa = 136,
            Yiddish = 137,
            Yoruba = 138,
            Zhuang = 139,
            Zulu = 140,
            NorwegianNynorsk = 141,
            Nynorsk = NorwegianNynorsk,
            Bosnian = 142,
            Divehi = 143,
            Manx = 144,
            Cornish = 145,
            Akan = 146,
            Konkani = 147,
            Ga = 148,
            Igbo = 149,
            Kamba = 150,
            Syriac = 151,
            Blin = 152,
            Geez = 153,
            Koro = 154,
            Sidamo = 155,
            Atsam = 156,
            Tigre = 157,
            Jju = 158,
            Friulian = 159,
            Venda = 160,
            Ewe = 161,
            Walamo = 162,
            Hawaiian = 163,
            Tyap = 164,
            Chewa = 165,
            LastLanguage = Chewa,
        }
        public enum Country {
            AnyCountry = 0,
            Afghanistan = 1,
            Albania = 2,
            Algeria = 3,
            AmericanSamoa = 4,
            Andorra = 5,
            Angola = 6,
            Anguilla = 7,
            Antarctica = 8,
            AntiguaAndBarbuda = 9,
            Argentina = 10,
            Armenia = 11,
            Aruba = 12,
            Australia = 13,
            Austria = 14,
            Azerbaijan = 15,
            Bahamas = 16,
            Bahrain = 17,
            Bangladesh = 18,
            Barbados = 19,
            Belarus = 20,
            Belgium = 21,
            Belize = 22,
            Benin = 23,
            Bermuda = 24,
            Bhutan = 25,
            Bolivia = 26,
            BosniaAndHerzegowina = 27,
            Botswana = 28,
            BouvetIsland = 29,
            Brazil = 30,
            BritishIndianOceanTerritory = 31,
            BruneiDarussalam = 32,
            Bulgaria = 33,
            BurkinaFaso = 34,
            Burundi = 35,
            Cambodia = 36,
            Cameroon = 37,
            Canada = 38,
            CapeVerde = 39,
            CaymanIslands = 40,
            CentralAfricanRepublic = 41,
            Chad = 42,
            Chile = 43,
            China = 44,
            ChristmasIsland = 45,
            CocosIslands = 46,
            Colombia = 47,
            Comoros = 48,
            DemocraticRepublicOfCongo = 49,
            PeoplesRepublicOfCongo = 50,
            CookIslands = 51,
            CostaRica = 52,
            IvoryCoast = 53,
            Croatia = 54,
            Cuba = 55,
            Cyprus = 56,
            CzechRepublic = 57,
            Denmark = 58,
            Djibouti = 59,
            Dominica = 60,
            DominicanRepublic = 61,
            EastTimor = 62,
            Ecuador = 63,
            Egypt = 64,
            ElSalvador = 65,
            EquatorialGuinea = 66,
            Eritrea = 67,
            Estonia = 68,
            Ethiopia = 69,
            FalklandIslands = 70,
            FaroeIslands = 71,
            FijiCountry = 72,
            Finland = 73,
            France = 74,
            MetropolitanFrance = 75,
            FrenchGuiana = 76,
            FrenchPolynesia = 77,
            FrenchSouthernTerritories = 78,
            Gabon = 79,
            Gambia = 80,
            Georgia = 81,
            Germany = 82,
            Ghana = 83,
            Gibraltar = 84,
            Greece = 85,
            Greenland = 86,
            Grenada = 87,
            Guadeloupe = 88,
            Guam = 89,
            Guatemala = 90,
            Guinea = 91,
            GuineaBissau = 92,
            Guyana = 93,
            Haiti = 94,
            HeardAndMcDonaldIslands = 95,
            Honduras = 96,
            HongKong = 97,
            Hungary = 98,
            Iceland = 99,
            India = 100,
            Indonesia = 101,
            Iran = 102,
            Iraq = 103,
            Ireland = 104,
            Israel = 105,
            Italy = 106,
            Jamaica = 107,
            Japan = 108,
            Jordan = 109,
            Kazakhstan = 110,
            Kenya = 111,
            Kiribati = 112,
            DemocraticRepublicOfKorea = 113,
            RepublicOfKorea = 114,
            Kuwait = 115,
            Kyrgyzstan = 116,
            Lao = 117,
            Latvia = 118,
            Lebanon = 119,
            Lesotho = 120,
            Liberia = 121,
            LibyanArabJamahiriya = 122,
            Liechtenstein = 123,
            Lithuania = 124,
            Luxembourg = 125,
            Macau = 126,
            Macedonia = 127,
            Madagascar = 128,
            Malawi = 129,
            Malaysia = 130,
            Maldives = 131,
            Mali = 132,
            Malta = 133,
            MarshallIslands = 134,
            Martinique = 135,
            Mauritania = 136,
            Mauritius = 137,
            Mayotte = 138,
            Mexico = 139,
            Micronesia = 140,
            Moldova = 141,
            Monaco = 142,
            Mongolia = 143,
            Montserrat = 144,
            Morocco = 145,
            Mozambique = 146,
            Myanmar = 147,
            Namibia = 148,
            NauruCountry = 149,
            Nepal = 150,
            Netherlands = 151,
            NetherlandsAntilles = 152,
            NewCaledonia = 153,
            NewZealand = 154,
            Nicaragua = 155,
            Niger = 156,
            Nigeria = 157,
            Niue = 158,
            NorfolkIsland = 159,
            NorthernMarianaIslands = 160,
            Norway = 161,
            Oman = 162,
            Pakistan = 163,
            Palau = 164,
            PalestinianTerritory = 165,
            Panama = 166,
            PapuaNewGuinea = 167,
            Paraguay = 168,
            Peru = 169,
            Philippines = 170,
            Pitcairn = 171,
            Poland = 172,
            Portugal = 173,
            PuertoRico = 174,
            Qatar = 175,
            Reunion = 176,
            Romania = 177,
            RussianFederation = 178,
            Rwanda = 179,
            SaintKittsAndNevis = 180,
            StLucia = 181,
            StVincentAndTheGrenadines = 182,
            Samoa = 183,
            SanMarino = 184,
            SaoTomeAndPrincipe = 185,
            SaudiArabia = 186,
            Senegal = 187,
            Seychelles = 188,
            SierraLeone = 189,
            Singapore = 190,
            Slovakia = 191,
            Slovenia = 192,
            SolomonIslands = 193,
            Somalia = 194,
            SouthAfrica = 195,
            SouthGeorgiaAndTheSouthSandwichIslands = 196,
            Spain = 197,
            SriLanka = 198,
            StHelena = 199,
            StPierreAndMiquelon = 200,
            Sudan = 201,
            Suriname = 202,
            SvalbardAndJanMayenIslands = 203,
            Swaziland = 204,
            Sweden = 205,
            Switzerland = 206,
            SyrianArabRepublic = 207,
            Taiwan = 208,
            Tajikistan = 209,
            Tanzania = 210,
            Thailand = 211,
            Togo = 212,
            Tokelau = 213,
            TongaCountry = 214,
            TrinidadAndTobago = 215,
            Tunisia = 216,
            Turkey = 217,
            Turkmenistan = 218,
            TurksAndCaicosIslands = 219,
            Tuvalu = 220,
            Uganda = 221,
            Ukraine = 222,
            UnitedArabEmirates = 223,
            UnitedKingdom = 224,
            UnitedStates = 225,
            UnitedStatesMinorOutlyingIslands = 226,
            Uruguay = 227,
            Uzbekistan = 228,
            Vanuatu = 229,
            VaticanCityState = 230,
            Venezuela = 231,
            VietNam = 232,
            BritishVirginIslands = 233,
            USVirginIslands = 234,
            WallisAndFutunaIslands = 235,
            WesternSahara = 236,
            Yemen = 237,
            Yugoslavia = 238,
            Zambia = 239,
            Zimbabwe = 240,
            SerbiaAndMontenegro = 241,
            LastCountry = SerbiaAndMontenegro,
        }
        public enum MeasurementSystem {
            MetricSystem = 0,
            ImperialSystem = 1,
        }
        public enum FormatType {
            LongFormat = 0,
            ShortFormat = 1,
            NarrowFormat = 2,
        }
        public enum NumberOption {
            OmitGroupSeparator = 0x01,
            RejectGroupSeparator = 0x02,
        }
        public QLocale() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLocale", "QLocale()", typeof(void));
        }
        public QLocale(string name) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLocale$", "QLocale(const QString&)", typeof(void), typeof(string), name);
        }
        public QLocale(QLocale.Language language, QLocale.Country country) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLocale$$", "QLocale(QLocale::Language, QLocale::Country)", typeof(void), typeof(QLocale.Language), language, typeof(QLocale.Country), country);
        }
        public QLocale(QLocale.Language language) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLocale$", "QLocale(QLocale::Language)", typeof(void), typeof(QLocale.Language), language);
        }
        public QLocale(QLocale other) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QLocale#", "QLocale(const QLocale&)", typeof(void), typeof(QLocale), other);
        }
        public QLocale.Language language() {
            return (QLocale.Language) interceptor.Invoke("language", "language() const", typeof(QLocale.Language));
        }
        public QLocale.Country country() {
            return (QLocale.Country) interceptor.Invoke("country", "country() const", typeof(QLocale.Country));
        }
        public string Name() {
            return (string) interceptor.Invoke("name", "name() const", typeof(string));
        }
        public short ToShort(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toShort$$$", "toShort(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_short;
        }
        public short ToShort(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toShort$$", "toShort(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_short;
        }
        public short ToShort(string s) {
            return (short) interceptor.Invoke("toShort$", "toShort(const QString&) const", typeof(short), typeof(string), s);
        }
        public ushort ToUShort(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toUShort$$$", "toUShort(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_ushort;
        }
        public ushort ToUShort(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toUShort$$", "toUShort(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_ushort;
        }
        public ushort ToUShort(string s) {
            return (ushort) interceptor.Invoke("toUShort$", "toUShort(const QString&) const", typeof(ushort), typeof(string), s);
        }
        public int ToInt(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toInt$$$", "toInt(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_int;
        }
        public int ToInt(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toInt$$", "toInt(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_int;
        }
        public int ToInt(string s) {
            return (int) interceptor.Invoke("toInt$", "toInt(const QString&) const", typeof(int), typeof(string), s);
        }
        public uint ToUInt(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toUInt$$$", "toUInt(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_uint;
        }
        public uint ToUInt(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toUInt$$", "toUInt(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_uint;
        }
        public uint ToUInt(string s) {
            return (uint) interceptor.Invoke("toUInt$", "toUInt(const QString&) const", typeof(uint), typeof(string), s);
        }
        public long ToLongLong(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toLongLong$$$", "toLongLong(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_long;
        }
        public long ToLongLong(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toLongLong$$", "toLongLong(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_long;
        }
        public long ToLongLong(string s) {
            return (long) interceptor.Invoke("toLongLong$", "toLongLong(const QString&) const", typeof(long), typeof(string), s);
        }
        public long ToULongLong(string s, ref bool ok, int arg3) {
            StackItem[] stack = new StackItem[4];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            stack[3].s_int = arg3;
            interceptor.Invoke("toULongLong$$$", "toULongLong(const QString&, bool*, int) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_long;
        }
        public long ToULongLong(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toULongLong$$", "toULongLong(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_long;
        }
        public long ToULongLong(string s) {
            return (long) interceptor.Invoke("toULongLong$", "toULongLong(const QString&) const", typeof(long), typeof(string), s);
        }
        public float ToFloat(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toFloat$$", "toFloat(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_float;
        }
        public float ToFloat(string s) {
            return (float) interceptor.Invoke("toFloat$", "toFloat(const QString&) const", typeof(float), typeof(string), s);
        }
        public double ToDouble(string s, ref bool ok) {
            StackItem[] stack = new StackItem[3];
#if DEBUG
            stack[1].s_class = (IntPtr) DebugGCHandle.Alloc(s);
#else
            stack[1].s_class = (IntPtr) GCHandle.Alloc(s);
#endif
            stack[2].s_bool = ok;
            interceptor.Invoke("toDouble$$", "toDouble(const QString&, bool*) const", stack);
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[1].s_class);
#else
            ((GCHandle) stack[1].s_class).Free();
#endif
            ok = stack[2].s_bool;
            return stack[0].s_double;
        }
        public double ToDouble(string s) {
            return (double) interceptor.Invoke("toDouble$", "toDouble(const QString&) const", typeof(double), typeof(string), s);
        }
        public string ToString(long i) {
            return (string) interceptor.Invoke("toString?", "toString(qlonglong) const", typeof(string), typeof(long), i);
        }
        public string ToString(ulong i) {
            return (string) interceptor.Invoke("toString$", "toString(qulonglong) const", typeof(string), typeof(ulong), i);
        }
        public string ToString(short i) {
            return (string) interceptor.Invoke("toString$", "toString(short) const", typeof(string), typeof(short), i);
        }
        public string ToString(ushort i) {
            return (string) interceptor.Invoke("toString$", "toString(unsigned short) const", typeof(string), typeof(ushort), i);
        }
        public string ToString(int i) {
            return (string) interceptor.Invoke("toString$", "toString(int) const", typeof(string), typeof(int), i);
        }
        public string ToString(uint i) {
            return (string) interceptor.Invoke("toString$", "toString(uint) const", typeof(string), typeof(uint), i);
        }
        public string ToString(double i, char f, int prec) {
            return (string) interceptor.Invoke("toString$$$", "toString(double, char, int) const", typeof(string), typeof(double), i, typeof(char), f, typeof(int), prec);
        }
        public string ToString(double i, char f) {
            return (string) interceptor.Invoke("toString$$", "toString(double, char) const", typeof(string), typeof(double), i, typeof(char), f);
        }
        public string ToString(double i) {
            return (string) interceptor.Invoke("toString$", "toString(double) const", typeof(string), typeof(double), i);
        }
        public string ToString(float i, char f, int prec) {
            return (string) interceptor.Invoke("toString$$$", "toString(float, char, int) const", typeof(string), typeof(float), i, typeof(char), f, typeof(int), prec);
        }
        public string ToString(float i, char f) {
            return (string) interceptor.Invoke("toString$$", "toString(float, char) const", typeof(string), typeof(float), i, typeof(char), f);
        }
        public string ToString(float i) {
            return (string) interceptor.Invoke("toString$", "toString(float) const", typeof(string), typeof(float), i);
        }
        public string ToString(QDate date, string formatStr) {
            return (string) interceptor.Invoke("toString#$", "toString(const QDate&, const QString&) const", typeof(string), typeof(QDate), date, typeof(string), formatStr);
        }
        public string ToString(QDate date, QLocale.FormatType format) {
            return (string) interceptor.Invoke("toString#$", "toString(const QDate&, QLocale::FormatType) const", typeof(string), typeof(QDate), date, typeof(QLocale.FormatType), format);
        }
        public string ToString(QDate date) {
            return (string) interceptor.Invoke("toString#", "toString(const QDate&) const", typeof(string), typeof(QDate), date);
        }
        public string ToString(QTime time, string formatStr) {
            return (string) interceptor.Invoke("toString#$", "toString(const QTime&, const QString&) const", typeof(string), typeof(QTime), time, typeof(string), formatStr);
        }
        public string ToString(QTime time, QLocale.FormatType format) {
            return (string) interceptor.Invoke("toString#$", "toString(const QTime&, QLocale::FormatType) const", typeof(string), typeof(QTime), time, typeof(QLocale.FormatType), format);
        }
        public string ToString(QTime time) {
            return (string) interceptor.Invoke("toString#", "toString(const QTime&) const", typeof(string), typeof(QTime), time);
        }
        public string ToString(QDateTime dateTime, QLocale.FormatType format) {
            return (string) interceptor.Invoke("toString#$", "toString(const QDateTime&, QLocale::FormatType) const", typeof(string), typeof(QDateTime), dateTime, typeof(QLocale.FormatType), format);
        }
        public string ToString(QDateTime dateTime) {
            return (string) interceptor.Invoke("toString#", "toString(const QDateTime&) const", typeof(string), typeof(QDateTime), dateTime);
        }
        public string ToString(QDateTime dateTime, string format) {
            return (string) interceptor.Invoke("toString#$", "toString(const QDateTime&, const QString&) const", typeof(string), typeof(QDateTime), dateTime, typeof(string), format);
        }
        public string DateFormat(QLocale.FormatType format) {
            return (string) interceptor.Invoke("dateFormat$", "dateFormat(QLocale::FormatType) const", typeof(string), typeof(QLocale.FormatType), format);
        }
        public string DateFormat() {
            return (string) interceptor.Invoke("dateFormat", "dateFormat() const", typeof(string));
        }
        public string TimeFormat(QLocale.FormatType format) {
            return (string) interceptor.Invoke("timeFormat$", "timeFormat(QLocale::FormatType) const", typeof(string), typeof(QLocale.FormatType), format);
        }
        public string TimeFormat() {
            return (string) interceptor.Invoke("timeFormat", "timeFormat() const", typeof(string));
        }
        public string DateTimeFormat(QLocale.FormatType format) {
            return (string) interceptor.Invoke("dateTimeFormat$", "dateTimeFormat(QLocale::FormatType) const", typeof(string), typeof(QLocale.FormatType), format);
        }
        public string DateTimeFormat() {
            return (string) interceptor.Invoke("dateTimeFormat", "dateTimeFormat() const", typeof(string));
        }
        public QDate ToDate(string arg1, QLocale.FormatType arg2) {
            return (QDate) interceptor.Invoke("toDate$$", "toDate(const QString&, QLocale::FormatType) const", typeof(QDate), typeof(string), arg1, typeof(QLocale.FormatType), arg2);
        }
        public QDate ToDate(string arg1) {
            return (QDate) interceptor.Invoke("toDate$", "toDate(const QString&) const", typeof(QDate), typeof(string), arg1);
        }
        public QTime ToTime(string arg1, QLocale.FormatType arg2) {
            return (QTime) interceptor.Invoke("toTime$$", "toTime(const QString&, QLocale::FormatType) const", typeof(QTime), typeof(string), arg1, typeof(QLocale.FormatType), arg2);
        }
        public QTime ToTime(string arg1) {
            return (QTime) interceptor.Invoke("toTime$", "toTime(const QString&) const", typeof(QTime), typeof(string), arg1);
        }
        public QDateTime ToDateTime(string arg1, QLocale.FormatType format) {
            return (QDateTime) interceptor.Invoke("toDateTime$$", "toDateTime(const QString&, QLocale::FormatType) const", typeof(QDateTime), typeof(string), arg1, typeof(QLocale.FormatType), format);
        }
        public QDateTime ToDateTime(string arg1) {
            return (QDateTime) interceptor.Invoke("toDateTime$", "toDateTime(const QString&) const", typeof(QDateTime), typeof(string), arg1);
        }
        public QDate ToDate(string arg1, string format) {
            return (QDate) interceptor.Invoke("toDate$$", "toDate(const QString&, const QString&) const", typeof(QDate), typeof(string), arg1, typeof(string), format);
        }
        public QTime ToTime(string arg1, string format) {
            return (QTime) interceptor.Invoke("toTime$$", "toTime(const QString&, const QString&) const", typeof(QTime), typeof(string), arg1, typeof(string), format);
        }
        public QDateTime ToDateTime(string arg1, string format) {
            return (QDateTime) interceptor.Invoke("toDateTime$$", "toDateTime(const QString&, const QString&) const", typeof(QDateTime), typeof(string), arg1, typeof(string), format);
        }
        public QChar DecimalPoint() {
            return (QChar) interceptor.Invoke("decimalPoint", "decimalPoint() const", typeof(QChar));
        }
        public QChar GroupSeparator() {
            return (QChar) interceptor.Invoke("groupSeparator", "groupSeparator() const", typeof(QChar));
        }
        public QChar Percent() {
            return (QChar) interceptor.Invoke("percent", "percent() const", typeof(QChar));
        }
        public QChar ZeroDigit() {
            return (QChar) interceptor.Invoke("zeroDigit", "zeroDigit() const", typeof(QChar));
        }
        public QChar NegativeSign() {
            return (QChar) interceptor.Invoke("negativeSign", "negativeSign() const", typeof(QChar));
        }
        public QChar PositiveSign() {
            return (QChar) interceptor.Invoke("positiveSign", "positiveSign() const", typeof(QChar));
        }
        public QChar Exponential() {
            return (QChar) interceptor.Invoke("exponential", "exponential() const", typeof(QChar));
        }
        public string MonthName(int arg1, QLocale.FormatType format) {
            return (string) interceptor.Invoke("monthName$$", "monthName(int, QLocale::FormatType) const", typeof(string), typeof(int), arg1, typeof(QLocale.FormatType), format);
        }
        public string MonthName(int arg1) {
            return (string) interceptor.Invoke("monthName$", "monthName(int) const", typeof(string), typeof(int), arg1);
        }
        public string StandaloneMonthName(int arg1, QLocale.FormatType format) {
            return (string) interceptor.Invoke("standaloneMonthName$$", "standaloneMonthName(int, QLocale::FormatType) const", typeof(string), typeof(int), arg1, typeof(QLocale.FormatType), format);
        }
        public string StandaloneMonthName(int arg1) {
            return (string) interceptor.Invoke("standaloneMonthName$", "standaloneMonthName(int) const", typeof(string), typeof(int), arg1);
        }
        public string DayName(int arg1, QLocale.FormatType format) {
            return (string) interceptor.Invoke("dayName$$", "dayName(int, QLocale::FormatType) const", typeof(string), typeof(int), arg1, typeof(QLocale.FormatType), format);
        }
        public string DayName(int arg1) {
            return (string) interceptor.Invoke("dayName$", "dayName(int) const", typeof(string), typeof(int), arg1);
        }
        public string StandaloneDayName(int arg1, QLocale.FormatType format) {
            return (string) interceptor.Invoke("standaloneDayName$$", "standaloneDayName(int, QLocale::FormatType) const", typeof(string), typeof(int), arg1, typeof(QLocale.FormatType), format);
        }
        public string StandaloneDayName(int arg1) {
            return (string) interceptor.Invoke("standaloneDayName$", "standaloneDayName(int) const", typeof(string), typeof(int), arg1);
        }
        public string AmText() {
            return (string) interceptor.Invoke("amText", "amText() const", typeof(string));
        }
        public string PmText() {
            return (string) interceptor.Invoke("pmText", "pmText() const", typeof(string));
        }
        public QLocale.MeasurementSystem measurementSystem() {
            return (QLocale.MeasurementSystem) interceptor.Invoke("measurementSystem", "measurementSystem() const", typeof(QLocale.MeasurementSystem));
        }
        public override bool Equals(object o) {
            if (!(o is QLocale)) { return false; }
            return this == (QLocale) o;
        }
        public override int GetHashCode() {
            return interceptor.GetHashCode();
        }
        public void SetNumberOptions(uint options) {
            interceptor.Invoke("setNumberOptions$", "setNumberOptions(QLocale::NumberOptions)", typeof(void), typeof(uint), options);
        }
        public uint NumberOptions() {
            return (uint) interceptor.Invoke("numberOptions", "numberOptions() const", typeof(uint));
        }
        ~QLocale() {
            interceptor.Invoke("~QLocale", "~QLocale()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QLocale", "~QLocale()", typeof(void));
        }
        public static bool operator==(QLocale lhs, QLocale other) {
            return (bool) staticInterceptor.Invoke("operator==#", "operator==(const QLocale&) const", typeof(bool), typeof(QLocale), lhs, typeof(QLocale), other);
        }
        public static bool operator!=(QLocale lhs, QLocale other) {
            return !(bool) staticInterceptor.Invoke("operator==#", "operator==(const QLocale&) const", typeof(bool), typeof(QLocale), lhs, typeof(QLocale), other);
        }
        public static string LanguageToString(QLocale.Language language) {
            return (string) staticInterceptor.Invoke("languageToString$", "languageToString(QLocale::Language)", typeof(string), typeof(QLocale.Language), language);
        }
        public static string CountryToString(QLocale.Country country) {
            return (string) staticInterceptor.Invoke("countryToString$", "countryToString(QLocale::Country)", typeof(string), typeof(QLocale.Country), country);
        }
        public static void SetDefault(QLocale locale) {
            staticInterceptor.Invoke("setDefault#", "setDefault(const QLocale&)", typeof(void), typeof(QLocale), locale);
        }
        public static QLocale C() {
            return (QLocale) staticInterceptor.Invoke("c", "c()", typeof(QLocale));
        }
        public static QLocale System() {
            return (QLocale) staticInterceptor.Invoke("system", "system()", typeof(QLocale));
        }
        public static List<QLocale.Country> CountriesForLanguage(QLocale.Language lang) {
            return (List<QLocale.Country>) staticInterceptor.Invoke("countriesForLanguage$", "countriesForLanguage(QLocale::Language)", typeof(List<QLocale.Country>), typeof(QLocale.Language), lang);
        }
    }
}
