#include <iostream>
#include <vector>
#include "shadowsocks/ss_core.h"

/* static methods */
static inline bool check_daemon_value(const std::string &value);

/* check daemon is correct */
static inline bool check_daemon_value(const std::string &value) {
    return Ss_Utils::contains<std::string>(value, {"start", "stop", "restart"});
}
