#//: General
 cmake_minimum_required (VERSION 2.6)
 project                (nethorn)
 set                    (nethorn_VERSION_MAJOR 1)
 set                    (nethorn_VERSION_MINOR 0)
#//: Package
 find_package(Boost COMPONENTS unit_test_framework)
#//: libnethorn.so [RELEASE]
 add_library                (nethorn source/protocols/raw/pot.cpp
                                     source/protocols/raw/eth.cpp
                                     source/helpers.cpp)
 target_include_directories (nethorn PUBLIC include/)
 target_compile_options     (nethorn PUBLIC -Wall -Wextra -pedantic -std=c++11
                                            -fPIC -Ofast)
#//: pot_test [RELEASE]
if (Boost_UNIT_TEST_FRAMEWORK_LIBRARY)
 #//: libnethorn.so [DEBUG]
 add_library                (nethorn_debug source/protocols/raw/pot.cpp
                                           source/helpers.cpp)
 target_include_directories (nethorn_debug PUBLIC include/)
 target_compile_options     (nethorn_debug PUBLIC -Wall -Wextra -pedantic -std=c++11
                                                  -fPIC -g -O0 -DNH_TEST)
 #//: pot_test [DEBUG]
 add_executable             (_test_pot test/_test_pot.cpp source/helpers.cpp)
 target_include_directories (_test_pot PUBLIC include/)
 target_compile_options     (_test_pot PUBLIC -Wall -Wextra -pedantic -std=c++11
                                              -O0 -g -DNH_TEST)
 target_link_libraries      (_test_pot LINK_PUBLIC ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                                                   nethorn_debug)
endif()
#//: Install
 INSTALL         (FILES include/protocols/raw/pot.hxx
                        DESTINATION include/nethorn/protocols/raw/)
 INSTALL         (FILES include/exception.hxx
                        DESTINATION include/nethorn/)
 INSTALL_TARGETS (/lib nethorn)
