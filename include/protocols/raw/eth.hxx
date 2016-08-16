#ifndef _NH_ETH_HXX_
#define _NH_ETH_HXX_

#include <string>
#include <memory>
#include <boost/crc.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include "protocols/raw/pot.hxx"
#include "helpers.hxx"
#include "exception.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { /*! \brief ethernet_t Is a class that helps generating ethernet frames.
       *
       * This class allows manipulating ethernet frame by providing additional
       * layer of abstraction over pot_t class. You can manipulate ethernet frame
       * by using variety of methods and even access raw data stream. */
      class ethernet_t : public pot_t
      { public:
         //#:- Constants
         #define MAC_DESTINATION_START 0x00
         #define MAC_DESTINATION_END 0x05
         #define MAC_SOURCE_START 0x06
         #define MAC_SOURCE_END 0x0B
         #define MAC_LENGTH 0x06
         #define TAG_START 0x0C
         #define TAG_SIZE 0x0C
         #define ETHERTYPE_START 0x0C
         #define ETHERTYPE_SIZE 0x02
         //#:- Construction
         /*! \brief Default constructor.
          *
          * Constructs \class ethernet_t object.
          * \throws Nothing, */
         ethernet_t() noexcept;
         /*! \brief Constructs \class ethernet_t object.
          *
          * Constructs object using raw \p _data_a ethernet data
          * with \p _size_a size.
          * \throw \class exception_t If raw frame does not fit in standard template or
          * does not fit in standard template + frame extensions. (802.1Q) */
         ethernet_t(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t);
         /*! \brief Default copy constructor.
          * \throw Nothing. */
         ethernet_t(const ethernet_t& _ethernet_a) noexcept;
         /*! \brief Default move constructor.
          * \throw Nothing. */
         ethernet_t(ethernet_t&& _ethernet_a) noexcept;
         /*! \brief Default Destructor.
          * \throw Nothing. */
         ~ethernet_t() noexcept;
         //#:- Copying
         /*! \biref Copy assign operator.
          * \throw Nothing. */
         const ethernet_t& operator=(const ethernet_t& _ethernet_a) noexcept;
         /*! \biref Move assign operator.
          * \throw Nothing. */
         const ethernet_t& operator=(ethernet_t&& _ethernet_a) noexcept;
         //#:- Interface
         /*! \brief Sets destination MAC address.
          *
          * Sets destination MAC address. MAC address can be in 2 notations.
          * (01-23-45-67-89-AB, AA:BB:CC:DD:EE:FF)
          * \throw \class exception_t If MAC address is invalid.
          * \return Nothing. */
         void destination_mac(const std::string& _mac_a) throw (exception_t);
         /*! \brief Gets destination MAC address.
          * \throw Nothing.
          * \return String with destination MAC address.
          * (Six groups of two hexadecimal digits separated by colons.) */
         std::string destination_mac() const noexcept;
         /*! \brief Sets source MAC address.
          *
          * Sets source MAC address. MAC address can be in 2 notations.
          * (01-23-45-67-89-AB, AA:BB:CC:DD:EE:FF)
          * \throw \class exception_t If MAC address is invalid.
          * \return Nothing. */
         void source_mac(const std::string& _mac_a) throw (exception_t);
         /*! \brief Gets source MAC address.
          * \throw Nothing.
          * \return String with source MAC address.
          * (Six groups of two hexadecimal digits separated by colons.) */
         std::string source_mac() const noexcept;
         /*! \brief Sets ETHERTYPE.
          * \throw Nothing.
          * \return Nothing. */
         void ethertype(uint16_t _type_a) noexcept;
         /*! \brief Gets ETHERTYPE.
          * \throw Nothing.
          * \return ETHERTYPE value. */
         uint16_t ethertype() const noexcept;
         /*! \brief Activates the 802.1Q extension.
          *
          * Sets 802.1Q accordingly to \p _activate_a bool parameter.
          * \throw \class exception_t If:
          * - You're willing to disable extension, but it is disabled already,
          * - You're willing to enable extension, but it is enabled already.
          * \return Nothing. */
         void extension_802_1q(bool _activate_a) throw (exception_t);
         /*! \brief Returns the state of 802.1Q activation flag.
          *
          * \throw Nothing.
          * \return True if 802.1Q extension is activated, False otherwise. */
         bool extension_802_1q() const noexcept;
         //#:- Validation
         static bool is_mac(const std::string& _mac_a) noexcept;
         template <typename... layers_t>
         static uint32_t calculate_checksum(pot_t _layer_a, layers_t... _layers_a)
         { boost::crc_32_type result = calculate_checksum(_layers_a...);
           result.process_bytes(_layer_a.data(), _layer_a.size());
           return result.checksum(); }

         static boost::crc_32_type calculate_checksum(pot_t _layer_a) noexcept
         { boost::crc_32_type result;
           result.process_bytes(_layer_a.data(), _layer_a.size());
           return result; }
        private:
         bool extension_802_1q_m;
         //#:- Helpers.
         static std::unique_ptr<uint8_t[]> get_bytes_from_mac(const std::string& _mac_a)
                                                              noexcept;
         static std::string get_mac_from_bytes(const std::unique_ptr<uint8_t[]>& _bytes_a)
                                               noexcept;

      };

    }

  }

}

#endif
