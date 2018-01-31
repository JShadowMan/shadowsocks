#include <iostream>
#include <cstdlib>
#include <cstring>
#include "shadowsocks/ss_core.h"


/**
 * check version of shadowsocks-server/client
 */
void Ss_Core::check_version() {
    if (std::strcmp(module_version, ERROR_UNKNOWN_MODULE_VERSION) == 0) {
        /**
         * \todo logger
         */
        std::exit(EXIT_SHADOWSOCKS_MODULE_INVALID);
    }
}

/* trigger error handler and logging */
void Ss_Core::trigger_error(int error_code, std::string &error) {
    std::cerr << error << std::endl;
    std::exit(error_code);
}

/* overload of Ss_Core::trigger_error */
inline void Ss_Core::trigger_error(int error_code, const char *error) {
    std::string error_message(error);
    trigger_error(error_code, error_message);
}

/* format a string */
std::string *Ss_Core::format(const char *format,
                             std::initializer_list<const char *> args) {
    auto result = new std::string(module_name);
    auto args_iterator = args.begin();

    *result += ": ";
    for (size_t i = 0; i < strlen(format); ++i) {
        if (format[i] == '\\' && format[i + 1] == FORMAT_PLACEHOLDER_FLAG) {
            *result += FORMAT_PLACEHOLDER_FLAG;
            i += 1;  // skip format[i + 1]
        } else if (format[i] == FORMAT_PLACEHOLDER_FLAG) {
            /* replace placeholder string */
            if (args_iterator == args.end()) {
                auto err = Ss_Core::format(ERROR_FORMAT_NOT_MATCHED, {format});
                trigger_error(EXIT_FORMAT_NOT_MATCHED, *err);
            }
            *result += *(args_iterator++);
        } else {
            *result += format[i];
        }
    }

    return result;
}
