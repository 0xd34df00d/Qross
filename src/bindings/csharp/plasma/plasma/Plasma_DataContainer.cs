//Auto-generated by kalyptus. DO NOT EDIT.
namespace Plasma {
    using Plasma;
    using System;
    using Kimono;
    using Qyoto;
    using System.Collections.Generic;
    /// <remarks>
    ///  @class DataContainer plasma/datacontainer.h <Plasma/DataContainer>
    ///  @brief A set of data exported via a DataEngine
    ///  Plasma.DataContainer wraps the data exported by a DataEngine
    ///  implementation, providing a generic wrapper for the data.
    ///  A DataContainer may have zero or more associated pieces of data which
    ///  are keyed by strings. The data itself is stored as QVariants. This allows
    ///  easy and flexible retrieval of the information associated with this object
    ///  without writing DataContainer or DataEngine specific code in visualizations.
    ///  If you are creating your own DataContainer objects (and are passing them to
    ///  DataEngine.AddSource()), you normally just need to listen to the
    ///  updateRequested() signal (as well as any other methods you might have of
    ///  being notified of new data) and call setData() to actually update the data.
    ///  Then you need to either trigger the scheduleSourcesUpdated signal of the
    ///  parent DataEngine or call checkForUpdate() on the DataContainer.
    ///  You also need to set a suitable name for the source with setObjectName().
    ///  See DataEngine.AddSource() for more information.
    ///  Note that there is normally no need to subclass DataContainer, except as
    ///  a way of encapsulating the data retreival for a source, since all notifications
    ///  are done via signals rather than methods.
    ///  See <see cref="IDataContainerSignals"></see> for signals emitted by DataContainer
    /// </remarks>        <short>    @class DataContainer plasma/datacontainer.</short>
    [SmokeClass("Plasma::DataContainer")]
    public class DataContainer : QObject, IDisposable {
        protected DataContainer(Type dummy) : base((Type) null) {}
        protected new void CreateProxy() {
            interceptor = new SmokeInvocation(typeof(DataContainer), this);
        }
        /// <remarks>
        ///  Constructs a default DataContainer that has no name or data
        ///  associated with it
        /// </remarks>        <short>    Constructs a default DataContainer that has no name or data  associated with it </short>
        public DataContainer(QObject parent) : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("DataContainer#", "DataContainer(QObject*)", typeof(void), typeof(QObject), parent);
        }
        public DataContainer() : this((Type) null) {
            CreateProxy();
            interceptor.Invoke("DataContainer", "DataContainer()", typeof(void));
        }
        /// <remarks>
        ///  Returns the data for this DataContainer
        /// </remarks>        <short>    Returns the data for this DataContainer </short>
        public Dictionary<string, QVariant> Data() {
            return (Dictionary<string, QVariant>) interceptor.Invoke("data", "data() const", typeof(Dictionary<string, QVariant>));
        }
        /// <remarks>
        ///  Set a value for a key.
        ///  This also marks this source as needing to signal an update.
        ///  If you call setData() directly on a DataContainer, you need to
        ///  either trigger the scheduleSourcesUpdated() slot for the
        ///  data engine it belongs to or call checkForUpdate() on the
        ///  DataContainer.
        /// <param> name="key" a string used as the key for the data
        /// </param><param> name="value" a QVariant holding the actual data. If a null or invalid
        ///               QVariant is passed in and the key currently exists in the
        ///               data, then the data entry is removed
        /// </param></remarks>        <short>    Set a value for a key.</short>
        public void SetData(string key, QVariant value) {
            interceptor.Invoke("setData$#", "setData(const QString&, const QVariant&)", typeof(void), typeof(string), key, typeof(QVariant), value);
        }
        /// <remarks>
        ///  Removes all data currently associated with this source
        ///  If you call removeAllData() on a DataContainer, you need to
        ///  either trigger the scheduleSourcesUpdated() slot for the
        ///  data engine it belongs to or call checkForUpdate() on the
        ///  DataContainer.
        /// </remarks>        <short>    Removes all data currently associated with this source </short>
        public void RemoveAllData() {
            interceptor.Invoke("removeAllData", "removeAllData()", typeof(void));
        }
        /// <remarks>
        /// </remarks>        <return> true if the visualization is currently connected
        ///          </return>
        ///         <short>   </short>
        public bool VisualizationIsConnected(QObject visualization) {
            return (bool) interceptor.Invoke("visualizationIsConnected#", "visualizationIsConnected(QObject*) const", typeof(bool), typeof(QObject), visualization);
        }
        /// <remarks>
        ///  Connects an object to this DataContainer.
        ///  May be called repeatedly for the same visualization without
        ///  side effects
        /// <param> name="visualization" the object to connect to this DataContainer
        /// </param><param> name="pollingInterval" the time in milliseconds between updates
        /// </param><param> name="alignment" the clock position to align updates to
        /// </param></remarks>        <short>    Connects an object to this DataContainer.</short>
        public void ConnectVisualization(QObject visualization, uint pollingInterval, Plasma.IntervalAlignment alignment) {
            interceptor.Invoke("connectVisualization#$$", "connectVisualization(QObject*, uint, Plasma::IntervalAlignment)", typeof(void), typeof(QObject), visualization, typeof(uint), pollingInterval, typeof(Plasma.IntervalAlignment), alignment);
        }
        /// <remarks>
        ///  Disconnects an object from this DataContainer.
        ///  Note that if this source was created by DataEngine.SourceRequestEvent(),
        ///  it will be deleted by DataEngine once control returns to the event loop.
        /// </remarks>        <short>    Disconnects an object from this DataContainer.</short>
        [Q_SLOT("void disconnectVisualization(QObject*)")]
        public void DisconnectVisualization(QObject visualization) {
            interceptor.Invoke("disconnectVisualization#", "disconnectVisualization(QObject*)", typeof(void), typeof(QObject), visualization);
        }
        /// <remarks>
        ///  Forces immediate update signals to all visualizations
        /// </remarks>        <short>    Forces immediate update signals to all visualizations </short>
        [Q_SLOT("void forceImmediateUpdate()")]
        public void ForceImmediateUpdate() {
            interceptor.Invoke("forceImmediateUpdate", "forceImmediateUpdate()", typeof(void));
        }
        /// <remarks>
        ///  Checks whether any data has changed and, if so, emits dataUpdated().
        /// </remarks>        <short>    Checks whether any data has changed and, if so, emits dataUpdated().</short>
        protected void CheckForUpdate() {
            interceptor.Invoke("checkForUpdate", "checkForUpdate()", typeof(void));
        }
        /// <remarks>
        ///  Returns how long ago, in msecs, that the data in this container was last updated.
        ///  This is used by DataEngine to compress updates that happen more quickly than the
        ///  minimum polling interval by calling setNeedsUpdate() instead of calling
        ///  updateSourceEvent() immediately.
        /// </remarks>        <short>    Returns how long ago, in msecs, that the data in this container was last updated.</short>
        protected uint TimeSinceLastUpdate() {
            return (uint) interceptor.Invoke("timeSinceLastUpdate", "timeSinceLastUpdate() const", typeof(uint));
        }
        /// <remarks>
        ///  Indicates that the data should be treated as dirty the next time hasUpdates() is called.
        ///  This is needed for the case where updateRequested() is triggered but we don't want to
        ///  update the data immediately because it has just been updated.  The second request won't
        ///  be fulfilled in this case, because we never updated the data and so never called
        ///  checkForUpdate().  So we claim it needs an update anyway.
        /// </remarks>        <short>    Indicates that the data should be treated as dirty the next time hasUpdates() is called.</short>
        protected void SetNeedsUpdate(bool update) {
            interceptor.Invoke("setNeedsUpdate$", "setNeedsUpdate(bool)", typeof(void), typeof(bool), update);
        }
        protected void SetNeedsUpdate() {
            interceptor.Invoke("setNeedsUpdate", "setNeedsUpdate()", typeof(void));
        }
        /// <remarks>
        ///  Check if the DataContainer is still in use.
        ///  If not the signal "becameUnused" will be emitted.
        ///  Warning: The DataContainer may be invalid after calling this function, because a listener
        ///  to becameUnused() may have deleted it.
        /// </remarks>        <short>    Check if the DataContainer is still in use.</short>
        [Q_SLOT("void checkUsage()")]
        protected void CheckUsage() {
            interceptor.Invoke("checkUsage", "checkUsage()", typeof(void));
        }
        ~DataContainer() {
            interceptor.Invoke("~DataContainer", "~DataContainer()", typeof(void));
        }
        public new void Dispose() {
            interceptor.Invoke("~DataContainer", "~DataContainer()", typeof(void));
        }
        protected new IDataContainerSignals Emit {
            get { return (IDataContainerSignals) Q_EMIT; }
        }
    }

    public interface IDataContainerSignals : IQObjectSignals {
        /// <remarks>
        ///  Emitted when the data has been updated, allowing visualizations to
        ///  reflect the new data.
        ///  Note that you should not normally emit this directly.  Instead, use
        ///  checkForUpdate() or the DataEngine.ScheduleSourcesUpdated() slot.
        /// <param> name="source" the objectName() of the DataContainer (and hence the name
        ///                of the source) that updated its data
        /// </param><param> name="data" the updated data
        /// </param></remarks>        <short>    Emitted when the data has been updated, allowing visualizations to  reflect the new data.</short>
        [Q_SIGNAL("void dataUpdated(QString, Plasma::DataEngine::Data)")]
        void DataUpdated(string source, Dictionary<string, QVariant> data);
        /// <remarks>
        ///  Emitted when the last visualization is disconnected.
        ///  Note that if this source was created by DataEngine.SourceRequestEvent(),
        ///  it will be deleted by DataEngine once control returns to the event loop
        ///  after this signal is emitted.
        /// <param> name="source" the name of the source that became unused
        /// </param></remarks>        <short>    Emitted when the last visualization is disconnected.</short>
        [Q_SIGNAL("void becameUnused(QString)")]
        void BecameUnused(string source);
        /// <remarks>
        ///  Emitted when an update is requested.
        ///  If a polling interval was passed connectVisualization(), this signal
        ///  will be emitted every time the interval expires.
        ///  Note that if you create your own DataContainer (and pass it to
        ///  DataEngine.AddSource()), you will need to listen to this signal
        ///  and refresh the data when it is triggered.
        /// <param> name="source" the datacontainer the update was requested for.  Useful
        ///                 for classes that update the data for several containers.
        /// </param></remarks>        <short>    Emitted when an update is requested.</short>
        [Q_SIGNAL("void updateRequested(DataContainer*)")]
        void UpdateRequested(Plasma.DataContainer source);
    }
}
