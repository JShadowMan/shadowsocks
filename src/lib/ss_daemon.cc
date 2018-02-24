#include <iostream>
#include <cstring>
#include <fstream>

/* shadowsocks headers */
#include "shadowsocks/ss_core.h"
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
/* in linux, using double-fork startup daemon */
#ifdef __linux__
    auto pid = fork();  // fork #1
    if (pid > 0) {
        Ss_Logger::debug("fork #1 parent exit, pid = ?", getpid());
        std::exit(0);  // parent exit
    }

    chdir("/");
    setsid();
    umask(0);

    pid = fork();  // fork #2
    if (pid > 0) {
        Ss_Logger::debug("fork #2 parent exit, pid = ?", getpid());
        std::exit(0);  // parent exit
    }

    Ss_Logger::info("daemon has startup, pid = ?", getpid());

    /* check directory exists, and create it */
    char *dir_name = Ss_Utils::dirname(Ss_Core::pid_file);
    if (!Ss_Utils::dir_exists(dir_name)) {
        Ss_Logger::debug("directory(?) not exists", dir_name);
        if (Ss_Utils::create_dir(dir_name)) {
            Ss_Logger::debug("create directory(?) success", dir_name);
        }
    }
    /* create pid file */
    create_pid_file(getpid());

    /* don't forget free memory */
    delete[] dir_name;

    std::cout << "stdin: " << fileno(stdin) << std::endl;
    std::cout << "stdout: " << fileno(stdout) << std::endl;
    std::cout << "stderr: " << fileno(stderr) << std::endl;
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
    char *pid_file = new char[std::strlen(Ss_Core::pid_file) + 1];
    memcpy(pid_file, Ss_Core::pid_file, std::strlen(Ss_Core::pid_file) + 1);

    auto pid_stream = new std::ofstream(pid_file, std::ofstream::out);
    *pid_stream << pid;

    /* close stream and free memory */
    pid_stream->close();
    delete[] pid_file;
}

#endif
