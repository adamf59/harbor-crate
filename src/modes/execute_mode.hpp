#ifndef EXECUTE_MODE_H
#define EXECUTE_MODE_H

    #include "../hbr_crate.hpp"
    #include "mode.hpp"
    #include <string>
    #include <vector>

    class Execute_Mode: public Mode {

            public:
                int process(std::vector<std::string> args);

                std::string * get_dock_path() const {
                    return _dock_path;   
                };

                crate_id_t * get_crate_id() const {
                    return _crate_id;
                }

                std::string get_executable() const {
                    return _executable;
                }

                bool get_detach() const {
                    return _detach;
                }

            private:
                std::string * _dock_path;
                crate_id_t * _crate_id;
                std::string _executable;
                bool _detach;

    };

#endif