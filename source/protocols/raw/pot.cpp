#include <cstring>

#include "protocols/raw/pot.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { pot_t::pot_t() noexcept
      { //#:- Initialize
        data_m = nullptr;
        size_m = 0; }

      pot_t::pot_t(const uint8_t* _data_m, uint32_t _size_a) throw(exception_t)
            :pot_t()
      { //#:- Check parameters
        if (!_data_m) ArgumentError("NH::Protocols::Raw", "Null pointer");
        if (!_size_a) ArgumentError("NH::Protocols::Raw", "Invalid size");
        //#:- Copy a memory block
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memcpy(data_m, _data_m, size_m); }

      pot_t::pot_t(uint32_t _size_a) throw(exception_t)
            :pot_t()
      { //#:- Check parameter
        if (!_size_a) ArgumentError("NH::Protocols::Raw", "Invalid size");
        //#:- Fill a memory block
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memset(data_m, '\0', size_m); }

      pot_t::pot_t(const pot_t& _pot_a) noexcept
      { //#:- Copy object
        if (_pot_a.data_m)
        { //#:- Copy a memory block
          size_m = _pot_a.size_m;
          data_m = new uint8_t [size_m];
          std::memcpy(data_m, _pot_a.data_m, size_m); }
        else
        { //#:- Initialize
          size_m = 0;
          data_m = nullptr; } }

      pot_t::pot_t(pot_t&& _pot_a) noexcept
      { //#:- Move object
        data_m = _pot_a.data_m;
        size_m = _pot_a.size_m;
        _pot_a.data_m = nullptr;
        _pot_a.size_m = 0; }

      pot_t::~pot_t()
      { //#:- Free a memory block
        if (data_m) { delete [] data_m; data_m = nullptr; }
        size_m = 0; }

      const pot_t& pot_t::operator=(const pot_t& _pot_a) noexcept
      { //#:- Check if duplicate
        if (&_pot_a == this) return (*this);
        //#:- Clear `this` object
        if (data_m) delete [] data_m;
        //#:- Copy object
        if (_pot_a.data_m)
        { //#:- Copy a memory block
          size_m = _pot_a.size_m;
          data_m = new uint8_t [size_m];
          std::memcpy(data_m, _pot_a.data_m, size_m); }
        else
        { //#:- Initialize
          size_m = 0;
          data_m = nullptr; }
        return (*this); }

      const pot_t& pot_t::operator=(pot_t&& _pot_a) noexcept
      { //#:- Check if duplicate
        if (&_pot_a == this) return (*this);
        //#:- Clear `this` object
        if (data_m) delete [] data_m;
        //#:- Move object
        data_m = _pot_a.data_m;
        size_m = _pot_a.size_m;
        _pot_a.data_m = nullptr;
        _pot_a.size_m = 0;
        return (*this); }

      uint32_t pot_t::set(const uint8_t* _data_a, uint32_t _size_a) throw(exception_t)
      { //#:- Check parameters
        if (!_data_a) ArgumentError("NH::Protocols::Raw", "Null pointer");
        if (!_size_a) ArgumentError("NH::Protocols::Raw", "Invalid size");
        //#:- Remove old content
        if (data_m) delete [] data_m;
        //#:- Copy a memory block
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memcpy(data_m, _data_a, size_m);
        return size_m; }

      uint32_t pot_t::set(uint32_t _size_a) throw(exception_t)
      { //#:- Check parameter
        if (!_size_a) ArgumentError("NH::Protocols::Raw", "Invalid size");
        //#:- Remove old content
        if (data_m) delete [] data_m;
        //#:- Create a memory block
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memset(data_m, '\0', size_m);
        return size_m; }

      const uint8_t* pot_t::data() const noexcept
      { return data_m; }

      uint32_t pot_t::size() const noexcept
      { return size_m; }



    }

  }

}
