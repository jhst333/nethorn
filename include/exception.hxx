#ifndef _NH_EXCEPTION_HXX_
#define _NH_EXCEPTION_HXX_

#include <catch_me.hpp>
#include <cstring>

namespace NH
{ enum class exception_type_t
  { RuntimeError,
    ArgumentError };
  using exception_t = catch_me::exception_t<exception_type_t>; }

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define ArgumentError(_module_a, _reason_a) exception_t(exception_type_t::ArgumentError, "<%s::%s:[%s:%d]> %s", (_module_a), __FUNCTION__, __FILENAME__, __LINE__, (_reason_a))
#define RuntimeError(_module_a, _reason_a) exception_t(exception_type_t::ArgumentError, "<%s::%s:[%s:%d]> %s", (_module_a), __FUNCTION__, __FILENAME__, __LINE__, (_reason_a))

#endif
