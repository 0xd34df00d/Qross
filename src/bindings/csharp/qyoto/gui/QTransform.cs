//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    using System.Runtime.InteropServices;
    [SmokeClass("QTransform")]
    public partial class QTransform : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QTransform(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QTransform), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QTransform() {
            staticInterceptor = new SmokeInvocation(typeof(QTransform), null);
        }
        public enum TransformationType {
            TxNone = 0x00,
            TxTranslate = 0x01,
            TxScale = 0x02,
            TxRotate = 0x04,
            TxShear = 0x08,
            TxProject = 0x10,
        }
        public QTransform(Qt.Initialization arg1) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform$", "QTransform(Qt::Initialization)", typeof(void), typeof(Qt.Initialization), arg1);
        }
        public QTransform() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform", "QTransform()", typeof(void));
        }
        public QTransform(double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32, double h33) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform$$$$$$$$$", "QTransform(qreal, qreal, qreal, qreal, qreal, qreal, qreal, qreal, qreal)", typeof(void), typeof(double), h11, typeof(double), h12, typeof(double), h13, typeof(double), h21, typeof(double), h22, typeof(double), h23, typeof(double), h31, typeof(double), h32, typeof(double), h33);
        }
        public QTransform(double h11, double h12, double h13, double h21, double h22, double h23, double h31, double h32) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform$$$$$$$$", "QTransform(qreal, qreal, qreal, qreal, qreal, qreal, qreal, qreal)", typeof(void), typeof(double), h11, typeof(double), h12, typeof(double), h13, typeof(double), h21, typeof(double), h22, typeof(double), h23, typeof(double), h31, typeof(double), h32);
        }
        public QTransform(double h11, double h12, double h21, double h22, double dx, double dy) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform$$$$$$", "QTransform(qreal, qreal, qreal, qreal, qreal, qreal)", typeof(void), typeof(double), h11, typeof(double), h12, typeof(double), h21, typeof(double), h22, typeof(double), dx, typeof(double), dy);
        }
        public QTransform(QMatrix mtx) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QTransform#", "QTransform(const QMatrix&)", typeof(void), typeof(QMatrix), mtx);
        }
        public bool IsAffine() {
            return (bool) interceptor.Invoke("isAffine", "isAffine() const", typeof(bool));
        }
        public bool IsIdentity() {
            return (bool) interceptor.Invoke("isIdentity", "isIdentity() const", typeof(bool));
        }
        public bool IsInvertible() {
            return (bool) interceptor.Invoke("isInvertible", "isInvertible() const", typeof(bool));
        }
        public bool IsScaling() {
            return (bool) interceptor.Invoke("isScaling", "isScaling() const", typeof(bool));
        }
        public bool IsRotating() {
            return (bool) interceptor.Invoke("isRotating", "isRotating() const", typeof(bool));
        }
        public bool IsTranslating() {
            return (bool) interceptor.Invoke("isTranslating", "isTranslating() const", typeof(bool));
        }
        public QTransform.TransformationType type() {
            return (QTransform.TransformationType) interceptor.Invoke("type", "type() const", typeof(QTransform.TransformationType));
        }
        public double Determinant() {
            return (double) interceptor.Invoke("determinant", "determinant() const", typeof(double));
        }
        public double Det() {
            return (double) interceptor.Invoke("det", "det() const", typeof(double));
        }
        public double M11() {
            return (double) interceptor.Invoke("m11", "m11() const", typeof(double));
        }
        public double M12() {
            return (double) interceptor.Invoke("m12", "m12() const", typeof(double));
        }
        public double M13() {
            return (double) interceptor.Invoke("m13", "m13() const", typeof(double));
        }
        public double M21() {
            return (double) interceptor.Invoke("m21", "m21() const", typeof(double));
        }
        public double M22() {
            return (double) interceptor.Invoke("m22", "m22() const", typeof(double));
        }
        public double M23() {
            return (double) interceptor.Invoke("m23", "m23() const", typeof(double));
        }
        public double M31() {
            return (double) interceptor.Invoke("m31", "m31() const", typeof(double));
        }
        public double M32() {
            return (double) interceptor.Invoke("m32", "m32() const", typeof(double));
        }
        public double M33() {
            return (double) interceptor.Invoke("m33", "m33() const", typeof(double));
        }
        public double Dx() {
            return (double) interceptor.Invoke("dx", "dx() const", typeof(double));
        }
        public double Dy() {
            return (double) interceptor.Invoke("dy", "dy() const", typeof(double));
        }
        public void SetMatrix(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33) {
            interceptor.Invoke("setMatrix$$$$$$$$$", "setMatrix(qreal, qreal, qreal, qreal, qreal, qreal, qreal, qreal, qreal)", typeof(void), typeof(double), m11, typeof(double), m12, typeof(double), m13, typeof(double), m21, typeof(double), m22, typeof(double), m23, typeof(double), m31, typeof(double), m32, typeof(double), m33);
        }
        public QTransform Inverted(ref bool invertible) {
            StackItem[] stack = new StackItem[2];
            stack[1].s_bool = invertible;
            interceptor.Invoke("inverted$", "inverted(bool*) const", stack);
            invertible = stack[1].s_bool;
            object returnValue = ((GCHandle) stack[0].s_class).Target;
#if DEBUG
            DebugGCHandle.Free((GCHandle) stack[0].s_class);
#else
            ((GCHandle) stack[0].s_class).Free();
#endif
            return (QTransform) returnValue;
        }
        public QTransform Inverted() {
            return (QTransform) interceptor.Invoke("inverted", "inverted() const", typeof(QTransform));
        }
        public QTransform Adjoint() {
            return (QTransform) interceptor.Invoke("adjoint", "adjoint() const", typeof(QTransform));
        }
        public QTransform Transposed() {
            return (QTransform) interceptor.Invoke("transposed", "transposed() const", typeof(QTransform));
        }
        public QTransform Translate(double dx, double dy) {
            return (QTransform) interceptor.Invoke("translate$$", "translate(qreal, qreal)", typeof(QTransform), typeof(double), dx, typeof(double), dy);
        }
        public QTransform Scale(double sx, double sy) {
            return (QTransform) interceptor.Invoke("scale$$", "scale(qreal, qreal)", typeof(QTransform), typeof(double), sx, typeof(double), sy);
        }
        public QTransform Shear(double sh, double sv) {
            return (QTransform) interceptor.Invoke("shear$$", "shear(qreal, qreal)", typeof(QTransform), typeof(double), sh, typeof(double), sv);
        }
        public QTransform Rotate(double a, Qt.Axis axis) {
            return (QTransform) interceptor.Invoke("rotate$$", "rotate(qreal, Qt::Axis)", typeof(QTransform), typeof(double), a, typeof(Qt.Axis), axis);
        }
        public QTransform Rotate(double a) {
            return (QTransform) interceptor.Invoke("rotate$", "rotate(qreal)", typeof(QTransform), typeof(double), a);
        }
        public QTransform RotateRadians(double a, Qt.Axis axis) {
            return (QTransform) interceptor.Invoke("rotateRadians$$", "rotateRadians(qreal, Qt::Axis)", typeof(QTransform), typeof(double), a, typeof(Qt.Axis), axis);
        }
        public QTransform RotateRadians(double a) {
            return (QTransform) interceptor.Invoke("rotateRadians$", "rotateRadians(qreal)", typeof(QTransform), typeof(double), a);
        }
        public override bool Equals(object o) {
            if (!(o is QTransform)) { return false; }
            return this == (QTransform) o;
        }
        public override int GetHashCode() {
            return interceptor.GetHashCode();
        }
        public void Reset() {
            interceptor.Invoke("reset", "reset()", typeof(void));
        }
        public QPoint Map(QPoint p) {
            return (QPoint) interceptor.Invoke("map#", "map(const QPoint&) const", typeof(QPoint), typeof(QPoint), p);
        }
        public QPointF Map(QPointF p) {
            return (QPointF) interceptor.Invoke("map#", "map(const QPointF&) const", typeof(QPointF), typeof(QPointF), p);
        }
        public QLine Map(QLine l) {
            return (QLine) interceptor.Invoke("map#", "map(const QLine&) const", typeof(QLine), typeof(QLine), l);
        }
        public QLineF Map(QLineF l) {
            return (QLineF) interceptor.Invoke("map#", "map(const QLineF&) const", typeof(QLineF), typeof(QLineF), l);
        }
        public QPolygonF Map(QPolygonF a) {
            return (QPolygonF) interceptor.Invoke("map#", "map(const QPolygonF&) const", typeof(QPolygonF), typeof(QPolygonF), a);
        }
        public QPolygon Map(QPolygon a) {
            return (QPolygon) interceptor.Invoke("map#", "map(const QPolygon&) const", typeof(QPolygon), typeof(QPolygon), a);
        }
        public QRegion Map(QRegion r) {
            return (QRegion) interceptor.Invoke("map#", "map(const QRegion&) const", typeof(QRegion), typeof(QRegion), r);
        }
        public QPainterPath Map(QPainterPath p) {
            return (QPainterPath) interceptor.Invoke("map#", "map(const QPainterPath&) const", typeof(QPainterPath), typeof(QPainterPath), p);
        }
        public QPolygon MapToPolygon(QRect r) {
            return (QPolygon) interceptor.Invoke("mapToPolygon#", "mapToPolygon(const QRect&) const", typeof(QPolygon), typeof(QRect), r);
        }
        public QRect MapRect(QRect arg1) {
            return (QRect) interceptor.Invoke("mapRect#", "mapRect(const QRect&) const", typeof(QRect), typeof(QRect), arg1);
        }
        public QRectF MapRect(QRectF arg1) {
            return (QRectF) interceptor.Invoke("mapRect#", "mapRect(const QRectF&) const", typeof(QRectF), typeof(QRectF), arg1);
        }
        public void Map(int x, int y, ref int tx, ref int ty) {
            StackItem[] stack = new StackItem[5];
            stack[1].s_int = x;
            stack[2].s_int = y;
            stack[3].s_int = tx;
            stack[4].s_int = ty;
            interceptor.Invoke("map$$$$", "map(int, int, int*, int*) const", stack);
            tx = stack[3].s_int;
            ty = stack[4].s_int;
            return;
        }
        public void Map(double x, double y, ref double tx, ref double ty) {
            StackItem[] stack = new StackItem[5];
            stack[1].s_double = x;
            stack[2].s_double = y;
            stack[3].s_double = tx;
            stack[4].s_double = ty;
            interceptor.Invoke("map$$$$", "map(qreal, qreal, qreal*, qreal*) const", stack);
            tx = stack[3].s_double;
            ty = stack[4].s_double;
            return;
        }
        public QMatrix ToAffine() {
            return (QMatrix) interceptor.Invoke("toAffine", "toAffine() const", typeof(QMatrix));
        }
        ~QTransform() {
            interceptor.Invoke("~QTransform", "~QTransform()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QTransform", "~QTransform()", typeof(void));
        }
        public static bool operator==(QTransform lhs, QTransform arg1) {
            return (bool) staticInterceptor.Invoke("operator==#", "operator==(const QTransform&) const", typeof(bool), typeof(QTransform), lhs, typeof(QTransform), arg1);
        }
        public static bool operator!=(QTransform lhs, QTransform arg1) {
            return !(bool) staticInterceptor.Invoke("operator==#", "operator==(const QTransform&) const", typeof(bool), typeof(QTransform), lhs, typeof(QTransform), arg1);
        }
        public static QTransform operator*(QTransform lhs, QTransform arg1) {
            return (QTransform) staticInterceptor.Invoke("operator*=#", "operator*=(const QTransform&)", typeof(QTransform), typeof(QTransform), lhs, typeof(QTransform), arg1);
        }
        public static QVariant operatorQVariant(QTransform lhs) {
            return (QVariant) staticInterceptor.Invoke("operator QVariant", "operator QVariant() const", typeof(QVariant), typeof(QTransform), lhs);
        }
        public static QTransform operator*(QTransform lhs, double div) {
            return (QTransform) staticInterceptor.Invoke("operator*=$", "operator*=(qreal)", typeof(QTransform), typeof(QTransform), lhs, typeof(double), div);
        }
        public static QTransform operator/(QTransform lhs, double div) {
            return (QTransform) staticInterceptor.Invoke("operator/=$", "operator/=(qreal)", typeof(QTransform), typeof(QTransform), lhs, typeof(double), div);
        }
        public static bool SquareToQuad(QPolygonF square, QTransform result) {
            return (bool) staticInterceptor.Invoke("squareToQuad##", "squareToQuad(const QPolygonF&, QTransform&)", typeof(bool), typeof(QPolygonF), square, typeof(QTransform), result);
        }
        public static bool QuadToSquare(QPolygonF quad, QTransform result) {
            return (bool) staticInterceptor.Invoke("quadToSquare##", "quadToSquare(const QPolygonF&, QTransform&)", typeof(bool), typeof(QPolygonF), quad, typeof(QTransform), result);
        }
        public static bool QuadToQuad(QPolygonF one, QPolygonF two, QTransform result) {
            return (bool) staticInterceptor.Invoke("quadToQuad###", "quadToQuad(const QPolygonF&, const QPolygonF&, QTransform&)", typeof(bool), typeof(QPolygonF), one, typeof(QPolygonF), two, typeof(QTransform), result);
        }
        public static QTransform FromTranslate(double dx, double dy) {
            return (QTransform) staticInterceptor.Invoke("fromTranslate$$", "fromTranslate(qreal, qreal)", typeof(QTransform), typeof(double), dx, typeof(double), dy);
        }
        public static QTransform FromScale(double dx, double dy) {
            return (QTransform) staticInterceptor.Invoke("fromScale$$", "fromScale(qreal, qreal)", typeof(QTransform), typeof(double), dx, typeof(double), dy);
        }
        public static QPoint operator*(QPoint p, QTransform m) {
            return (QPoint) staticInterceptor.Invoke("operator*##", "operator*(const QPoint&, const QTransform&)", typeof(QPoint), typeof(QPoint), p, typeof(QTransform), m);
        }
        public static QPointF operator*(QPointF p, QTransform m) {
            return (QPointF) staticInterceptor.Invoke("operator*##", "operator*(const QPointF&, const QTransform&)", typeof(QPointF), typeof(QPointF), p, typeof(QTransform), m);
        }
        public static QLineF operator*(QLineF l, QTransform m) {
            return (QLineF) staticInterceptor.Invoke("operator*##", "operator*(const QLineF&, const QTransform&)", typeof(QLineF), typeof(QLineF), l, typeof(QTransform), m);
        }
        public static QLine operator*(QLine l, QTransform m) {
            return (QLine) staticInterceptor.Invoke("operator*##", "operator*(const QLine&, const QTransform&)", typeof(QLine), typeof(QLine), l, typeof(QTransform), m);
        }
        public static QPolygon operator*(QPolygon a, QTransform m) {
            return (QPolygon) staticInterceptor.Invoke("operator*##", "operator*(const QPolygon&, const QTransform&)", typeof(QPolygon), typeof(QPolygon), a, typeof(QTransform), m);
        }
        public static QPolygonF operator*(QPolygonF a, QTransform m) {
            return (QPolygonF) staticInterceptor.Invoke("operator*##", "operator*(const QPolygonF&, const QTransform&)", typeof(QPolygonF), typeof(QPolygonF), a, typeof(QTransform), m);
        }
        public static QRegion operator*(QRegion r, QTransform m) {
            return (QRegion) staticInterceptor.Invoke("operator*##", "operator*(const QRegion&, const QTransform&)", typeof(QRegion), typeof(QRegion), r, typeof(QTransform), m);
        }
        public static QPainterPath operator*(QPainterPath p, QTransform m) {
            return (QPainterPath) staticInterceptor.Invoke("operator*##", "operator*(const QPainterPath&, const QTransform&)", typeof(QPainterPath), typeof(QPainterPath), p, typeof(QTransform), m);
        }
        public static QTransform operator+(QTransform a, double n) {
            return (QTransform) staticInterceptor.Invoke("operator+#$", "operator+(const QTransform&, qreal)", typeof(QTransform), typeof(QTransform), a, typeof(double), n);
        }
        public static QTransform operator-(QTransform a, double n) {
            return (QTransform) staticInterceptor.Invoke("operator-#$", "operator-(const QTransform&, qreal)", typeof(QTransform), typeof(QTransform), a, typeof(double), n);
        }
    }
}
