#include <cstring>

#include "protocols/raw/pot.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { pot_t::pot_t() noexcept
      { //#:- Initialize.
        data_m = nullptr;
        size_m = 0; }

      pot_t::pot_t(const uint8_t* _data_m, uint32_t _size_a) throw (exception_t)
            :pot_t()
      { //#:- Check parameters.
        if (!_data_m) throw (ArgumentError("NH::Protocols::Raw", "Null pointer"));
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Copy a memory block.
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memcpy(data_m, _data_m, size_m); }

      pot_t::pot_t(uint32_t _size_a) throw (exception_t)
            :pot_t()
      { //#:- Check parameter.
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Fill a memory block.
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memset(data_m, '\0', size_m); }

      pot_t::pot_t(const pot_t& _pot_a) noexcept
      { //#:- Copy object.
        if (_pot_a.data_m)
        { //#:- Copy a memory block.
          size_m = _pot_a.size_m;
          data_m = new uint8_t [size_m];
          std::memcpy(data_m, _pot_a.data_m, size_m); }
        else
        { //#:- Initialize.
          size_m = 0;
          data_m = nullptr; } }

      pot_t::pot_t(pot_t&& _pot_a) noexcept
      { //#:- Move object.
        data_m = _pot_a.data_m;
        size_m = _pot_a.size_m;
        _pot_a.data_m = nullptr;
        _pot_a.size_m = 0; }

      pot_t::~pot_t() noexcept
      { //#:- Free a memory block.
        if (data_m) { delete [] data_m; data_m = nullptr; }
        size_m = 0; }

      const pot_t& pot_t::operator=(const pot_t& _pot_a) noexcept
      { //#:- Check if duplicate.
        if (&_pot_a == this) return (*this);
        //#:- Clear `this` object.
        if (data_m) delete [] data_m;
        //#:- Copy object.
        if (_pot_a.data_m)
        { //#:- Copy a memory block.
          size_m = _pot_a.size_m;
          data_m = new uint8_t [size_m];
          std::memcpy(data_m, _pot_a.data_m, size_m); }
        else
        { //#:- Initialize.
          size_m = 0;
          data_m = nullptr; }
        return (*this); }

      const pot_t& pot_t::operator=(pot_t&& _pot_a) noexcept
      { //#:- Check if duplicate.
        if (&_pot_a == this) return (*this);
        //#:- Clear `this` object.
        if (data_m) delete [] data_m;
        //#:- Move object.
        data_m = _pot_a.data_m;
        size_m = _pot_a.size_m;
        _pot_a.data_m = nullptr;
        _pot_a.size_m = 0;
        return (*this); }

      uint32_t pot_t::set(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t)
      { //#:- Check parameters.
        if (!_data_a) throw (ArgumentError("NH::Protocols::Raw", "Null pointer"));
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Remove old content.
        if (data_m) delete [] data_m;
        //#:- Copy a memory block.
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memcpy(data_m, _data_a, size_m);
        return size_m; }

      uint32_t pot_t::set(uint32_t _size_a) throw (exception_t)
      { //#:- Check parameter.
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Remove old content.
        if (data_m) delete [] data_m;
        //#:- Create a memory block.
        size_m = _size_a;
        data_m = new uint8_t [size_m];
        std::memset(data_m, '\0', size_m);
        return size_m; }

      uint32_t pot_t::extend_at(const uint8_t* _data_a, uint32_t _size_a,
                                uint32_t _offset_a) throw (exception_t)
      { //#:- Check parameters.
        if (!_data_a) throw (ArgumentError("NH::Protocols::Raw", "Null pointer"));
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Check if offset is within range.
        if (_offset_a > size_m) throw (ArgumentError("NH::Protocols::Raw",
                                                     "Invalid offset"));
        //#:- Check for integer overflow.
        if (_size_a + size_m < size_m) throw (RuntimeError("NH::Protocols::Raw",
                                                           "Integer overflow"));
        uint8_t* new_data = new uint8_t [_size_a + size_m];
        //#:- Pot exists?
        if (data_m)
        { //#:- Copy first part of original pot.
          for (uint32_t index = 0; index < _offset_a; ++index)
           new_data[index] = data_m[index];
          //#:- Copy _data_a at _offset_a.
          for (uint32_t d_index = 0, o_index = _offset_a; d_index < _size_a;
               d_index++, o_index++) new_data[o_index] = _data_a[d_index];
          //#:- Copy rest of original pot.
          for (uint32_t o_index = _offset_a + _size_a, d_index = _offset_a;
               o_index < _size_a + size_m; o_index++, d_index++)
           new_data[o_index] = data_m[d_index];
          delete [] data_m; }
        else
        { //#:- Copy new pot.
          for (uint32_t index = 0; index < _size_a; ++index)
           new_data[index] = _data_a[index]; }
        //#:- Update variables.
        data_m = new_data;
        size_m += _size_a;
        return size_m; }

      uint32_t pot_t::extend_by(const uint8_t* _data_a,
                                uint32_t _size_a) throw (exception_t)
      { return extend_at(_data_a, _size_a, size()); }

      uint32_t pot_t::extend_by(uint32_t _size_a) throw (exception_t)
      { //#:- Check parameter.
        if (!_size_a) throw(ArgumentError("NH::Protocols::Raw", "Invalid size"));
        //#:- Construct new pot.
        uint8_t* new_data = new uint8_t [_size_a + size_m];
        //#:- Pot exists?
        if (data_m)
        { //#:- Copy old pot.
          for (uint32_t index = 0; index < size_m; ++index)
           new_data[index] = data_m[index];
          //#:- Fill new space.
          std::memset(new_data + size_m, '\0', _size_a);
          delete [] data_m; }
        else std::memset(new_data, '\0', _size_a);
        //#:- Update variables.
        data_m = new_data;
        size_m += _size_a;
        return size_m; }

      uint32_t pot_t::shrink_by(uint32_t _size_a) throw (exception_t)
      { //#:- Check parameter.
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        if (!data_m) throw (ArgumentError("NH::Protocols::Raw", "Nothing to shrink"));
        if (_size_a == size_m || size_m - _size_a >= size_m)
         throw (ArgumentError("NH::Protocols::Raw", "Unable to shrink"));
        //#:- Create shrinked pot.
        size_m = size_m - _size_a;
        uint8_t* new_data = new uint8_t [size_m];
        //#:- Copy pot
        for (uint32_t index = 0; index < size_m; ++index) new_data[index] = data_m[index];
        //#:- Update pot pointer.
        delete [] data_m;
        data_m = new_data;
        return size_m; }

      uint32_t pot_t::shrink_to(uint32_t _size_a) throw (exception_t)
      { //#:- Check parameter.
        if (!_size_a) throw (ArgumentError("NH::Protocols::Raw", "Invalid size"));
        if (!data_m) throw (ArgumentError("NH::Protocols::Raw", "Nothing to shrink"));
        if (_size_a >= size_m)
         throw (ArgumentError("NH::Protocols::Raw", "Unable to shrink"));
        size_m = _size_a;
        uint8_t* new_data = new uint8_t [size_m];
        //#:- Copy pot
        for (uint32_t index = 0; index < size_m; ++index) new_data[index] = data_m[index];
        //#:- Update pot pointer.
        delete [] data_m;
        data_m = new_data;
        return size_m; }

      uint32_t pot_t::clear() noexcept
      { if (data_m) delete [] data_m;
        data_m = nullptr;
        size_m = 0;
        return 0; }

      const uint8_t* pot_t::data() const noexcept
      { return data_m; }

      uint8_t pot_t::operator[](int32_t _index_a) const throw (exception_t)
      { //#:- In case index is negative,
        //#:- user wants array to be indexed in reverse.
        if (_index_a < 0) _index_a += size_m;
        //#:- _index_a can be safely treat as uint32_t.
        //#:- Check parameter.
        if (_index_a < 0 || static_cast<uint32_t>(_index_a) >= size_m)
         throw (ArgumentError("NH::Protocols::Raw","Invalid index"));
        return data_m[_index_a]; }

      uint8_t& pot_t::operator[](int32_t _index_a) throw (exception_t)
      { //#:- In case index is negative,
        //#:- user wants array to be indexed in reverse.
        if (_index_a < 0) _index_a += size_m;
        //#:- _index_a can be safely treat as uint32_t.
        //#:- Check parameter.
        if (_index_a < 0 || static_cast<uint32_t>(_index_a) >= size_m)
         throw (ArgumentError("NH::Protocols::Raw","Invalid index"));
        return data_m[_index_a]; }

      uint32_t pot_t::size() const noexcept
      { return size_m; }



    }

  }

}
