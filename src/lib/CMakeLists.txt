remake_find_package(eigen3 CONFIG)
remake_find_package(Boost COMPONENTS thread system
  RESULT_VAR Boost_FOUND)

remake_include()
remake_include(visensor ${CMAKE_CURRENT_BINARY_DIR})
remake_include(${EIGEN3_INCLUDE_DIRS})
remake_include(${Boost_INCLUDE_DIR})

remake_add_directories(EXCLUDE work)

remake_pkg_config_generate(EXTRA_CFLAGS -std=c++0x)
