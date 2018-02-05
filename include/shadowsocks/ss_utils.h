#ifndef __SHADOWSOCKS_UTILS_INCLUDED__
#define __SHADOWSOCKS_UTILS_INCLUDED__

/* other standard headers */
#include <string>
#include <initializer_list>
#include "shadowsocks/ss_core.h"


/* Class Ss_Utils */
class Ss_Utils {
    public:
        template <typename T>
        static bool contains(T value, std::initializer_list<T> list);

    public:
        static std::string *format(const char *format,
                                   std::initializer_list<const char *> args);
        static std::string *format(const char *format);
};


/* check value is in the list *MUST IN HEADER* */
template <typename T>
bool Ss_Utils::contains(T value, std::initializer_list<T> list) {
    for (auto item : list) {
        if (value == item) {
            return true;
        }
    }
    return false;
}


#endif  // __SHADOWSOCKS_UTILS_INCLUDED__