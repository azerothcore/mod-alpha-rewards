AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod-alpha-rewards.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod-alpha-rewards.h")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod-alpha-rewards-player.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/mod-alpha-rewards-creature.cpp")
AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/cs_alpha-rewards.cpp")
AC_ADD_SCRIPT_LOADER("AlphaReward" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")


AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/AlphaRewards.conf.dist")