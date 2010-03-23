//Auto-generated by kalyptus. DO NOT EDIT.
namespace Qyoto {
    using System;
    [SmokeClass("QVector3D")]
    public class QVector3D : Object, IDisposable {
        protected SmokeInvocation interceptor = null;
        private IntPtr smokeObject;
        protected QVector3D(Type dummy) {}
        protected void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(QVector3D), this);
        }
        private static SmokeInvocation staticInterceptor = null;
        static QVector3D() {
            staticInterceptor = new SmokeInvocation(typeof(QVector3D), null);
        }
        public QVector3D() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D", "QVector3D()", typeof(void));
        }
        public QVector3D(double xpos, double ypos, double zpos) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D$$$", "QVector3D(qreal, qreal, qreal)", typeof(void), typeof(double), xpos, typeof(double), ypos, typeof(double), zpos);
        }
        public QVector3D(QPoint point) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D#", "QVector3D(const QPoint&)", typeof(void), typeof(QPoint), point);
        }
        public QVector3D(QPointF point) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D#", "QVector3D(const QPointF&)", typeof(void), typeof(QPointF), point);
        }
        public QVector3D(QVector2D vector) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D#", "QVector3D(const QVector2D&)", typeof(void), typeof(QVector2D), vector);
        }
        public QVector3D(QVector2D vector, double zpos) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D#$", "QVector3D(const QVector2D&, qreal)", typeof(void), typeof(QVector2D), vector, typeof(double), zpos);
        }
        public QVector3D(QVector4D vector) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("QVector3D#", "QVector3D(const QVector4D&)", typeof(void), typeof(QVector4D), vector);
        }
        public bool IsNull() {
            return (bool) interceptor.Invoke("isNull", "isNull() const", typeof(bool));
        }
        public double X() {
            return (double) interceptor.Invoke("x", "x() const", typeof(double));
        }
        public double Y() {
            return (double) interceptor.Invoke("y", "y() const", typeof(double));
        }
        public double Z() {
            return (double) interceptor.Invoke("z", "z() const", typeof(double));
        }
        public void SetX(double x) {
            interceptor.Invoke("setX$", "setX(qreal)", typeof(void), typeof(double), x);
        }
        public void SetY(double y) {
            interceptor.Invoke("setY$", "setY(qreal)", typeof(void), typeof(double), y);
        }
        public void SetZ(double z) {
            interceptor.Invoke("setZ$", "setZ(qreal)", typeof(void), typeof(double), z);
        }
        public double Length() {
            return (double) interceptor.Invoke("length", "length() const", typeof(double));
        }
        public double LengthSquared() {
            return (double) interceptor.Invoke("lengthSquared", "lengthSquared() const", typeof(double));
        }
        public QVector3D Normalized() {
            return (QVector3D) interceptor.Invoke("normalized", "normalized() const", typeof(QVector3D));
        }
        public void Normalize() {
            interceptor.Invoke("normalize", "normalize()", typeof(void));
        }
        public double DistanceToPlane(QVector3D plane, QVector3D normal) {
            return (double) interceptor.Invoke("distanceToPlane##", "distanceToPlane(const QVector3D&, const QVector3D&) const", typeof(double), typeof(QVector3D), plane, typeof(QVector3D), normal);
        }
        public double DistanceToPlane(QVector3D plane1, QVector3D plane2, QVector3D plane3) {
            return (double) interceptor.Invoke("distanceToPlane###", "distanceToPlane(const QVector3D&, const QVector3D&, const QVector3D&) const", typeof(double), typeof(QVector3D), plane1, typeof(QVector3D), plane2, typeof(QVector3D), plane3);
        }
        public double DistanceToLine(QVector3D point, QVector3D direction) {
            return (double) interceptor.Invoke("distanceToLine##", "distanceToLine(const QVector3D&, const QVector3D&) const", typeof(double), typeof(QVector3D), point, typeof(QVector3D), direction);
        }
        public QVector2D ToVector2D() {
            return (QVector2D) interceptor.Invoke("toVector2D", "toVector2D() const", typeof(QVector2D));
        }
        public QVector4D ToVector4D() {
            return (QVector4D) interceptor.Invoke("toVector4D", "toVector4D() const", typeof(QVector4D));
        }
        public QPoint ToPoint() {
            return (QPoint) interceptor.Invoke("toPoint", "toPoint() const", typeof(QPoint));
        }
        public QPointF ToPointF() {
            return (QPointF) interceptor.Invoke("toPointF", "toPointF() const", typeof(QPointF));
        }
        ~QVector3D() {
            interceptor.Invoke("~QVector3D", "~QVector3D()", typeof(void));
        }
        public void Dispose() {
            interceptor.Invoke("~QVector3D", "~QVector3D()", typeof(void));
        }
        public override bool Equals(object o) {
            if (!(o is QVector3D)) { return false; }
            return this == (QVector3D) o;
        }
        public override int GetHashCode() {
            return interceptor.GetHashCode();
        }
        public static QVector3D operator*(QVector3D lhs, double factor) {
            return (QVector3D) staticInterceptor.Invoke("operator*=$", "operator*=(qreal)", typeof(QVector3D), typeof(QVector3D), lhs, typeof(double), factor);
        }
        public static QVector3D operator*(QVector3D lhs, QVector3D vector) {
            return (QVector3D) staticInterceptor.Invoke("operator*=#", "operator*=(const QVector3D&)", typeof(QVector3D), typeof(QVector3D), lhs, typeof(QVector3D), vector);
        }
        public static QVector3D operator/(QVector3D lhs, double divisor) {
            return (QVector3D) staticInterceptor.Invoke("operator/=$", "operator/=(qreal)", typeof(QVector3D), typeof(QVector3D), lhs, typeof(double), divisor);
        }
        public static QVariant operatorQVariant(QVector3D lhs) {
            return (QVariant) staticInterceptor.Invoke("operator QVariant", "operator QVariant() const", typeof(QVariant), typeof(QVector3D), lhs);
        }
        public static double DotProduct(QVector3D v1, QVector3D v2) {
            return (double) staticInterceptor.Invoke("dotProduct##", "dotProduct(const QVector3D&, const QVector3D&)", typeof(double), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D CrossProduct(QVector3D v1, QVector3D v2) {
            return (QVector3D) staticInterceptor.Invoke("crossProduct##", "crossProduct(const QVector3D&, const QVector3D&)", typeof(QVector3D), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D Normal(QVector3D v1, QVector3D v2) {
            return (QVector3D) staticInterceptor.Invoke("normal##", "normal(const QVector3D&, const QVector3D&)", typeof(QVector3D), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D Normal(QVector3D v1, QVector3D v2, QVector3D v3) {
            return (QVector3D) staticInterceptor.Invoke("normal###", "normal(const QVector3D&, const QVector3D&, const QVector3D&)", typeof(QVector3D), typeof(QVector3D), v1, typeof(QVector3D), v2, typeof(QVector3D), v3);
        }
        public static bool operator==(QVector3D v1, QVector3D v2) {
            return (bool) staticInterceptor.Invoke("operator==##", "operator==(const QVector3D&, const QVector3D&)", typeof(bool), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static bool operator!=(QVector3D v1, QVector3D v2) {
            return !(bool) staticInterceptor.Invoke("operator==##", "operator==(const QVector3D&, const QVector3D&)", typeof(bool), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D operator+(QVector3D v1, QVector3D v2) {
            return (QVector3D) staticInterceptor.Invoke("operator+##", "operator+(const QVector3D&, const QVector3D&)", typeof(QVector3D), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D operator-(QVector3D v1, QVector3D v2) {
            return (QVector3D) staticInterceptor.Invoke("operator-##", "operator-(const QVector3D&, const QVector3D&)", typeof(QVector3D), typeof(QVector3D), v1, typeof(QVector3D), v2);
        }
        public static QVector3D operator*(double factor, QVector3D vector) {
            return (QVector3D) staticInterceptor.Invoke("operator*$#", "operator*(qreal, const QVector3D&)", typeof(QVector3D), typeof(double), factor, typeof(QVector3D), vector);
        }
        public static QVector3D operator-(QVector3D vector) {
            return (QVector3D) staticInterceptor.Invoke("operator-#", "operator-(const QVector3D&)", typeof(QVector3D), typeof(QVector3D), vector);
        }
        public static QVector3D operator*(QVector3D vector, QMatrix4x4 matrix) {
            return (QVector3D) staticInterceptor.Invoke("operator*##", "operator*(const QVector3D&, const QMatrix4x4&)", typeof(QVector3D), typeof(QVector3D), vector, typeof(QMatrix4x4), matrix);
        }
        public static QVector3D operator*(QMatrix4x4 matrix, QVector3D vector) {
            return (QVector3D) staticInterceptor.Invoke("operator*##", "operator*(const QMatrix4x4&, const QVector3D&)", typeof(QVector3D), typeof(QMatrix4x4), matrix, typeof(QVector3D), vector);
        }
    }
}
