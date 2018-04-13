#include <iostream>
#include <cstring>
#include <fstream>

/* shadowsocks headers */
#include "shadowsocks/ss_core.h"
#include "shadowsocks/ss_logger.h"
#include "shadowsocks/ss_utils.h"

/* linux only headers */
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>

/* cross-platform methods */
static void create_pid_file(const int pid);
static std::string *get_pid_from_file(const char *pid_file);
static void startup_daemon();


/* check environment and startup daemon */
Ss_Daemon::Ss_Daemon(Ss_Config &config): _config(config) {
    if (!Ss_Utils::file_exists(Ss_Core::pid_file)) {
        startup_daemon();

        /* check directory exists, and create it */
        char *dir_name = Ss_Utils::dirname(Ss_Core::pid_file);
        if (!Ss_Utils::dir_exists(dir_name)) {
            auto dir = std::string(dir_name);

            Ss_Logger::debug("directory(\"?\") not exists", dir);
            if (Ss_Utils::create_dir(dir_name)) {
                Ss_Logger::debug("create directory(\"?\") success", dir);
            }
        }
        /* create pid file */
        create_pid_file(getpid());

        /* don't forget free memory */
        delete[] dir_name;
    } else {
        auto pid = get_pid_from_file(Ss_Core::pid_file);
        Ss_Logger::info("detect daemon running, pid = ?", *pid);
    }

//    std::cout << "stdin: " << fileno(stdin) << std::endl;
//    std::cout << "stdout: " << fileno(stdout) << std::endl;
//    std::cout << "stderr: " << fileno(stderr) << std::endl;
}

/* create pid file */
static void create_pid_file(const int pid) {
    auto pid_file = new char[std::strlen(Ss_Core::pid_file) + 1];
    memcpy(pid_file, Ss_Core::pid_file, std::strlen(Ss_Core::pid_file) + 1);

    auto pid_stream = new std::ofstream(pid_file, std::ofstream::out);
    *pid_stream << pid;

    /* close stream and free memory */
    pid_stream->close();
    Ss_Logger::debug("pid file created, path = ?", std::string(pid_file));

    delete[] pid_file;
}

/* get pid from pid_file */
static std::string *get_pid_from_file(const char *pid_file) {
    auto pid = new std::string();

    auto pid_stream = new std::ifstream(pid_file, std::ifstream::in);
    if (pid_stream->good()) {
        *pid_stream >> *pid;
        pid_stream->close();
    }

    return pid;
}

/* startup daemon */
static void startup_daemon() {
    /* in linux, using double-fork startup daemon */
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
}
