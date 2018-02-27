#ifndef __SHADOWSOCKS_UTILS_INCLUDED__
#define __SHADOWSOCKS_UTILS_INCLUDED__


/* other standard headers */
#include <string>
#include <algorithm>
#include <initializer_list>


/* Class Ss_Utils */
class Ss_Utils {
    public:
        template <typename T>
        static bool contains(T value, std::initializer_list<T> list);

    public:
        static char *dirname(const std::string &path);
        static bool dir_exists(const std::string &path);
        static bool file_exists(const std::string &path);
        static bool create_dir(const std::string &path);
        static std::string *current_time(const char *format);
};


/* check value is in the list *MUST IN HEADER* */
template <typename T>
bool Ss_Utils::contains(T value, std::initializer_list<T> list) {
    return std::find(list.begin(), list.end(), value) != list.end();
}


#endif  // __SHADOWSOCKS_UTILS_INCLUDED__