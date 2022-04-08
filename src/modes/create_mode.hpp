#ifndef CREATE_MODE_H
#define CREATE_MODE_H

    #include "mode.hpp"
    #include <string>
    #include <vector>

    class Create_Mode : public Mode {

        public:
            int process(std::vector<std::string> args);
        private:
            /**
             * @brief crate containerized OS flavor
             * 
             */
            std::string _flavor;
            /**
             * @brief user-given name of this crate
             * 
             */
            std::string _cratename;
            /**
             * @brief host to crate file system mounts
             * 
             */
            std::vector<std::string> _fsmounts;
            /**
             * @brief crate hostname
             * 
             */
            std::string _hostname;
            /**
             * @brief crate network mode
             * 
             */
            std::string _network_mode;

    };

#endif