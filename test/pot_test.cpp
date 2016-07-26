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
  BOOST_CHECK(compare_blocks(data, pot.data(),
              sizeof("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB")));
  BOOST_CHECK(compare_blocks(data, pot.data(), pot.size())); }

//#:- set Function
BOOST_AUTO_TEST_CASE(PotTest003)
{ //#:- Construct basic object.
  auto data = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB");
  auto pot = pot_t();
  //#:- Set object.
  pot.set(data, sizeof("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB"));
  //#:- Compare
  BOOST_CHECK(compare_blocks(data, pot.data(),
              sizeof("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB")));
  //#:- Fill a pot with 1337 long byte stream.
  pot.set(1337);
  //#:- Generate block with 1337 '\x00' bytes.
  data = generate_block(1337, '\0');
  //#:- Compare
  BOOST_CHECK(compare_blocks(data, pot.data(), 1337));
  //#:- Check if creation of 0-length pot will fail.
  BOOST_CHECK_THROW(pot.set(0), NH::exception_t); }
