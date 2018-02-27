#include <cstring>
#include <ctime>
#include <chrono>

/* linux-only headers */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/* shadowsocks other headers */
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_utils.h"

/* Ss_Utils macro */
#define TIME_INFO_BUFFER_SIZE 128


/* get directory-name from path */
char* Ss_Utils::dirname(const std::string &path) {
    auto dir = new std::string(path);
    auto sep_index = dir->rfind('/');

    auto alloc_size = (sep_index == std::string::npos ? path.length()
                                                      : sep_index) + 1;
    auto name = new char[alloc_size];
    memcpy(name, path.c_str(), alloc_size);

    if (sep_index != std::string::npos) {
        name[sep_index] = '\0';
    }
    return name;
}

/* check directory exists */
bool Ss_Utils::dir_exists(const std::string &path) {
    DIR *dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}

/* check file exists */
bool Ss_Utils::file_exists(const std::string &path) {
    return access(path.c_str(), F_OK) != -1;
}

/* create directory */
bool Ss_Utils::create_dir(const std::string &path) {
    auto result = mkdir(path.c_str(), 0755);
    return result == 0;
}

/* return current time format by first parameter */
std::string* Ss_Utils::current_time(const char *format) {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    struct tm *time_info = std::localtime(&current_time);
    auto buffer = new char[TIME_INFO_BUFFER_SIZE];

    std::strftime(buffer, TIME_INFO_BUFFER_SIZE, format, time_info);
    auto result = new std::string(buffer);

    delete[] buffer;
    return result;
}
