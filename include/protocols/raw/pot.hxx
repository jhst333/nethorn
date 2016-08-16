#ifndef _NH_POT_HXX_
#define _NH_POT_HXX_

#include <cstdint>

#include "exception.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { /*! \brief pot_t Is a class that allows manipulation over raw data.
       *
       * It is used to help crafting raw packets. */
      class pot_t
      { public:
         //#:- Construction
         /*! \brief Default constructor.
          *
          * Initializes class members with default values. */
         pot_t() noexcept;
         /*! \brief Non-default constructor.
          *
          * Constructs object with given length \p _size_a and fills it
          * with \p _data_a */
         pot_t(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t);
         /*! \brief Non-default constructor.
          *
          * Constructs object with given length \p _size_a and fills it
          * with zeros. */
         pot_t(uint32_t _size_a) throw (exception_t);
         /*! \brief Copy constructor. */
         pot_t(const pot_t& _pot_a) noexcept;
         /*! \brief Move constructor. */
         pot_t(pot_t&& _pot_a) noexcept;
         /*! \brief Destructor */
         virtual ~pot_t() noexcept;
         //#:- Copying
         /*! \brief Assign operator
          * \returns Copy of \p _pot_a. */
         const pot_t& operator=(const pot_t& _pot_a) noexcept;
         /*! \brief Move operator
          * \returns Copy of \p _pot_a. */
         const pot_t& operator=(pot_t&& _pot_a) noexcept;
        //#:- In case we're compiling tests and debug version.
        #ifndef NH_TEST
         //#:- There is really no purpose to put these methods in public access.
         protected:
        #endif
         //#:- Memory manipulation
         /*! \brief Sets the new content into the pot.
          *
          * Sets pot with \p _size_a long size and fills
          * it with \p _data_a data.
          * \returns Size of pot. */
         uint32_t set(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t);
         /*! \brief Sets the new content into the pot.
          *
          * Sets pot with \p _size_a long size and fills
          * it with \p _data_a data.
          * \returns Size of pot. */
         uint32_t set(uint32_t _size_a) throw (exception_t);
         /*! \brief Extends pot size.
          *
          * Extends pot by \p _size_a size, filling new space with \p _data_a
          * at \p _offset_a offset.
          * \returns Size of pot. */
         uint32_t extend_at(const uint8_t* _data_a, uint32_t _size_a,
                            uint32_t _offset_a) throw (exception_t);
         /*! \brief Extends pot size.
          *
          * Extends pot by \p _size_a size, filling new space with \p _data_a.
          * \returns Size of pot. */
         uint32_t extend_by(const uint8_t* _data_a, uint32_t _size_a)
                            throw (exception_t);
         /*! \brief Extends pot size.
          *
          * Extends pot by \p _size_a size, filling new space with \x00 bytes.
          * \returns Size of pot. */
         uint32_t extend_by(uint32_t _size_a) throw (exception_t);
         /*! \brief Shirnks pot size.
          *
          * Shirnks pot by \p _size_a size.
          * \returns Size of pot. */
         uint32_t shrink_by(uint32_t _size_a) throw (exception_t);
         /*! \brief Shirnks pot size.
          *
          * Shirnks pot to \p _size_a size.
          * \returns Size of pot. */
         uint32_t shrink_to(uint32_t _size_a) throw (exception_t);
         /*! \brief Erases given pot region.
          *
          * Erases region at \p _offset_a offset with \p _size_a size.
          * \throw \class exception_t If:
          * - Parameters are invalid;
          * - Region is bigger than pot;
          * \return Size of pot after erase operation. */
         uint32_t erase(uint32_t _size_a, uint32_t _offset_a) throw (exception_t);
         /*! \brief Writes data to pot.
          *
          * Writes \p _data_a at \p _offset_a offset with \p _size_a size.
          * \returns Size of pot. */
         uint32_t write(const void* _data_a, uint32_t _size_a,
                        uint32_t _offset_a) throw (exception_t);
         /*! \brief Clears a pot.
          * \returns Size of pot. */
         uint32_t clear() noexcept;
         //#:- Memory access
         /*! \brief Reads data from pot.
          *
          * Reads data from pot at \p _offset_a offset with \p _size_a size.
          * \returns Pointer to copied data from pot. */
         uint8_t* read(uint32_t _size_a, uint32_t _offset_a) const throw (exception_t);
        public:
         /*! \brief Returns pot.
          * \returns Pointer to held data. */
         const uint8_t* data() const noexcept;
         /*! \brief Accesses pot by \p _index_a index.
          *
          * Index value can be negative.
          * In such case, pot will be accessed in reverse.
          * \returns Byte from pot at given index. */
         uint8_t operator[](int32_t _index_a) const throw (exception_t);
         /*! \brief Accesses pot by \p _index_a index.
          *
          * Index value can be negative.
          * In such case, pot will be accessed in reverse.
          * \returns Reference to byte from pot at given index. */
         uint8_t& operator[](int32_t _index_a) throw (exception_t);
         //#:- State
         /*! \brief Returns size of pot.
          * \returns Size of pot. */
         uint32_t size() const noexcept;
        private:
         /*! \brief Pot that is holding raw data. */
         uint8_t* data_m;
         /*! \brief Size of pot. */
         uint32_t size_m; }; } } }

#endif
