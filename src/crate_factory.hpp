#ifndef CRATE_FACTORY_H
#define CRATE_FACTORY_H
    
    #include <string>
    #include "modes/create_mode.hpp"

    typedef std::string crate_id_t;

    /**
     * @brief create a new crate 
     * @return null pointer if failure, else pointer to string of crate's id.
     */
    crate_id_t * create_crate(Create_Mode * cm_spec);

    /**
     * @brief create a new dock at path. docks are directories which contain crate information and container file systems.
     * 
     */
    void create_dock(std::string * path);

    /**
     * @brief validates that a dock exists at a given path, and that it is a valid configuration
     * 
     * @param path 
     * @return true 
     * @return false 
     */
    std::string * validate_dock(std::string * path);

    /**
     * @brief execute a command in a crate
     * 
     * @param id id of crate
     * @param path path to executable inside crate
     * @param detached whether to run the process as a daemon or attached to this tty
     */
    void crate_execute(std::string * dock_path, crate_id_t crate_id, std::string path, bool detached);

    /**
     * @brief changes directory into the specified dock (or the default if dock_path is NULL) 
     * 
     * @param dock_path 
     */
    void enter_dock(std::string * dock_path);

    /**
     * @brief changes directory into the specified crate, should be preceded by enter_dock 
     * 
     * @param crate_id the ID of the crate in the current dock
     */
    void enter_crate(crate_id_t crate_id);

    std::string expand_dock_to_realpath(std::string * path);

    /**
     * @brief generates a random hex string (size = 10, len = 9)
     * 
     * @return std::string* 
     */
    std::string * generate_crate_id();

    void pull_container_fs(const char * url);

#endif