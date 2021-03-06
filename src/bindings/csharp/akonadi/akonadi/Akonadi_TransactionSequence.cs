//Auto-generated by kalyptus. DO NOT EDIT.
namespace Akonadi {
    using Kimono;
    using System;
    using Qyoto;
    /// <remarks>
    ///  As soon as the first subjob is added, the transaction is started.
    ///  As soon as the last subjob has successfully finished, the transaction is committed.
    ///  If any subjob fails, the transaction is rolled back.
    ///  Alternatively, a TransactionSequence object can be used as a parent object
    ///  for a set of jobs to achieve the same behaviour without subclassing.
    /// </remarks>        <author> Volker Krause <vkrause@kde.org>
    ///  </author>
    ///         <short> Base class for jobs that need to run a sequence of sub-jobs in a transaction. </short>
    [SmokeClass("Akonadi::TransactionSequence")]
    public class TransactionSequence : Akonadi.Job, IDisposable {
        protected TransactionSequence(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(TransactionSequence), this);
        }
        /// <remarks>
        ///  Creates a new transaction sequence.
        /// <param> name="parent" The parent object.
        ///      </param></remarks>        <short>    Creates a new transaction sequence.</short>
        public TransactionSequence(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("TransactionSequence#", "TransactionSequence(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public TransactionSequence() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("TransactionSequence", "TransactionSequence()", typeof(void));
        }
        /// <remarks>
        ///  Commits the transaction as soon as all pending sub-jobs finished successfully.
        ///      </remarks>        <short>    Commits the transaction as soon as all pending sub-jobs finished successfully.</short>
        public void Commit() {
            interceptor.Invoke("commit", "commit()", typeof(void));
        }
        [SmokeMethod("addSubjob(KJob*)")]
        protected override bool AddSubjob(KJob job) {
            return (bool) interceptor.Invoke("addSubjob#", "addSubjob(KJob*)", typeof(bool), typeof(KJob), job);
        }
        [SmokeMethod("doStart()")]
        protected override void DoStart() {
            interceptor.Invoke("doStart", "doStart()", typeof(void));
        }
        [Q_SLOT("void slotResult(KJob*)")]
        [SmokeMethod("slotResult(KJob*)")]
        protected override void SlotResult(KJob job) {
            interceptor.Invoke("slotResult#", "slotResult(KJob*)", typeof(void), typeof(KJob), job);
        }
        ~TransactionSequence() {
            interceptor.Invoke("~TransactionSequence", "~TransactionSequence()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~TransactionSequence", "~TransactionSequence()", typeof(void));
        }
        protected new ITransactionSequenceSignals Emit {
            get { return (ITransactionSequenceSignals) Q_EMIT; }
        }
    }

    public interface ITransactionSequenceSignals : Akonadi.IJobSignals {
    }
}
