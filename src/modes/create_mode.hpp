#ifndef CREATE_MODE_H
#define CREATE_MODE_H

    #include "mode.hpp"
    #include <string>
    #include <vector>

    class Create_Mode : public Mode {

        public:
            int process(std::vector<std::string> args);

    };

#endif