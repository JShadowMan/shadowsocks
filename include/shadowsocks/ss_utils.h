#ifndef __SHADOWSOCKS_UTILS_INCLUDED__
#define __SHADOWSOCKS_UTILS_INCLUDED__


/* other standard headers */
#include <string>
#include <algorithm>
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

        static char *dirname(const std::string &path);
};


/* check value is in the list *MUST IN HEADER* */
template <typename T>
bool Ss_Utils::contains(T value, std::initializer_list<T> list) {
    return std::find(list.begin(), list.end(), value) != list.end();
}


#endif  // __SHADOWSOCKS_UTILS_INCLUDED__