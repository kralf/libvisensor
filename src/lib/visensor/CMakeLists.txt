remake_project_header(visensor_version.hpp.remake INSTALL)
remake_add_library(visensor PREFIX OFF LINK helpers networking sensors
  serial_bridge synchronization ${Boost_LIBRARIES})
remake_add_headers()
