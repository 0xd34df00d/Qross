//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Collections.Generic;
    [SmokeClass("QTextFormat")]
    public class QTextFormat : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QTextFormat(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QTextFormat), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QTextFormat() {
            staticInterceptor = new SmokeInvocation(typeof(QTextFormat), null);
        }
        public enum FormatType {
            InvalidFormat = -1,
            BlockFormat = 1,
            CharFormat = 2,
            ListFormat = 3,
            TableFormat = 4,
            FrameFormat = 5,
            UserFormat = 100,
        }
        public enum Property {
            ObjectIndex = 0x0,
            CssFloat = 0x0800,
            LayoutDirection = 0x0801,
            OutlinePen = 0x810,
            BackgroundBrush = 0x820,
            ForegroundBrush = 0x821,
            BackgroundImageUrl = 0x823,
            BlockAlignment = 0x1010,
            BlockTopMargin = 0x1030,
            BlockBottomMargin = 0x1031,
            BlockLeftMargin = 0x1032,
            BlockRightMargin = 0x1033,
            TextIndent = 0x1034,
            TabPositions = 0x1035,
            BlockIndent = 0x1040,
            BlockNonBreakableLines = 0x1050,
            BlockTrailingHorizontalRulerWidth = 0x1060,
            FirstFontProperty = 0x1FE0,
            FontCapitalization = FirstFontProperty,
            FontLetterSpacing = 0x1FE1,
            FontWordSpacing = 0x1FE2,
            FontStyleHint = 0x1FE3,
            FontStyleStrategy = 0x1FE4,
            FontKerning = 0x1FE5,
            FontFamily = 0x2000,
            FontPointSize = 0x2001,
            FontSizeAdjustment = 0x2002,
            FontSizeIncrement = FontSizeAdjustment,
            FontWeight = 0x2003,
            FontItalic = 0x2004,
            FontUnderline = 0x2005,
            FontOverline = 0x2006,
            FontStrikeOut = 0x2007,
            FontFixedPitch = 0x2008,
            FontPixelSize = 0x2009,
            LastFontProperty = FontPixelSize,
            TextUnderlineColor = 0x2010,
            TextVerticalAlignment = 0x2021,
            TextOutline = 0x2022,
            TextUnderlineStyle = 0x2023,
            TextToolTip = 0x2024,
            IsAnchor = 0x2030,
            AnchorHref = 0x2031,
            AnchorName = 0x2032,
            ObjectType = 0x2f00,
            ListStyle = 0x3000,
            ListIndent = 0x3001,
            FrameBorder = 0x4000,
            FrameMargin = 0x4001,
            FramePadding = 0x4002,
            FrameWidth = 0x4003,
            FrameHeight = 0x4004,
            FrameTopMargin = 0x4005,
            FrameBottomMargin = 0x4006,
            FrameLeftMargin = 0x4007,
            FrameRightMargin = 0x4008,
            FrameBorderBrush = 0x4009,
            FrameBorderStyle = 0x4010,
            TableColumns = 0x4100,
            TableColumnWidthConstraints = 0x4101,
            TableCellSpacing = 0x4102,
            TableCellPadding = 0x4103,
            TableHeaderRowCount = 0x4104,
            TableCellRowSpan = 0x4810,
            TableCellColumnSpan = 0x4811,
            TableCellTopPadding = 0x4812,
            TableCellBottomPadding = 0x4813,
            TableCellLeftPadding = 0x4814,
            TableCellRightPadding = 0x4815,
            ImageName = 0x5000,
            ImageWidth = 0x5010,
            ImageHeight = 0x5011,
            FullWidthSelection = 0x06000,
            PageBreakPolicy = 0x7000,
            UserProperty = 0x100000,
        }
        public enum ObjectTypes {
            NoObject = 0,
            ImageObject = 1,
            TableObject = 2,
            TableCellObject = 3,
            UserObject = 0x1000,
        }
        public enum PageBreakFlag {
            PageBreak_Auto = 0,
            PageBreak_AlwaysBefore = 0x001,
            PageBreak_AlwaysAfter = 0x010,
        }
        public QTextFormat() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTextFormat", "QTextFormat()", typeof(void));
        }
        public QTextFormat(int type) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTextFormat$", "QTextFormat(int)", typeof(void), typeof(int), type);
        }
        public QTextFormat(QTextFormat rhs) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTextFormat#", "QTextFormat(const QTextFormat&)", typeof(void), typeof(QTextFormat), rhs);
        }
        public void Merge(QTextFormat other) {
            interceptor.Invoke("merge#", "merge(const QTextFormat&)", typeof(void), typeof(QTextFormat), other);
        }
        public bool IsValid() {
            return (bool) interceptor.Invoke("isValid", "isValid() const", typeof(bool));
        }
        public int type() {
            return (int) interceptor.Invoke("type", "type() const", typeof(int));
        }
        public int ObjectIndex() {
            return (int) interceptor.Invoke("objectIndex", "objectIndex() const", typeof(int));
        }
        public void SetObjectIndex(int arg1) {
            interceptor.Invoke("setObjectIndex$", "setObjectIndex(int)", typeof(void), typeof(int), arg1);
        }
        public QVariant property(int propertyId) {
            return (QVariant) interceptor.Invoke("property$", "property(int) const", typeof(QVariant), typeof(int), propertyId);
        }
        public void SetProperty(int propertyId, QVariant value) {
            interceptor.Invoke("setProperty$#", "setProperty(int, const QVariant&)", typeof(void), typeof(int), propertyId, typeof(QVariant), value);
        }
        public void ClearProperty(int propertyId) {
            interceptor.Invoke("clearProperty$", "clearProperty(int)", typeof(void), typeof(int), propertyId);
        }
        public bool HasProperty(int propertyId) {
            return (bool) interceptor.Invoke("hasProperty$", "hasProperty(int) const", typeof(bool), typeof(int), propertyId);
        }
        public bool BoolProperty(int propertyId) {
            return (bool) interceptor.Invoke("boolProperty$", "boolProperty(int) const", typeof(bool), typeof(int), propertyId);
        }
        public int IntProperty(int propertyId) {
            return (int) interceptor.Invoke("intProperty$", "intProperty(int) const", typeof(int), typeof(int), propertyId);
        }
        public double DoubleProperty(int propertyId) {
            return (double) interceptor.Invoke("doubleProperty$", "doubleProperty(int) const", typeof(double), typeof(int), propertyId);
        }
        public string StringProperty(int propertyId) {
            return (string) interceptor.Invoke("stringProperty$", "stringProperty(int) const", typeof(string), typeof(int), propertyId);
        }
        public QColor ColorProperty(int propertyId) {
            return (QColor) interceptor.Invoke("colorProperty$", "colorProperty(int) const", typeof(QColor), typeof(int), propertyId);
        }
        public QPen PenProperty(int propertyId) {
            return (QPen) interceptor.Invoke("penProperty$", "penProperty(int) const", typeof(QPen), typeof(int), propertyId);
        }
        public QBrush BrushProperty(int propertyId) {
            return (QBrush) interceptor.Invoke("brushProperty$", "brushProperty(int) const", typeof(QBrush), typeof(int), propertyId);
        }
        public QTextLength LengthProperty(int propertyId) {
            return (QTextLength) interceptor.Invoke("lengthProperty$", "lengthProperty(int) const", typeof(QTextLength), typeof(int), propertyId);
        }
        public List<QTextLength> LengthVectorProperty(int propertyId) {
            return (List<QTextLength>) interceptor.Invoke("lengthVectorProperty$", "lengthVectorProperty(int) const", typeof(List<QTextLength>), typeof(int), propertyId);
        }
        public void SetProperty(int propertyId, List<QTextLength> lengths) {
            interceptor.Invoke("setProperty$?", "setProperty(int, const QVector<QTextLength>&)", typeof(void), typeof(int), propertyId, typeof(List<QTextLength>), lengths);
        }
        public Dictionary<int, QVariant> Properties() {
            return (Dictionary<int, QVariant>) interceptor.Invoke("properties", "properties() const", typeof(Dictionary<int, QVariant>));
        }
        public int PropertyCount() {
            return (int) interceptor.Invoke("propertyCount", "propertyCount() const", typeof(int));
        }
        public void SetObjectType(int type) {
            interceptor.Invoke("setObjectType$", "setObjectType(int)", typeof(void), typeof(int), type);
        }
        public int ObjectType() {
            return (int) interceptor.Invoke("objectType", "objectType() const", typeof(int));
        }
        public bool IsCharFormat() {
            return (bool) interceptor.Invoke("isCharFormat", "isCharFormat() const", typeof(bool));
        }
        public bool IsBlockFormat() {
            return (bool) interceptor.Invoke("isBlockFormat", "isBlockFormat() const", typeof(bool));
        }
        public bool IsListFormat() {
            return (bool) interceptor.Invoke("isListFormat", "isListFormat() const", typeof(bool));
        }
        public bool IsFrameFormat() {
            return (bool) interceptor.Invoke("isFrameFormat", "isFrameFormat() const", typeof(bool));
        }
        public bool IsImageFormat() {
            return (bool) interceptor.Invoke("isImageFormat", "isImageFormat() const", typeof(bool));
        }
        public bool IsTableFormat() {
            return (bool) interceptor.Invoke("isTableFormat", "isTableFormat() const", typeof(bool));
        }
        public bool IsTableCellFormat() {
            return (bool) interceptor.Invoke("isTableCellFormat", "isTableCellFormat() const", typeof(bool));
        }
        public QTextBlockFormat ToBlockFormat() {
            return (QTextBlockFormat) interceptor.Invoke("toBlockFormat", "toBlockFormat() const", typeof(QTextBlockFormat));
        }
        public QTextCharFormat ToCharFormat() {
            return (QTextCharFormat) interceptor.Invoke("toCharFormat", "toCharFormat() const", typeof(QTextCharFormat));
        }
        public QTextListFormat ToListFormat() {
            return (QTextListFormat) interceptor.Invoke("toListFormat", "toListFormat() const", typeof(QTextListFormat));
        }
        public QTextTableFormat ToTableFormat() {
            return (QTextTableFormat) interceptor.Invoke("toTableFormat", "toTableFormat() const", typeof(QTextTableFormat));
        }
        public QTextFrameFormat ToFrameFormat() {
            return (QTextFrameFormat) interceptor.Invoke("toFrameFormat", "toFrameFormat() const", typeof(QTextFrameFormat));
        }
        public QTextImageFormat ToImageFormat() {
            return (QTextImageFormat) interceptor.Invoke("toImageFormat", "toImageFormat() const", typeof(QTextImageFormat));
        }
        public QTextTableCellFormat ToTableCellFormat() {
            return (QTextTableCellFormat) interceptor.Invoke("toTableCellFormat", "toTableCellFormat() const", typeof(QTextTableCellFormat));
        }
        public override bool Equals(object o) {
            if (!(o is QTextFormat)) { return false; }
            return this == (QTextFormat) o;
        }
        public override int GetHashCode() {
            return interceptor.GetHashCode();
        }
        public void SetLayoutDirection(Qt.LayoutDirection direction) {
            interceptor.Invoke("setLayoutDirection$", "setLayoutDirection(Qt::LayoutDirection)", typeof(void), typeof(Qt.LayoutDirection), direction);
        }
        public Qt.LayoutDirection LayoutDirection() {
            return (Qt.LayoutDirection) interceptor.Invoke("layoutDirection", "layoutDirection() const", typeof(Qt.LayoutDirection));
        }
        public void SetBackground(QBrush brush) {
            interceptor.Invoke("setBackground#", "setBackground(const QBrush&)", typeof(void), typeof(QBrush), brush);
        }
        public QBrush Background() {
            return (QBrush) interceptor.Invoke("background", "background() const", typeof(QBrush));
        }
        public void ClearBackground() {
            interceptor.Invoke("clearBackground", "clearBackground()", typeof(void));
        }
        public void SetForeground(QBrush brush) {
            interceptor.Invoke("setForeground#", "setForeground(const QBrush&)", typeof(void), typeof(QBrush), brush);
        }
        public QBrush Foreground() {
            return (QBrush) interceptor.Invoke("foreground", "foreground() const", typeof(QBrush));
        }
        public void ClearForeground() {
            interceptor.Invoke("clearForeground", "clearForeground()", typeof(void));
        }
        ~QTextFormat() {
            interceptor.Invoke("~QTextFormat", "~QTextFormat()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QTextFormat", "~QTextFormat()", typeof(void));
        }
        public static bool operator==(QTextFormat lhs, QTextFormat rhs) {
            return (bool) staticInterceptor.Invoke("operator==#", "operator==(const QTextFormat&) const", typeof(bool), typeof(QTextFormat), lhs, typeof(QTextFormat), rhs);
        }
        public static bool operator!=(QTextFormat lhs, QTextFormat rhs) {
            return !(bool) staticInterceptor.Invoke("operator==#", "operator==(const QTextFormat&) const", typeof(bool), typeof(QTextFormat), lhs, typeof(QTextFormat), rhs);
        }
        public static QVariant operatorQVariant(QTextFormat lhs) {
            return (QVariant) staticInterceptor.Invoke("operator QVariant", "operator QVariant() const", typeof(QVariant), typeof(QTextFormat), lhs);
        }
    }
}
