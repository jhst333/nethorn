#include "helpers.hxx"

namespace NH
{ namespace Helpers
  {
    uint32_t safe_string_length(const char* _string_a,
                                uint32_t _limit_a) throw (exception_t)
    { //#:- Iterate over string if checked character is not NULL and
      //#:- it is not bigger than limit.
      uint32_t index = 0
      for (; (_string_a[index]) and index != _limit_a; ++index)
      { //#:- Check if character is present within latin language.
        if (_string_a[index] < '\x20' or
            _string_a[index] > '\x7E')
         throw (ArgumentError("NH::Helpers", "String contains illegal characters.")); }
      //#:- Did we hit character limit?
      if (index == _limit_a)
       throw (ArgumentError("NH::Helpers",
                            "String length exceeds expected character limit."));
      return index; }

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

    std::string ip_to_string(const sockaddr* _sockaddr_a) throw (exception_t)
    { //#:- Check if structure is empty.
      if (!_sockaddr_a) throw (ArgumentError("NH::Helpers", "Empty structure."));
      //#:- Allocate memory.
      std::unique_ptr<char[]> ip(Helpers::init_memory<char>(INET6_ADDRSTRLEN + 1));
      //#:- Convert IPv4/6 from binary form into text and save it into ip.
      switch (_sockaddr_a->sa_family)
      { case PF_INET:
         if (!inet_ntop(PF_INET, &(reinterpret_cast<const sockaddr_in*>(_sockaddr_a)->sin_addr),
                        ip.get(), INET6_ADDRSTRLEN))
          throw (ArgumentError("NH::Helpers", "Unable to convert IPv4 address."));
         break;
        case PF_INET6:
         if (!inet_ntop(PF_INET6, &(reinterpret_cast<const sockaddr_in6*>(_sockaddr_a)->sin6_addr),
                        ip.get(), INET6_ADDRSTRLEN))
          throw (ArgumentError("NH::Helpers", "Unable to convert IPv6 address."));
         break;
        default:
         throw (ArgumentError("NH::Helpers", "Invalid address family.")); }
      //#:- Check if buffer contains legal characters.
      //#:- In case string does contain illegal characters, throw exception.
      safe_string_length(ip.get(), INET6_ADDRSTRLEN);
      return std::string(ip.get()); }

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
  }

}
