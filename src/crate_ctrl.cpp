#include "crate_ctrl.hpp"
#include "hbr_crate.hpp"
#include "pretty_print/pretty_print.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sched.h>


#define pivot_root(new_root, put_old) syscall(SYS_pivot_root, new_root, put_old)
#define CRATE_FS_DIR "fs"
#define CRATE_FS_OLD_ROOT_DIR "./host_root"

int crate_proc_run(const char * exec_path, char * const * exec_argv) {

    // call fork to create a new process (a subprocess of the caller)
    pid_t fork_ret = fork();

    if (fork_ret == -1) {
        // fork call failed, print error and exit
        PrettyPrint::log_error("failed to fork process: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_FORKERR);
    }

    if (fork_ret == 0) {
        // inside forked process

        // containerize this process by inheriting the crate's create spec
        proc_inherit_crate_spec();
        // call execvp to run the executable
        if(execvp(exec_path, exec_argv) == -1) {
            // exec call failed, print error and _exit
            PrettyPrint::log_error("when switching execution in crate environment: %s", strerror(errno));
            _exit(HBRC_EXIT_CODE_EXECERR);
        }

        // code here is never executed.

    } else {
        // inside parent process

        PrettyPrint::log("crate process pid: %i\n", fork_ret);

    }

    // wait for the child process to finish before ending
    int wait_status;
    waitpid(fork_ret, &wait_status, 0);

    return wait_status;
}

void proc_inherit_crate_spec() {

    // create a new unix time share and mount share
    if (unshare(CLONE_NEWUTS | CLONE_NEWNS) == -1) {
        PrettyPrint::log_error("when running unshare: %s", strerror(errno));
        perror("unshare");
        _exit(HBRC_EXIT_CODE_UTSERR);
    }

    sethostname("testcontainer", 14);

    if (mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1) {
        PrettyPrint::log_error("unable to mount / to none", true);
        _exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // mount the crate file system
    if (mount(CRATE_FS_DIR, CRATE_FS_DIR, NULL, MS_BIND | MS_PRIVATE | MS_REC, NULL) == -1) {
        PrettyPrint::log_error("unable to mount crate file system", true);
        _exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // change directory to file system
    if (chdir(CRATE_FS_DIR) == -1) {
        PrettyPrint::log_error("crate file system does not exist, or insufficient access", true);
        _exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // create directory for old root for root pivoting
    if (mkdir(CRATE_FS_OLD_ROOT_DIR, 0755) == -1) {
        PrettyPrint::log_error("unable to create old root directory", true);
        _exit(HBRC_EXIT_CODE_UNKNOWN);
    }
    
    // pivot root to switch the root directory for the containerized process
    if (syscall(SYS_pivot_root, ".", CRATE_FS_OLD_ROOT_DIR) == -1) {
        PrettyPrint::log_error("unable to pivot root to crate file system", true);
        perror("pivot_root");
        printf("%i\n", errno);
        _exit(HBRC_EXIT_CODE_UTSERR);
    }

    // change directories to new root
    if (chdir("/") == -1) {
        PrettyPrint::log_error("unable to switch to new root file system", true);
        _exit(HBRC_EXIT_CODE_UTSERR);
    }

    // unmount the old_root to prevent host machine access
    if (umount2(CRATE_FS_OLD_ROOT_DIR, MNT_DETACH)) {
        PrettyPrint::log_error("unable to unmount host root from containerized process", true);
        _exit(HBRC_EXIT_CODE_UTSERR);
    }

    // remove the old_root directory
    if (rmdir(CRATE_FS_OLD_ROOT_DIR) == -1) {
        PrettyPrint::log_error("unable to rm host root directory from containerized process", true);
        _exit(HBRC_EXIT_CODE_UTSERR);
    }



}