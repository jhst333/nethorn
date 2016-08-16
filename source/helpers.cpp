#include "helpers.hxx"

namespace NH
{ namespace Helpers
  {
    #ifdef NH_TEST
     bool compare_blocks(const uint8_t* _destination_a, const uint8_t* _source_a,
                         uint32_t _size_a) throw (exception_t)
     { //#:- Check parameters.
       if (!_destination_a ||
           !_source_a) throw (ArgumentError("NH::Helpers", "Null pointer"));
       if (!_size_a) throw (ArgumentError("NH::Helpers", "Invalid size"));
       //#:- Compare 2 sources.
       for (uint32_t index = 0; index != _size_a; ++index)
       { if (_destination_a[index] != _source_a[index]) return false; }
       return true; }

     uint8_t* generate_block(uint32_t _size_a, uint8_t _byte_a) throw (exception_t)
     { //#:- Check parameters.
       if (!_size_a) throw (ArgumentError("NH::Helpers", "Invalid size"));
       //#:- Generate and fill memory block.
       uint8_t* data = new uint8_t [_size_a];
       std::memset(data, _byte_a, _size_a);
       return data; }
    #endif

    uint16_t swap_byte_order(uint16_t _value_a) noexcept
    { //#:- Swap bytes order
      uint16_t swapped = 0;
      swapped |= (_value_a & 0xFF00) >> 8;
      swapped |= (_value_a & 0x00FF) << 8;
      return swapped; }

    uint32_t swap_byte_order(uint32_t _value_a) noexcept
    { //#:- Swap bytes order
      uint32_t swapped = 0;
      swapped |= (_value_a & 0xFF000000) >> 24;
      swapped |= (_value_a & 0x00FF0000) >> 8;
      swapped |= (_value_a & 0x0000FF00) << 8;
      swapped |= (_value_a & 0x000000FF) << 24;
      return swapped; }

    uint64_t swap_byte_order(uint64_t _value_a) noexcept
    { //#:- Swap bytes order
      uint64_t swapped = 0;
      swapped |= (_value_a & 0xFF00000000000000) >> 56;
      swapped |= (_value_a & 0x00FF000000000000) >> 40;
      swapped |= (_value_a & 0x0000FF0000000000) >> 24;
      swapped |= (_value_a & 0x000000FF00000000) >> 8;
      swapped |= (_value_a & 0x00000000FF000000) << 8;
      swapped |= (_value_a & 0x0000000000FF0000) << 24;
      swapped |= (_value_a & 0x000000000000FF00) << 40;
      swapped |= (_value_a & 0x00000000000000FF) << 56;
      return swapped; }
  }

}
