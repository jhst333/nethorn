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
  BOOST_CHECK(compare_blocks(data, pot.data(), 12));
  BOOST_CHECK(compare_blocks(data, pot.data(), pot.size())); }

//#:- set Function
BOOST_AUTO_TEST_CASE(PotTest003)
{ auto data = NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB");
  auto pot = pot_t();
  pot.set(data, 12);
  BOOST_CHECK(compare_blocks(data, pot.data(), 12));
  pot.set(1337);
  data = generate_block(1337, '\0');
  BOOST_CHECK(compare_blocks(data, pot.data(), 1337));
  BOOST_CHECK_THROW(pot.set(0), NH::exception_t); }

//#:- extend Function family
BOOST_AUTO_TEST_CASE(PotTest004)
{ auto pot = pot_t(NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB"), 12);
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

  pot.extend_at(NH_RAW("\xFF\xFF"), 2, 2);
  auto pattern5 = NH_RAW("\x00\x00\xFF\xFF\x00\x00\x00\x00");
  BOOST_CHECK(compare_blocks(pattern5, pot.data(), pot.size()));

  pot.extend_at(NH_RAW("\xFF"), 1, pot.size());
  auto pattern6 = NH_RAW("\x00\x00\xFF\xFF\x00\x00\x00\x00\xFF");
  BOOST_CHECK(compare_blocks(pattern6, pot.data(), pot.size()));

  BOOST_CHECK_THROW(pot.extend_by(0), NH::exception_t);
  BOOST_CHECK_THROW(pot.extend_at(NH_RAW("\xFF"), 1, pot.size() + 1),
                    NH::exception_t);
  pot.clear();
  BOOST_CHECK_THROW(pot.extend_at(NH_RAW("\xFF"), 1, pot.size() + 1),
                    NH::exception_t);
  pot.extend_at(NH_RAW("\xFF"), 1, pot.size());
  auto pattern7 = NH_RAW("\xFF");
  BOOST_CHECK(compare_blocks(pattern7, pot.data(), pot.size()));
  BOOST_CHECK_THROW(pot.extend_at(NH_RAW("\xFF"), 0xFFFFFFFF, pot.size()),
                    NH::exception_t); }

//#:- shrink Function family
BOOST_AUTO_TEST_CASE(PotTest005)
{ auto pot = pot_t(NH_RAW("\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xAA\xBB"), 12);
  pot.shrink_by(5);
  BOOST_CHECK(pot.size() == 7);
  BOOST_CHECK_THROW(pot.shrink_by(0), NH::exception_t);
  BOOST_CHECK_THROW(pot.shrink_by(777), NH::exception_t);
  BOOST_CHECK_THROW(pot.shrink_by(8), NH::exception_t);
  BOOST_CHECK_THROW(pot.shrink_by(7), NH::exception_t);
  pot.extend_by(7);
  BOOST_CHECK_THROW(pot.shrink_to(0), NH::exception_t); }
