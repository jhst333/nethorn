#ifndef _NH_ETH_HXX_
#define _NH_ETH_HXX_

#include <string>
#include <memory>
#include <boost/crc.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include "protocols/raw/pot.hxx"
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
         #define MAC_SOURCE_START 0x00
         #define MAC_SOURCE_END 0x05
         #define MAC_DESTINATION_START 0x06
         #define MAC_DESTINATION_END 0x0B
         #define MAC_LENGTH 0x06
         #define ETHERTYPE_START
         //#:- Construction
         ethernet_t() noexcept;
         ethernet_t(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t);
         ethernet_t(const ethernet_t& _ethernet_a) noexcept;
         ethernet_t(ethernet_t&& _ethernet_a) noexcept;
         ~ethernet_t() noexcept;
         //#:- Copying
         const ethernet_t& operator=(const ethernet_t& _ethernet_a) noexcept;
         const ethernet_t& operator=(ethernet_t&& _ethernet_a) noexcept;
         //#:- Interface
         void source_mac(const std::string& _mac_a) throw (exception_t);
         std::string source_mac() const noexcept;
         void destination_mac(const std::string& _mac_a) throw (exception_t);
         std::string destination_mac() const noexcept;
         void ethertype(uint16_t _type_a) noexcept;
         uint16_t ethertype() const noexcept;
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
         bool tag_m;
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
