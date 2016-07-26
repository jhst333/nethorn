#//: General
 cmake_minimum_required (VERSION 2.6)
 project                (nethorn)
 set                    (nethorn_VERSION_MAJOR 1)
 set                    (nethorn_VERSION_MINOR 0)

#//: Package
 find_package(Boost COMPONENTS unit_test_framework)

#//: libnethorn.so [RELEASE]
 add_library                (nethorn source/protocols/raw/pot.cpp
                                     source/helpers.cpp)
 target_include_directories (nethorn PUBLIC include/)
 target_compile_options     (nethorn PUBLIC -Wall -Wextra -std=c++11 -fPIC -Ofast)

#//: pot_test [RELEASE]
if (Boost_UNIT_TEST_FRAMEWORK_LIBRARY)
 add_executable             (pot_test test/pot_test.cpp source/helpers.cpp)
 target_include_directories (pot_test PUBLIC include/)
 target_compile_options     (pot_test PUBLIC -Wall -Wextra -std=c++11 -Ofast -DNH_TEST)
 target_link_libraries      (pot_test LINK_PUBLIC ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} nethorn)
endif()

INSTALL         (FILES include/protocols/raw/pot.hxx
                       DESTINATION include/nethorn/protocols/raw/)
INSTALL         (FILES include/exception.hxx
                       DESTINATION include/nethorn/)
INSTALL_TARGETS (/lib nethorn)
