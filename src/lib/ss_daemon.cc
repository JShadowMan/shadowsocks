#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <sys/stat.h>
#include "shadowsocks/ss_daemon.h"


/* enter daemon mode */
void Ss_Daemon::run_forever() {
    auto pid = fork();  // fork #1
    if (pid > 0) {  // parent exit
        std::exit(0);
    }

    chdir("/");
    setsid();
    umask(0);

    pid = fork();  // fork #2
    if (pid > 0) {
        std::exit(0);  // parent exit
    }

    std::fflush(stdout);
    std::fflush(stderr);

    auto _stdin = fopen("/stdin.log", "r");
    auto _stdout = fopen("/stdout.log", "w");
    auto _stderr = fopen("/stderr.log", "w");

    dup2(fileno(_stdin), fileno(stdin));
    dup2(fileno(_stdout), fileno(stdout));
    dup2(fileno(_stderr), fileno(stderr));
}
