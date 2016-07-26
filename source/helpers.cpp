#include "helpers.hxx"

namespace NH
{ namespace Helpers
  {
    #ifdef NH_TEST
     bool compare_memory(const uint8_t* _destination_a, const uint8_t* _source_a,
                         uint32_t _size_a) throw (exception_t)
     { //#:- Check parameters.
       if (!_destination_a ||
           !_source_a) throw (exception_t("NH::Helpers", "Null pointer"));
       if (!_size_a) throw (exception_t("NH::Helpers", "Invalid size"));
       //#:- Compare 2 sources.
       for (uint32_t index = 0; index != _size_a; ++index)
       { if (_destination_a[index] != _source_a[index]) return false; }
       return true; }
    #endif

  }

}
