cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libvisensor
  VERSION 0.5
  RELEASE alpha
  SUMMARY "A C++-based library for interfacing the VI-sensor."
  AUTHOR "Michael Burri"
  AUTHOR "Pascal Gohl"
  AUTHOR "Thomas Schneider"
  CONTACT "pascal.gohl@mavt.ethz.ch"
  HOME "http://www.skybotix.com"
  LICENSE "Apache License, Version 2.0 (ALv2)"
  README README.md
  PREFIX visensor-
  INSTALL /usr
  HEADER_DESTINATION include/visensor
  EXTRA_CXX_FLAGS -std=c++0x
)

remake_doc(
  html
)

remake_pack_deb(
  DEPENDS libboost-system[0-9.]* libboost-thread[0-9.]*
)
remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "development headers"
  DEPENDS libvisensor libboost-all-dev
)
remake_pack_deb(
  ARCH all
  COMPONENT doc
  DESCRIPTION "documentation"
)

remake_distribute_deb(
  DISTRIBUTION lucid
  SECTION libs
  UPLOAD ppa:kralf/asl
  DEPENDS remake doxygen pkg-config libeigen3-dev libboost-all-dev
  PASS CMAKE_BUILD_TYPE LIBVISENSOR_GIT_REVISION
)
remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:kralf/asl
  DEPENDS remake doxygen pkg-config libeigen3-dev libboost-all-dev
  PASS CMAKE_BUILD_TYPE LIBVISENSOR_GIT_REVISION
)
remake_distribute_deb(
  DISTRIBUTION trusty
  SECTION libs
  UPLOAD ppa:kralf/asl
  DEPENDS remake doxygen pkg-config libeigen3-dev libboost-all-dev
  PASS CMAKE_BUILD_TYPE LIBVISENSOR_GIT_REVISION
)
