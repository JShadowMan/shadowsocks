#include <cstring>
#include "shadowsocks/ss_utils.h"


/* format a string */
std::string *Ss_Utils::format(const char *format,
                             std::initializer_list<const char *> args) {
    auto result = new std::string(Ss_Core::module_name);
    auto args_iterator = args.begin();

    *result += ": ";
    for (size_t i = 0; i < strlen(format); ++i) {
        if (format[i] == '\\' && format[i + 1] == FORMAT_PLACEHOLDER_FLAG) {
            *result += FORMAT_PLACEHOLDER_FLAG;
            i += 1;  // skip format[i + 1]
        } else if (format[i] == FORMAT_PLACEHOLDER_FLAG) {
            /* replace placeholder string */
            if (args_iterator == args.end()) {
                auto err = Ss_Utils::format(ERROR_FORMAT_NOT_MATCHED, {format});
                Ss_Core::trigger_error(EXIT_FORMAT_NOT_MATCHED, *err);
            }
            *result += *(args_iterator++);
        } else {
            *result += format[i];
        }
    }

    return result;
}

/* simple version overload */
std::string* Ss_Utils::format(const char *format) {
    auto result = new std::string(Ss_Core::module_name);
    *result = *result + ": " + format;
    return result;
}