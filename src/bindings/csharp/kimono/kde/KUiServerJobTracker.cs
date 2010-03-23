//Auto-generated by kalyptus. DO NOT EDIT.
namespace Kimono {
    using System;
    using Qyoto;
    /// <remarks>
    ///  The interface to implement to track the progresses of a job.
    ///  </remarks>        <short>    The interface to implement to track the progresses of a job.</short>
    [SmokeClass("KUiServerJobTracker")]
    public class KUiServerJobTracker : KJobTrackerInterface, IDisposable {
        protected KUiServerJobTracker(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(KUiServerJobTracker), this);
        }
        /// <remarks>
        ///  Creates a new KJobTrackerInterface
        /// <param> name="parent" the parent object
        ///      </param></remarks>        <short>    Creates a new KJobTrackerInterface </short>
        public KUiServerJobTracker(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KUiServerJobTracker#", "KUiServerJobTracker(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public KUiServerJobTracker() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("KUiServerJobTracker", "KUiServerJobTracker()", typeof(void));
        }
        /// <remarks>
        ///  Register a new job in this tracker.
        /// <param> name="job" the job to register
        ///      </param></remarks>        <short>    Register a new job in this tracker.</short>
        [SmokeMethod("registerJob(KJob*)")]
        public override void RegisterJob(KJob job) {
            interceptor.Invoke("registerJob#", "registerJob(KJob*)", typeof(void), typeof(KJob), job);
        }
        /// <remarks>
        ///  Unregister a job from this tracker.
        /// <param> name="job" the job to unregister
        ///      </param></remarks>        <short>    Unregister a job from this tracker.</short>
        [SmokeMethod("unregisterJob(KJob*)")]
        public override void UnregisterJob(KJob job) {
            interceptor.Invoke("unregisterJob#", "unregisterJob(KJob*)", typeof(void), typeof(KJob), job);
        }
        /// <remarks>
        ///  The following slots are inherited from KJobTrackerInterface.
        ///      </remarks>        <short>    The following slots are inherited from KJobTrackerInterface.</short>
        [Q_SLOT("void finished(KJob*)")]
        [SmokeMethod("finished(KJob*)")]
        protected override void Finished(KJob job) {
            interceptor.Invoke("finished#", "finished(KJob*)", typeof(void), typeof(KJob), job);
        }
        [Q_SLOT("void suspended(KJob*)")]
        [SmokeMethod("suspended(KJob*)")]
        protected override void Suspended(KJob job) {
            interceptor.Invoke("suspended#", "suspended(KJob*)", typeof(void), typeof(KJob), job);
        }
        [Q_SLOT("void resumed(KJob*)")]
        [SmokeMethod("resumed(KJob*)")]
        protected override void Resumed(KJob job) {
            interceptor.Invoke("resumed#", "resumed(KJob*)", typeof(void), typeof(KJob), job);
        }
        [Q_SLOT("void description(KJob*, QString, QPair<QString, QString>, QPair<QString, QString>)")]
        [SmokeMethod("description(KJob*, const QString&, const QPair<QString,QString>&, const QPair<QString,QString>&)")]
        protected override void Description(KJob job, string title, QPair<string, string> field1, QPair<string, string> field2) {
            interceptor.Invoke("description#$??", "description(KJob*, const QString&, const QPair<QString,QString>&, const QPair<QString,QString>&)", typeof(void), typeof(KJob), job, typeof(string), title, typeof(QPair<string, string>), field1, typeof(QPair<string, string>), field2);
        }
        [Q_SLOT("void infoMessage(KJob*, QString, QString)")]
        [SmokeMethod("infoMessage(KJob*, const QString&, const QString&)")]
        protected override void InfoMessage(KJob job, string plain, string rich) {
            interceptor.Invoke("infoMessage#$$", "infoMessage(KJob*, const QString&, const QString&)", typeof(void), typeof(KJob), job, typeof(string), plain, typeof(string), rich);
        }
        [Q_SLOT("void totalAmount(KJob*, KJob::Unit, qulonglong)")]
        [SmokeMethod("totalAmount(KJob*, KJob::Unit, qulonglong)")]
        protected override void TotalAmount(KJob job, KJob.Unit unit, ulong amount) {
            interceptor.Invoke("totalAmount#$$", "totalAmount(KJob*, KJob::Unit, qulonglong)", typeof(void), typeof(KJob), job, typeof(KJob.Unit), unit, typeof(ulong), amount);
        }
        [Q_SLOT("void processedAmount(KJob*, KJob::Unit, qulonglong)")]
        [SmokeMethod("processedAmount(KJob*, KJob::Unit, qulonglong)")]
        protected override void ProcessedAmount(KJob job, KJob.Unit unit, ulong amount) {
            interceptor.Invoke("processedAmount#$$", "processedAmount(KJob*, KJob::Unit, qulonglong)", typeof(void), typeof(KJob), job, typeof(KJob.Unit), unit, typeof(ulong), amount);
        }
        [Q_SLOT("void percent(KJob*, unsigned long)")]
        [SmokeMethod("percent(KJob*, unsigned long)")]
        protected override void Percent(KJob job, ulong percent) {
            interceptor.Invoke("percent#$", "percent(KJob*, unsigned long)", typeof(void), typeof(KJob), job, typeof(ulong), percent);
        }
        [Q_SLOT("void speed(KJob*, unsigned long)")]
        [SmokeMethod("speed(KJob*, unsigned long)")]
        protected override void Speed(KJob job, ulong value) {
            interceptor.Invoke("speed#$", "speed(KJob*, unsigned long)", typeof(void), typeof(KJob), job, typeof(ulong), value);
        }
        ~KUiServerJobTracker() {
            interceptor.Invoke("~KUiServerJobTracker", "~KUiServerJobTracker()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~KUiServerJobTracker", "~KUiServerJobTracker()", typeof(void));
        }
        protected new IKUiServerJobTrackerSignals Emit {
            get { return (IKUiServerJobTrackerSignals) Q_EMIT; }
        }
    }

    public interface IKUiServerJobTrackerSignals : IKJobTrackerInterfaceSignals {
    }
}
