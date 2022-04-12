#include "crate_factory.hpp"
#include "pretty_print/pretty_print.hpp"
#include "hbr_crate.hpp"
#include "crate_ctrl.hpp"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>



#ifdef __x86_64 
    #define DEFAULT_FLAVOR_PULL_URL "https://dl-cdn.alpinelinux.org/alpine/v3.15/releases/x86_64/alpine-minirootfs-3.15.4-x86_64.tar.gz"
#elif __arm__
    #define DEFAULT_FLAVOR_PULL_URL "https://dl-cdn.alpinelinux.org/alpine/v3.15/releases/armv7/alpine-minirootfs-3.15.4-armv7.tar.gz"
#endif

crate_id_t * create_crate(Create_Mode * cm_spec) {

    // check that the target dock exists (or create it)
    if (validate_dock(cm_spec->get_dock()) == NULL) {

        // create a new dock
        create_dock(cm_spec->get_dock());
    } else {
        PrettyPrint::log("using existing dock");
    }
    
    // change directory to the dock
    enter_dock(cm_spec->get_dock());

    // assign a unique crate id
    std::string * crate_id = generate_crate_id();

    // create and enter the crate directory
    if (mkdir(crate_id->c_str(), 220) == -1 || chdir(crate_id->c_str()) == -1) {
        PrettyPrint::log_error("creating or entering crate directory: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // create and pull the crate file system
    pull_container_fs(NULL);
    
    PrettyPrint::log("successfully built %s", crate_id->c_str());

    // return the crate ID
    return crate_id;
}

void create_dock(std::string * path) {

    // absolute path to the directory to create a dock in
    std::string init_dock_path = expand_dock_to_realpath(path);

    // print dock creation location
    PrettyPrint::log("creating dock: %s%s", init_dock_path.c_str());

    // call mkdir to create the directory
    if (mkdir(init_dock_path.c_str(), 220) == -1) {
        
        PrettyPrint::log_error("when creating dock: %s", true, strerror(errno));
        
        exit(HBRC_EXIT_CODE_EACCES);
    }

}

int crate_execute(Execute_Mode * em_spec) {

    std::string crate_id = *em_spec->get_crate_id();

    // change directory to the dock
    enter_dock(em_spec->get_dock_path());
    // change directory to the crate
    enter_crate(crate_id);

    // get the executable
    const char * executable = em_spec->get_executable().c_str();
    // TODO: handle arguments passed to crate execute executable, i.e. "harbor-crate execute crate_id "ls -la""
    char* exec_argv[] = {(char*) executable, NULL};

    // print to user
    PrettyPrint::log("attaching process '%s' to %s", executable, crate_id.c_str());

    // run command inside containerized environment
    crate_proc_run(executable, exec_argv);

    return 0; // temporary
}

void enter_crate(crate_id_t crate_id) {

    // ensure the crate exists
    if (access(crate_id.c_str(), F_OK) == -1) {
        // unable to access crate, so error out
        PrettyPrint::log_error("crate does not exist or insufficient permissions to access", true);
        perror("access");
        exit(HBRC_EXIT_CODE_UNKNOWN);
    }

    // crate exists, so change directory into it
    if (chdir(crate_id.c_str()) == -1) {
        PrettyPrint::log_error("when changing directory into crate: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);
    }

}

void enter_dock(std::string * dock_path) {

    std::string * dock_res = validate_dock(dock_path);

    // validate the dock is set up and exists
    if (dock_res != NULL) {

        // change directory into the dock
        if (chdir(dock_res->c_str()) == -1) {

            PrettyPrint::log_error("entering dock path: %s", true, strerror(errno));
            exit(HBRC_EXIT_CODE_UNKNOWN);

        }
        
        // successfully changed directory into dock
        return;

    } else {

        PrettyPrint::log_error("validating dock path: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);

    }

} 

std::string * validate_dock(std::string * path) {

    // expand to a realpath
    std::string rpath = expand_dock_to_realpath(path);

    // ensure the path exists and is accessable
    if (access(rpath.c_str(), F_OK) == -1) {
        return NULL;
    }

    return new std::string(rpath);;
}

std::string expand_dock_to_realpath(std::string * path) {

    std::string rpath;
    
    // if path is null, use $USER_HOME/
    if (path == NULL) {

        // get the user passwd entry, containing their home dir
        struct passwd * upw_entry = getpwuid(getuid());
        // convert to std::string
        std::string user_home_path (upw_entry->pw_dir);
        
        rpath = user_home_path.append("/.harbor/");

    } else {

        // expand path using realpath

    }

    return rpath;

}

std::string * generate_crate_id() {

    // create char array for holding random values
    char id[10] = {0};
    // set the randomness seed to time. security is not an issue here becuase we really just need a mostly unique value
    srand (time(NULL));
    // insert the random hex values in to the char array
    for (int i = 0; i < 9; i++) {
        sprintf(&id[i], "%x", rand() % 16);
    }

    return new std::string(id);
}


void pull_container_fs(const char * url) {
    
    // create file system (fs) directory
    if (mkdir("fs", 220) == -1 || chdir("fs") == -1) {
        // give error and exit
        
        PrettyPrint::log_error("creating or entering crate fs directory: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);

    }

    std::string pull_url;

    if (url == NULL) {
        // use default flavor defined at compile time
        pull_url = std::string (DEFAULT_FLAVOR_PULL_URL);
    } else {
        pull_url = url;
    }

    // setup call to wget, save tar as `pack`
    std::string sys_wget_command("wget --output-document=pack ");
    sys_wget_command.append(pull_url);

    // perform wget
    system(sys_wget_command.c_str());

    // ... unpack tar into fs directory
    system("tar -xzf pack");

    // remove pack
    system("rm pack");

    // move back out of the file system directory
    if (chdir("../") == -1) {

        PrettyPrint::log_error("leaving fs directory: %s", true, strerror(errno));
        exit(HBRC_EXIT_CODE_UNKNOWN);

    }

}