//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    using System.Text;
    using System.Collections.Generic;
    /// <remarks>
    ///  @class RunnerScript plasma/scripting/runnerscript.h <Plasma/Scripting/RunnerScript>
    ///  See <see cref="IRunnerScriptSignals"></see> for signals emitted by RunnerScript
    /// </remarks>        <short> Provides a restricted interface for scripting a runner.  </short>
    [SmokeClass("Plasma::RunnerScript")]
    public class RunnerScript : Plasma.ScriptEngine, IDisposable {
        protected RunnerScript(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(RunnerScript), this);
        }
        /// <remarks>
        ///  Default constructor for a RunnerScript.
        ///  Subclasses should not attempt to access the Plasma.AbstractRunner
        ///  associated with this RunnerScript in the constructor. All
        ///  such set up that requires the AbstractRunner itself should be done
        ///  in the init() method.
        ///      </remarks>        <short>    Default constructor for a RunnerScript.</short>
        public RunnerScript(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("RunnerScript#", "RunnerScript(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public RunnerScript() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("RunnerScript", "RunnerScript()", typeof(void));
        }
        /// <remarks>
        ///  Sets the Plasma.AbstractRunner associated with this RunnerScript
        ///      </remarks>        <short>    Sets the Plasma.AbstractRunner associated with this RunnerScript      </short>
        public void SetRunner(Plasma.AbstractRunner runner) {
            interceptor.Invoke("setRunner#", "setRunner(Plasma::AbstractRunner*)", typeof(void), typeof(Plasma.AbstractRunner), runner);
        }
        /// <remarks>
        ///  Returns the Plasma.AbstractRunner associated with this script component
        ///      </remarks>        <short>    Returns the Plasma.AbstractRunner associated with this script component      </short>
        public Plasma.AbstractRunner Runner() {
            return (Plasma.AbstractRunner) interceptor.Invoke("runner", "runner() const", typeof(Plasma.AbstractRunner));
        }
        /// <remarks>
        ///  Called when the script should create QueryMatch instances through
        ///  RunnerContext.AddInformationalMatch, RunnerContext.AddExactMatch, and
        ///  RunnerContext.AddPossibleMatch.
        ///      </remarks>        <short>    Called when the script should create QueryMatch instances through  RunnerContext.AddInformationalMatch, RunnerContext.AddExactMatch, and  RunnerContext.AddPossibleMatch.</short>
        [SmokeMethod("match(Plasma::RunnerContext&)")]
        public virtual void Match(Plasma.RunnerContext search) {
            interceptor.Invoke("match#", "match(Plasma::RunnerContext&)", typeof(void), typeof(Plasma.RunnerContext), search);
        }
        /// <remarks>
        ///  Called whenever an exact or possible match associated with this
        ///  runner is triggered.
        ///      </remarks>        <short>    Called whenever an exact or possible match associated with this  runner is triggered.</short>
        [SmokeMethod("run(const Plasma::RunnerContext&, const Plasma::QueryMatch&)")]
        public virtual void Run(Plasma.RunnerContext search, Plasma.QueryMatch action) {
            interceptor.Invoke("run##", "run(const Plasma::RunnerContext&, const Plasma::QueryMatch&)", typeof(void), typeof(Plasma.RunnerContext), search, typeof(Plasma.QueryMatch), action);
        }
        /// <remarks>
        /// </remarks>        <return> absolute path to the main script file for this plasmoid
        ///      </return>
        ///         <short>   </short>
        [SmokeMethod("mainScript() const")]
        protected override string MainScript() {
            return (string) interceptor.Invoke("mainScript", "mainScript() const", typeof(string));
        }
        /// <remarks>
        /// </remarks>        <return> the Package associated with this plasmoid which can
        ///          be used to request resources, such as images and
        ///          interface files.
        ///      </return>
        ///         <short>   </short>
        [SmokeMethod("package() const")]
        protected override Plasma.Package Package() {
            return (Plasma.Package) interceptor.Invoke("package", "package() const", typeof(Plasma.Package));
        }
        /// <remarks>
        /// </remarks>        <return> the KPluginInfo associated with this plasmoid
        ///      </return>
        ///         <short>   </short>
        protected KPluginInfo Description() {
            return (KPluginInfo) interceptor.Invoke("description", "description() const", typeof(KPluginInfo));
        }
        /// <remarks>
        /// </remarks>        <return> a Plasma.DataEngine matchin name
        /// </return>
        ///         <short>   </short>
        protected Plasma.DataEngine DataEngine(string name) {
            return (Plasma.DataEngine) interceptor.Invoke("dataEngine$", "dataEngine(const QString&)", typeof(Plasma.DataEngine), typeof(string), name);
        }
        protected KConfigGroup Config() {
            return (KConfigGroup) interceptor.Invoke("config", "config() const", typeof(KConfigGroup));
        }
        protected void SetIgnoredTypes(uint types) {
            interceptor.Invoke("setIgnoredTypes$", "setIgnoredTypes(Plasma::RunnerContext::Types)", typeof(void), typeof(uint), types);
        }
        protected void SetHasRunOptions(bool hasRunOptions) {
            interceptor.Invoke("setHasRunOptions$", "setHasRunOptions(bool)", typeof(void), typeof(bool), hasRunOptions);
        }
        protected void SetSpeed(Plasma.AbstractRunner.Speed newSpeed) {
            interceptor.Invoke("setSpeed$", "setSpeed(Plasma::AbstractRunner::Speed)", typeof(void), typeof(Plasma.AbstractRunner.Speed), newSpeed);
        }
        protected void SetPriority(Plasma.AbstractRunner.Priority newPriority) {
            interceptor.Invoke("setPriority$", "setPriority(Plasma::AbstractRunner::Priority)", typeof(void), typeof(Plasma.AbstractRunner.Priority), newPriority);
        }
        protected List<KService> ServiceQuery(string serviceType, string constraint) {
            return (List<KService>) interceptor.Invoke("serviceQuery$$", "serviceQuery(const QString&, const QString&) const", typeof(List<KService>), typeof(string), serviceType, typeof(string), constraint);
        }
        protected List<KService> ServiceQuery(string serviceType) {
            return (List<KService>) interceptor.Invoke("serviceQuery$", "serviceQuery(const QString&) const", typeof(List<KService>), typeof(string), serviceType);
        }
        protected QAction AddAction(string id, QIcon icon, string text) {
            return (QAction) interceptor.Invoke("addAction$#$", "addAction(const QString&, const QIcon&, const QString&)", typeof(QAction), typeof(string), id, typeof(QIcon), icon, typeof(string), text);
        }
        protected void AddAction(string id, QAction action) {
            interceptor.Invoke("addAction$#", "addAction(const QString&, QAction*)", typeof(void), typeof(string), id, typeof(QAction), action);
        }
        protected void RemoveAction(string id) {
            interceptor.Invoke("removeAction$", "removeAction(const QString&)", typeof(void), typeof(string), id);
        }
        protected QAction Action(string id) {
            return (QAction) interceptor.Invoke("action$", "action(const QString&) const", typeof(QAction), typeof(string), id);
        }
        protected string Actions() {
            return (string) interceptor.Invoke("actions", "actions() const", typeof(string));
        }
        protected void ClearActions() {
            interceptor.Invoke("clearActions", "clearActions()", typeof(void));
        }
        protected void AddSyntax(Plasma.RunnerSyntax syntax) {
            interceptor.Invoke("addSyntax#", "addSyntax(const Plasma::RunnerSyntax&)", typeof(void), typeof(Plasma.RunnerSyntax), syntax);
        }
        protected void SetSyntaxes(List<Plasma.RunnerSyntax> syns) {
            interceptor.Invoke("setSyntaxes?", "setSyntaxes(const QList<Plasma::RunnerSyntax>&)", typeof(void), typeof(List<Plasma.RunnerSyntax>), syns);
        }
        ~RunnerScript() {
            interceptor.Invoke("~RunnerScript", "~RunnerScript()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~RunnerScript", "~RunnerScript()", typeof(void));
        }
        protected new IRunnerScriptSignals Emit {
            get { return (IRunnerScriptSignals) Q_EMIT; }
        }
    }

    public interface IRunnerScriptSignals : Plasma.IScriptEngineSignals {
        [Q_SIGNAL("void prepare()")]
        void Prepare();
        [Q_SIGNAL("void teardown()")]
        void Teardown();
        [Q_SIGNAL("void createRunOptions(QWidget*)")]
        void CreateRunOptions(QWidget widget);
        [Q_SIGNAL("void reloadConfiguration()")]
        void ReloadConfiguration();
        [Q_SIGNAL("void actionsForMatch(Plasma::QueryMatch, QList<QAction* >*)")]
        void ActionsForMatch(Plasma.QueryMatch match, List<QAction> actions);
    }
}
