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
{ //#:- Construct basic object.
  auto data = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB");
  auto pot = pot_t(data, 12);
  //#:-Compare raw input with generated one.
  BOOST_CHECK(compare_blocks(data, pot.data(), 12));
  BOOST_CHECK(compare_blocks(data, pot.data(), pot.size())); }

//#:- set Function
BOOST_AUTO_TEST_CASE(PotTest003)
{ //#:- Construct basic object.
  auto data = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB");
  auto pot = pot_t();
  //#:- Set object.
  pot.set(data, 12);
  //#:- Compare
  BOOST_CHECK(compare_blocks(data, pot.data(), 12));
  //#:- Fill a pot with 1337 long byte stream.
  pot.set(1337);
  //#:- Generate block with 1337 '\x00' bytes.
  data = generate_block(1337, '\0');
  //#:- Compare
  BOOST_CHECK(compare_blocks(data, pot.data(), 1337));
  //#:- Check if creation of 0-length pot will fail.
  BOOST_CHECK_THROW(pot.set(0), NH::exception_t); }

//#:- extend Function family
BOOST_AUTO_TEST_CASE(PotTest004)
{ //#:- Construct basic object.
  auto pot = pot_t(NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB"), 12);
  //#:- Extend it by one byte.
  pot.extend_by(NH_RAW("\x11"), 1);
  auto pattern1 = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB\x11");
  BOOST_CHECK(compare_blocks(pattern1, pot.data(), 13));
  pot.clear();
  pot.extend_by(NH_RAW("\x00\x00"), 2);
  auto pattern2 = NH_RAW("\x00\x00");
  BOOST_CHECK(compare_blocks(pattern2, pot.data(), pot.size()));
  pot.extend_by(NH_RAW("\x00\x00"), 2);
  auto pattern3 = NH_RAW("\x00\x00\x00\x00");
  BOOST_CHECK(compare_blocks(pattern3, pot.data(), pot.size()));
  pot.extend_by(2);
  auto pattern4 = NH_RAW("\x00\x00\x00\x00\x00\x00");
  BOOST_CHECK(compare_blocks(pattern4, pot.data(), pot.size()));
  BOOST_CHECK_THROW(pot.extend_by(0), NH::exception_t);


}
