#include "helpers.hxx"

namespace NH
{ namespace Helpers
  {
    #ifdef NH_TEST
     bool compare_blocks(const uint8_t* _destination_a, const uint8_t* _source_a,
                         uint32_t _size_a) throw (exception_t)
     { //#:- Check parameters.
       if (!_destination_a ||
           !_source_a) throw (exception_t("NH::Helpers", "Null pointer"));
       if (!_size_a) throw (exception_t("NH::Helpers", "Invalid size"));
       //#:- Compare 2 sources.
       for (uint32_t index = 0; index != _size_a; ++index)
       { if (_destination_a[index] != _source_a[index]) return false; }
       return true; }

     uint8_t* generate_block(uint32_t _size_a, uint8_t _byte_a) throw (exception_t)
     { //#:- Check parameters.
       if (!_size_a) throw (exception_t("NH::Helpers", "Invalid size"));
       //#:- Generate and fill memory block.
       uint8_t* data = new uint8_t [_size_a];
       std::memset(data, _byte_a, _size_a);
       return data; }
    #endif

  }

}
