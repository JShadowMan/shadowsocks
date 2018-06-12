# -- platform/compiler feature check
include(CheckFunctionExists)

# -- inet
check_function_exists(inet_ntop HAVE_INET_NTOP)
check_function_exists(inet_pton HAVE_INET_PTON)

# -- daemon support
check_function_exists(fork HAVE_FORK)
