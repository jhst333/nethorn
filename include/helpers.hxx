#ifndef _NH_HELPERS_HXX_
#define _NH_HELPERS_HXX_

#include <cstdint>
#include <cstdio>
#include <string>
#include <arpa/inet.h>

#include "exception.hxx"

namespace NH
{ namespace Helpers
  {
    #define NH_RAW reinterpret_cast<const uint8_t*>
    #define TO_UINT32_T reinterpret_cast<uint32_t*>
    #define TO_UINT16_T reinterpret_cast<uint16_t*>
    #define TO_UINT8_T reinterpret_cast<uint8_t*>
    #define NH_BINARY(_n) strtol(#_n, 0, 2)

    template <typename _type_t>
    _type_t* init_memory(uint32_t _bytes_a) throw (exception_t)
    { if (!_bytes_a) throw (ArgumentError("NH::Helpers", "Invalid size"));
      _type_t* block = new _type_t [_bytes_a];
      std::memset(&block, '\0', _bytes_a);
      return block; }

    inline uint16_t swap_byte_order(uint16_t _value_a) noexcept;
    inline uint32_t swap_byte_order(uint32_t _value_a) noexcept;
    inline uint64_t swap_byte_order(uint64_t _value_a) noexcept;
    std::string ip_to_string(const sockaddr* _sockaddr_a) throw (exception_t);

    /*! \brief Counts characters in a string with safe manner.
     *
     * Counts characters in a \p _string_a string excluding non-alphanumeric and
     * non-punctual characters.
     * \throw \class exception_t If:
     * - A character without graphical representation in ASCII standard is found.
     * - Loop counter exceeds expected character limit.
     * \return Amount of characters. */
    uint32_t safe_string_length(const char* _string_a,
                                uint32_t _limit_a) throw (exception_t);

    //////////////////////////////////////////
    //#:- For test & debug purposes only
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
  }
}

#endif
