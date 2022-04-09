#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

    namespace PrettyPrint {

        /**
         * @brief Print an error message
         * 
         * @param message message to print
         */
        void log_error(const char* message, bool fatal);

        /**
         * @brief Print a message with no special formatting
         * 
         * @param message message to print
         */
        void log(const char* message);

        void log_warning(const char * message, const char * ...);

    }

#endif