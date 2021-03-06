//Auto-generated by kalyptus. DO NOT EDIT.
namespace KFileShare {
    using Kimono;
    using System;
    using Qyoto;
    public enum Authorization {
        NotInitialized = 0,
        ErrorNotFound = 1,
        Authorized = 2,
        UserNotAllowed = 3,
    }
    /// <remarks>
    ///  The used share mode.
    ///  Simple means that the simple sharing dialog is used and
    ///  users can share only folders from there HOME folder.
    ///  Advanced means that the advanced sharing dialog is used and
    ///  users can share any folder.
    ///      </remarks>        <short>    The used share mode.</short>
    public enum ShareMode {
        Simple = 0,
        Advanced = 1,
    }
    /// <remarks>
    ///  Common functionality for the file sharing
    ///  (communication with the backend)
    ///  </remarks>        <short>    Common functionality for the file sharing  (communication with the backend)  </short>
    [SmokeClass("KFileShare")]
    public class Global {
        private static SmokeInvocation staticInterceptor = null;
        static Global() {
            staticInterceptor = new SmokeInvocation(typeof(Global), null);
        }
        /// <remarks>
        ///  Reads the file share configuration file
        ///      </remarks>        <short>    Reads the file share configuration file      </short>
        public static void ReadConfig() {
            staticInterceptor.Invoke("readConfig", "readConfig()", typeof(void));
        }
        /// <remarks>
        ///  Reads the list of shared folders
        ///      </remarks>        <short>    Reads the list of shared folders      </short>
        public static void ReadShareList() {
            staticInterceptor.Invoke("readShareList", "readShareList()", typeof(void));
        }
        /// <remarks>
        ///  Call this to know if a directory is currently shared
        ///      </remarks>        <short>    Call this to know if a directory is currently shared      </short>
        public static bool IsDirectoryShared(string path) {
            return (bool) staticInterceptor.Invoke("isDirectoryShared$", "isDirectoryShared(const QString&)", typeof(bool), typeof(string), path);
        }
        /// <remarks>
        ///  Call this to know if the current user is authorized to share directories
        ///      </remarks>        <short>    Call this to know if the current user is authorized to share directories      </short>
        public static KFileShare.Authorization authorization() {
            return (KFileShare.Authorization) staticInterceptor.Invoke("authorization", "authorization()", typeof(KFileShare.Authorization));
        }
        /// <remarks>
        ///  Uses a suid perl script to share the given path 
        ///  with NFS and Samba
        /// <param> name="path" the path to share
        /// </param><param> name="shared" whether the path should be shared or not
        /// </param></remarks>        <return> whether the perl script was successful
        ///      </return>
        ///         <short>    Uses a suid perl script to share the given path   with NFS and Samba </short>
        public static bool SetShared(string path, bool shared) {
            return (bool) staticInterceptor.Invoke("setShared$$", "setShared(const QString&, bool)", typeof(bool), typeof(string), path, typeof(bool), shared);
        }
        /// <remarks>
        ///  Returns whether sharing is enabled
        ///  If this is false, file sharing is disabled and
        ///  nobody can share files.
        ///      </remarks>        <short>    Returns whether sharing is enabled  If this is false, file sharing is disabled and  nobody can share files.</short>
        public static bool SharingEnabled() {
            return (bool) staticInterceptor.Invoke("sharingEnabled", "sharingEnabled()", typeof(bool));
        }
        /// <remarks>
        ///  Returns whether file sharing is restricted.
        ///  If it is not restricted every user can shar files.
        ///  If it is restricted only users in the configured
        ///  file share group can share files.
        ///      </remarks>        <short>    Returns whether file sharing is restricted.</short>
        public static bool IsRestricted() {
            return (bool) staticInterceptor.Invoke("isRestricted", "isRestricted()", typeof(bool));
        }
        /// <remarks>
        ///  Returns the group that is used for file sharing.
        ///  That is, all users in that group are allowed to
        ///  share files if file sharing is restricted.
        ///      </remarks>        <short>    Returns the group that is used for file sharing.</short>
        public static string FileShareGroup() {
            return (string) staticInterceptor.Invoke("fileShareGroup", "fileShareGroup()", typeof(string));
        }
        /// <remarks>
        ///  Returns the configured share mode
        ///      </remarks>        <short>    Returns the configured share mode      </short>
        public static KFileShare.ShareMode shareMode() {
            return (KFileShare.ShareMode) staticInterceptor.Invoke("shareMode", "shareMode()", typeof(KFileShare.ShareMode));
        }
        /// <remarks>
        ///  Returns whether Samba is enabled
        ///      </remarks>        <short>    Returns whether Samba is enabled      </short>
        public static bool SambaEnabled() {
            return (bool) staticInterceptor.Invoke("sambaEnabled", "sambaEnabled()", typeof(bool));
        }
        /// <remarks> 
        ///  Returns whether NFS is enabled
        ///      </remarks>        <short>     Returns whether NFS is enabled      </short>
        public static bool NfsEnabled() {
            return (bool) staticInterceptor.Invoke("nfsEnabled", "nfsEnabled()", typeof(bool));
        }
    }
}
