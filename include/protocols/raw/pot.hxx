#ifndef _NH_POT_HXX_
#define _NH_POT_HXX_

#include <cstdint>

#include "../../exception.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { /*! \brief pot_t Is a class that allows manipulation over raw data.

          It is used to help crafting raw packets. */
      class pot_t
      { public:
         //#:- Construction
         /*! \brief Default constructor.
          *
          *  Initializes class members with default values. */
         pot_t() noexcept;
         /*! \brief Non-default constructor.
          *
          *  Constructs object with given length \p _size_a and fills it
          *  with \p _data_a */
         pot_t(const uint8_t* _data_a, uint32_t _size_a) throw(exception_t);
         /*! \brief Non-default constructor.
          *
          *  Constructs object with given length \p _size_a and fills it
          *  with zeros. */
         pot_t(uint32_t _size_a) throw(exception_t);
         /*! \brief Copy constructor. */
         pot_t(const pot_t& _pot_a) noexcept;
         /*! \brief Move constructor. */
         pot_t(pot_t&& _pot_a) noexcept;
         /*! \brief Destructor */
         ~pot_t() noexcept;
         //#:- Copying
         /*! \brief Assign operator */
         const pot_t& operator=(const pot_t& _pot_a) noexcept;
         /*! \brief Move operator */
         const pot_t& operator=(pot_t&& _pot_a) noexcept;
         //#:- Memory manipulation
         /*! \brief Sets the new content into the container.
          *
          * Sets container with \p _size_a long size and fills
          * it with \p _data_a data. */
         uint32_t set(const uint8_t* _data_a, uint32_t _size_a) throw(exception_t);
         /*! \brief Sets the new content into the container.
          *
          * Sets container with \p _size_a long size and fills
          * it with \p _data_a data. */
         uint32_t set(uint32_t _size_a) throw(exception_t);
         uint32_t extend(const uint8_t* _data_a, uint32_t _size_a, uint32_t _offset) throw(exception_t);
         uint32_t extend_by(const uint8_t* _data_a, uint32_t _size_a) throw(exception_t);
         uint32_t extend_by(uint32_t _size_a) throw(exception_t);
         uint32_t extend_to(const uint8_t* _data_a, uint32_t _size_a) throw(exception_t);
         uint32_t shrink_by(uint32_t _size_a) throw(exception_t);
         uint32_t shrink_to(uint32_t _size_a) throw(exception_t);
         uint32_t clear() noexcept;
         //#:- Memory access
         const uint8_t* data() const noexcept;
         uint8_t operator[](int32_t _index_a) const throw(exception_t);
         uint8_t& operator[](int32_t _index_a) throw(exception_t);
         //#:- State
         uint32_t size() const noexcept;
        private:
         uint8_t* data_m;
         uint32_t size_m; }; } } }

#endif
