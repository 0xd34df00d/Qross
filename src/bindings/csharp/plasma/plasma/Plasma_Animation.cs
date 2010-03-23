//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    /// <remarks>
    ///  @brief Abstract representation of a single animation.
    /// </remarks>        <short>    @brief Abstract representation of a single animation.</short>
    [SmokeClass("Plasma::Animation")]
    public abstract class Animation : QAbstractAnimation {
        protected Animation(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(Animation), this);
        }
        /// <remarks>
        ///  Animation movement reference (used by \ref RotationAnimation).
        ///      </remarks>        <short>    Animation movement reference (used by \ref RotationAnimation).</short>
        public enum Reference {
            Center = 0,
            Up = 1,
            Down = 2,
            Left = 3,
            Right = 4,
        }
        /// <remarks>
        ///  The movement direction of an animation.
        ///      </remarks>        <short>    The movement direction of an animation.</short>
        public enum MovementDirection {
            MoveUp = 0,
            MoveUpRight = 1,
            MoveRight = 2,
            MoveDownRight = 3,
            MoveDown = 4,
            MoveDownLeft = 5,
            MoveLeft = 6,
            MoveUpLeft = 7,
        }
        [Q_PROPERTY("int", "duration")]
        public new int Duration {
            get { return (int) interceptor.Invoke("duration", "duration()", typeof(int)); }
            set { interceptor.Invoke("setDuration$", "setDuration(int)", typeof(void), typeof(int), value); }
        }
        [Q_PROPERTY("QEasingCurve", "easingCurve")]
        public QEasingCurve EasingCurve {
            get { return (QEasingCurve) interceptor.Invoke("easingCurve", "easingCurve()", typeof(QEasingCurve)); }
            set { interceptor.Invoke("setEasingCurve#", "setEasingCurve(QEasingCurve)", typeof(void), typeof(QEasingCurve), value); }
        }
        [Q_PROPERTY("QGraphicsWidget*", "targetWidget")]
        public QGraphicsWidget TargetWidget {
            get { return (QGraphicsWidget) interceptor.Invoke("targetWidget", "targetWidget()", typeof(QGraphicsWidget)); }
            set { interceptor.Invoke("setTargetWidget#", "setTargetWidget(QGraphicsWidget*)", typeof(void), typeof(QGraphicsWidget), value); }
        }
        /// <remarks>
        ///  Default constructor.
        /// <param> name="parent" Object parent (might be set when using
        ///  \ref Animator.Create factory).
        /// </param>     </remarks>        <short>    Default constructor.</short>
        public Animation(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("Animation#", "Animation(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public Animation() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("Animation", "Animation()", typeof(void));
        }
        /// <remarks>
        ///  Change the animation duration. Default is 250ms.
        ///  @arg duration The new duration of the animation.
        ///      </remarks>        <short>    Change the animation duration.</short>
        [SmokeMethod("setDuration(int)")]
        protected virtual void SetDuration(int duration) {
            interceptor.Invoke("setDuration$", "setDuration(int)", typeof(void), typeof(int), duration);
        }
        [SmokeMethod("setDuration()")]
        protected virtual void SetDuration() {
            interceptor.Invoke("setDuration", "setDuration()", typeof(void));
        }
        /// <remarks>
        ///  QAbstractAnimation will call this method while the animation
        ///  is running. Each specialized animation class should implement
        ///  the correct behavior for it.
        /// <param> name="currentTime" Slapsed time using the \ref duration as reference
        ///  (it will be from duration up to zero if the animation is running
        ///  backwards).
        ///      </param></remarks>        <short>    QAbstractAnimation will call this method while the animation  is running.</short>
        [SmokeMethod("updateCurrentTime(int)")]
        protected override void UpdateCurrentTime(int currentTime) {
            interceptor.Invoke("updateCurrentTime$", "updateCurrentTime(int)", typeof(void), typeof(int), currentTime);
        }
        protected new IAnimationSignals Emit {
            get { return (IAnimationSignals) Q_EMIT; }
        }
    }

    public interface IAnimationSignals : IQAbstractAnimationSignals {
    }
}
