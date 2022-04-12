#ifndef CRATE_CTRL_H
#define CRATE_CTRL_H

    /**
     * @brief forks a process to run inside a crate. attaches the processes to the current tty
     * @return exit code
     */
    int crate_proc_run(const char * exec_path, char * const * exec_argv);

    /**
     * @brief forks a process to run inside a crate. daemonizes the process so as to run in the background
     * 
     */
    void crate_proc_run_detached(const char * exec_path, const char * argv[]);

    /**
     * @brief executes a command via exec 
     * 
     * @param exec_path 
     * @param argv 
     */
    void crate_exec(const char * exec_path, const char * argv[]);

    /**
     * @brief causes the process to join/configure namespaces/cgroups to "containerize" the process.
     * 
     */
    void proc_inherit_crate_spec();

#endif