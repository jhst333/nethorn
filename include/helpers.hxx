#ifndef _NH_HELPERS_HXX_
#define _NH_HELPERS_HXX_

#include <cstdint>

#include "exception.hxx"

#define NH_RAW reinterpret_cast<const uint8_t*>

namespace NH
{ namespace Helpers
  {
    #ifdef NH_TEST
     /*! \brief Compares 2 memory segments.
      *
      * Compares \p _destination_a with \p _source_a, using \p _size_a size.
      * If 2 segments have equal content, function returns true, false otherwise */
     bool compare_memory(const uint8_t* _destination_a, const uint8_t* _source_a,
                         uint32_t _size_a) throw (exception_t);
    #endif
  }
}

#endif
