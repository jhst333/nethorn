#include "protocols/raw/eth.hxx"

#include <iostream>

namespace NH
{ namespace Protocols
  { namespace Raw
    { ethernet_t::ethernet_t() noexcept
                 :pot_t(19)
      { tag_m = false; }

      ethernet_t::ethernet_t(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t)
                 :pot_t()
      { //#:- Standard size. Destination MAC + Source MAC + Ethertype.
        if (_size_a == 14) pot_t(_data_a, _size_a);
        //#:- 802.1Q TAG extension.
        //#:- Destination MAC + Source MAC + TAG + Ethertype.
        else if (_size_a == 19)
        { tag_m = true;
          throw (ArgumentError("NH::Protocols::Raw", "Unsupported 802.1Q TAG"));

        }
        //#:- Malformed frame.
        else throw (ArgumentError("NH::Protocols::Raw", "Malformed frame."));

      }

      ethernet_t::ethernet_t(const ethernet_t& _ethernet_a) noexcept
                 :pot_t(static_cast<const pot_t&>(_ethernet_a))
      { tag_m = _ethernet_a.tag_m; }

      ethernet_t::ethernet_t(ethernet_t&& _ethernet_a) noexcept
                 :pot_t(static_cast<pot_t&&>(_ethernet_a))
      { tag_m = _ethernet_a.tag_m; }

      ethernet_t::~ethernet_t() noexcept
      { ; }

      const ethernet_t& ethernet_t::operator=(const ethernet_t& _ethernet_a) noexcept
      { //#:- Check if 2 same objects.
        if (&_ethernet_a == this) return (*this);
        //#:- Use pot_t assign operator.
        pot_t::operator=(_ethernet_a);
        tag_m = _ethernet_a.tag_m;
        return (*this); }

      const ethernet_t& ethernet_t::operator=(ethernet_t&& _ethernet_a) noexcept
      { //#:- Check if 2 same objects.
        if (&_ethernet_a == this) return (*this);
        //#:- Use pot_t assign operator.
        pot_t::operator=(_ethernet_a);
        tag_m = _ethernet_a.tag_m;
        return (*this); }

      void ethernet_t::source_mac(const std::string& _mac_a) throw (exception_t)
      { //#:- Check if _mac_a is NOT MAC address.
        if (!is_mac(_mac_a)) throw (ArgumentError("NH::Protocols::Raw", "Invalid MAC address"));
        //#:- Get bytes from MAC.
        std::unique_ptr<uint8_t[]> bytes(ethernet_t::get_bytes_from_mac(_mac_a));
        if (!bytes) throw (ArgumentError("NH::Protocols::Raw", "Invalid MAC address"));
        //#:- Write to pot.
        pot_t::write(bytes.get(), MAC_LENGTH, MAC_SOURCE_START); }

      std::string ethernet_t::source_mac() const noexcept
      { //#:- Read raw MAC.
        std::unique_ptr<uint8_t[]> mac_raw(pot_t::read(MAC_LENGTH,
                                                       MAC_SOURCE_START));
        //#:- Convert it to string.
        return ethernet_t::get_mac_from_bytes(mac_raw); }

      void ethernet_t::destination_mac(const std::string& _mac_a) throw (exception_t)
      { //#:- Check if _mac_a is NOT MAC address.
        if (!is_mac(_mac_a)) throw (ArgumentError("NH::Protocols::Raw", "Invalid MAC address"));
        //#:- Get bytes from MAC.
        std::unique_ptr<uint8_t[]> bytes(ethernet_t::get_bytes_from_mac(_mac_a));
        if (!bytes) throw (ArgumentError("NH::Protocols::Raw", "Invalid MAC address"));
        //#:- Write to pot.
        pot_t::write(bytes.get(), MAC_LENGTH, MAC_DESTINATION_START); }

      std::string ethernet_t::destination_mac() const noexcept
      { //#:- Read raw MAC.
        std::unique_ptr<uint8_t[]> mac_raw(pot_t::read(MAC_LENGTH,
                                                       MAC_DESTINATION_START));
        //#:- Convert it to string.
        return ethernet_t::get_mac_from_bytes(mac_raw); }

      bool ethernet_t::is_mac(const std::string& _mac_a) noexcept
      { //#:- Acceptable notations are: 00-11-22-33-44-55-66 or
        //#:- AA:BB:CC:DD:EE:FF
        static const boost::regex mac_regex("^([\\dA-Fa-f]{2}\\-){5}[\\dA-Fa-f]{2}|([\\dA-Fa-f]{2}\\:){5}[\\dA-Fa-f]{2}$");
        if (!boost::regex_match(_mac_a, mac_regex)) return false;
        return true; }

      std::unique_ptr<uint8_t[]> ethernet_t::get_bytes_from_mac(const std::string& _mac_a) noexcept
      { //#:- Perform no parameter checks.
        uint8_t* mac = nullptr;
        //#:- Construct regex and search for bytes.
        static const boost::regex byte_regex("([\\dA-Fa-f]{2})");
        boost::smatch results;
        if (!boost::regex_search(_mac_a.cbegin(), _mac_a.cend(), results, byte_regex) ||
            results.size() != 7) return std::unique_ptr<uint8_t[]>(mac);
        //#:- Allocate memory to fit 6 bytes of MAC.
        mac = new uint8_t [6];
        for (uint8_t index = 1; index != results.size(); ++index)
        { //#:- Convert result to hex.
          std::string hex("0x");
          hex.append(results[index]);
          mac[index - 1] = boost::lexical_cast<uint8_t>(hex.c_str()); }
        return std::unique_ptr<uint8_t[]>(mac); }

      std::string ethernet_t::get_mac_from_bytes(const std::unique_ptr<uint8_t[]>& _bytes_a)
                                                 noexcept
      { //#:- Perform no parameter checks.
        std::string mac;
        for (uint8_t index = 0; index < MAC_LENGTH; ++index)
        { //#:- Push each byte to /mac/.
          mac.append(boost::lexical_cast<std::string>(_bytes_a[index]));
          //#:- Split bytes.
          mac.push_back(':'); }
        //#: Remove last splitter.
        mac.pop_back();
        return mac; } } } }
