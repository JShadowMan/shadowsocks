#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>

/* shadowsocks headers */
#include "shadowsocks/ss_daemon.h"
#include "shadowsocks/ss_logger.h"
#include "shadowsocks/ss_utils.h"

// linux only headers
#ifdef __linux__
#   include <unistd.h>
#   include <dirent.h>
#   include <libgen.h>
#   include <sys/stat.h>
#endif

// on linux methods
#ifdef __linux__
static void create_pid_file(const int pid);
#endif


/* check environment and startup daemon */
Ss_Daemon::Ss_Daemon(Ss_Config &config): _config(config) {
// in linux, using double-fork startup daemon
#ifdef __linux__
    auto pid = fork();  // fork #1
    if (pid > 0) {
        std::cout << "Parent PID: " << getpid() << " exit" << std::endl;
        std::exit(0);  // parent exit
    }

    chdir("/");
    setsid();
    umask(0);

    pid = fork();  // fork #2
    if (pid > 0) {
        Ss_Logger::debug("asd");
        std::cout << "Parent PID: " << getpid() << " exit" << std::endl;
        std::exit(0);  // parent exit
    }

    std::cout << "PID: " << getpid() << std::endl;

    char *dir_name = Ss_Utils::dirname(Ss_Core::pid_file);
    std::cout << dir_name << std::endl;
    // create pid file
    // create_pid_file(getpid());

    delete[] dir_name;  // don't forget free memory

    std::cout << "stdin: " << fileno(stdin) << std::endl;
    std::cout << "stdout: " << fileno(stdout) << std::endl;
    std::cout << "stderr: " << fileno(stderr) << std::endl;

    sleep(20);
#endif


// only services startup daemon, just warning
#ifdef __windows__
    Ss_Logger::debug("windows not support daemon service");
#endif
}

/* methods definitions */
#ifdef __linux__

/* create pid file */
static void create_pid_file(const int pid) {
//    char *pid_file = nullptr;
//    auto size_of_string = std::strlen(Ss_Core::pid_file) * sizeof(char);
//    if ((pid_file = (char *)malloc(size_of_string)) == nullptr) {
//        std::cout << "malloc error" << std::endl;
//    }
//    std::memncpy(pid_file, Ss_Core::pid_file, size_of_string);
//    std::cout << dirname(pid_file) << std::endl;
//
//    free(pid_file);
//    pid_file = nullptr;
//
//    auto pid_stream = new std::ofstream(Ss_Core::pid_file, std::ofstream::out);
//    *pid_stream << pid;
//    pid_stream->close();
}

#endif
