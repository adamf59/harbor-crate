#include "crate_ctrl.hpp"
#include "hbr_crate.hpp"
#include "pretty_print/pretty_print.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

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

    // create a new unix time share
    if (unshare(CLONE_NEWUTS) == -1) {
        PrettyPrint::log_error("when running unshare: %s", strerror(errno));
        perror("unshare");
        _exit(HBRC_EXIT_CODE_UTSERR);
    }

    sethostname("testcontainer", 14);

}