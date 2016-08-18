#ifndef _NH_HELPERS_HXX_
#define _NH_HELPERS_HXX_

#include <cstdint>
#include <cstdio>

#include "exception.hxx"

namespace NH
{ namespace Helpers
  {
    #define NH_RAW reinterpret_cast<const uint8_t*>
    #define TO_UINT32_T reinterpret_cast<uint32_t*>
    #define TO_UINT16_T reinterpret_cast<uint16_t*>
    #define TO_UINT8_T reinterpret_cast<uint8_t*>
    #define NH_BINARY(_n) strtol(#_n, 0, 2)
    #ifdef NH_TEST
     /*! \brief Compares 2 memory segments.
      *
      * Compares \p _destination_a with \p _source_a, using \p _size_a size.
      * \returns True if 2 blocks are equal, false otherwise. */
     bool compare_blocks(const uint8_t* _destination_a, const uint8_t* _source_a,
                         uint32_t _size_a) throw (exception_t);
     /*! \brief Generates a memory block.
      *
      * Generates a memory block of \p _size_a size,
      * filled with \p _byte_a pattern.
      * \returns Pointer to memory block. */
     uint8_t* generate_block(uint32_t _size_a, uint8_t _byte_a) throw (exception_t);
    #endif

    uint16_t swap_byte_order(uint16_t _value_a) noexcept;
    uint32_t swap_byte_order(uint32_t _value_a) noexcept;
    uint64_t swap_byte_order(uint64_t _value_a) noexcept;
  }
}

#endif
