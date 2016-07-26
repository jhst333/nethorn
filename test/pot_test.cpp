#include "protocols/raw/pot.hxx"
#include "helpers.hxx"

#define BOOST_TEST_DYN_LINK 1
#define BOOST_TEST_MODULE pot_test
#include <boost/test/unit_test.hpp>

using namespace NH::Helpers;
using namespace NH::Protocols::Raw;

//#:- Default constructor exception.
BOOST_AUTO_TEST_CASE(PotTest001)
{ BOOST_CHECK_THROW(pot_t(nullptr, 5), NH::exception_t);
  BOOST_CHECK_THROW(pot_t(NH_RAW("123"), 0), NH::exception_t); }

//#:- Default constructor working.
BOOST_AUTO_TEST_CASE(PotTest002)
{ auto data = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB");
  auto pot = pot_t(data, 12);
  BOOST_CHECK(compare_memory(data, pot.data(), 12));
  BOOST_CHECK(compare_memory(data, pot.data(), pot.size())); }
