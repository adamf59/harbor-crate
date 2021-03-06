#ifndef HARBOR_CRATE_H
#define HARBOR_CRATE_H

    #include <vector>
    #include <string>

    // valid harbor-crate command modes
    #define HBRC_MODE_CREATE "create"
    #define HBRC_MODE_DELETE "delete"
    #define HBRC_MODE_EXECUTE "execute"

    // harbor-crate exit codes
    #define HBRC_EXIT_CODE_SUCCESS 0
    #define HBRC_EXIT_CODE_BADMODE 1 // invalid mode specified to a command handler
    #define HBRC_EXIT_CODE_BADARGS 2 // insufficient or invalid arguments provided to harbor_arguments handler
    #define HBRC_EXIT_CODE_EACCES  3 // permissions error occurred 
    #define HBRC_EXIT_CODE_FORKERR 4 // error when forking process to command run inside a crate
    #define HBRC_EXIT_CODE_EXECERR 5 // error when running exec inside forked process
    #define HBRC_EXIT_CODE_UTSERR 6 // error when creating a new UTS namespace inside forked process
    #define HBRC_EXIT_CODE_UNKNOWN 99 // an unknown or generic error occured, no further information.

    typedef std::string crate_id_t;

    /**
     * @brief Process harbor commands in the form of a vector of arguments 
     * 
     * @param args vector of valid harbor crate command arguments (see the documentation for syntax)
     * @returns exit code from harbor crate command processing
     */
    int handle_harbor_arguments(std::vector<std::string> args);

    
#endif