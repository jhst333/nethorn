#include "protocols/raw/eth.hxx"

namespace NH
{ namespace Protocols
  { namespace Raw
    { ethernet_t::ethernet_t() noexcept
                 :pot_t(19)
      { extension_802_1q_m = false; }

      ethernet_t::ethernet_t(const uint8_t* _data_a, uint32_t _size_a) throw (exception_t)
                 :pot_t()
      { //#:- Standard size. Destination MAC + Source MAC + Ethertype.
        if (_size_a == 14) pot_t(_data_a, _size_a);
        //#:- 802.1Q TAG extension.
        //#:- Destination MAC + Source MAC + TAG + Ethertype.
        else if (_size_a == 19)
        { extension_802_1q_m = true;
          pot_t(_data_a, _size_a); }
        //#:- Malformed frame.
        else throw (ArgumentError("NH::Protocols::Raw", "Malformed frame.")); }

      ethernet_t::ethernet_t(const ethernet_t& _ethernet_a) noexcept
                 :pot_t(static_cast<const pot_t&>(_ethernet_a))
      { extension_802_1q_m = _ethernet_a.extension_802_1q_m; }

      ethernet_t::ethernet_t(ethernet_t&& _ethernet_a) noexcept
                 :pot_t(static_cast<pot_t&&>(_ethernet_a))
      { extension_802_1q_m = _ethernet_a.extension_802_1q_m; }

      ethernet_t::~ethernet_t() noexcept
      { ; }

      const ethernet_t& ethernet_t::operator=(const ethernet_t& _ethernet_a) noexcept
      { //#:- Check if 2 same objects.
        if (&_ethernet_a == this) return (*this);
        //#:- Use pot_t assign operator.
        pot_t::operator=(_ethernet_a);
        extension_802_1q_m = _ethernet_a.extension_802_1q_m;
        return (*this); }

      const ethernet_t& ethernet_t::operator=(ethernet_t&& _ethernet_a) noexcept
      { //#:- Check if 2 same objects.
        if (&_ethernet_a == this) return (*this);
        //#:- Use pot_t assign operator.
        pot_t::operator=(_ethernet_a);
        extension_802_1q_m = _ethernet_a.extension_802_1q_m;
        return (*this); }

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

      void ethernet_t::ethertype(uint16_t _type_a) noexcept
      { //#:- If 802.1Q TAG extension is present,
        //#:- ETHERTYPE is moved by 4 bytes futher.
        uint32_t offset = 0;
        if (extension_802_1q_m) offset = 4;
        //#:- Swap bytes and write into pot.
        uint16_t type = Helpers::swap_byte_order(_type_a);
        pot_t::write(&type, ETHERTYPE_SIZE, ETHERTYPE_START + offset); }

      uint16_t ethernet_t::ethertype() const noexcept
      { //#:- If 802.1Q TAG extension is present,
        //#:- ETHERTYPE is moved by 4 bytes futher.
        uint32_t offset = 0;
        if (extension_802_1q_m) offset = 4;
        //#:- Read ETHERTYPE.
        std::unique_ptr<uint8_t[]> bytes(pot_t::read(ETHERTYPE_SIZE,
                                                     ETHERTYPE_START + offset));
        //#:- Cast it into uint16_t, change byte order and return.
        return Helpers::swap_byte_order(*reinterpret_cast<uint16_t*>(bytes.get())); }

      void ethernet_t::extension_802_1q(bool _activate_a) throw (exception_t)
      { //#:- Do we want to activate this extension?
        if (_activate_a)
        { //#:- Check if extension is active.
          if (extension_802_1q_m)
           throw (ArgumentError("NH::Protocols::Raw", "Extension 802.1Q is already active."));
          //#:- Extend pot and write tag into new space.
          pot_t::extend_at(NH_RAW("\x81\x00\x00\x00"), EXTENSION_802_1Q_SIZE, EXTENSION_802_1Q_START);
          extension_802_1q_m = true; }
        else
        { //#:- Check if extension is not activate yet.
          if (!extension_802_1q_m)
           throw (ArgumentError("NH::Protocols::Raw", "Extension 802.1Q is not active."));
          //#:- Remove tag.
          pot_t::erase(EXTENSION_802_1Q_SIZE, EXTENSION_802_1Q_START);
          extension_802_1q_m = false; } }

      bool ethernet_t::extension_802_1q() const noexcept
      { return extension_802_1q_m; }

      void ethernet_t::extension_802_1q_pcp(uint8_t _pcp_a) throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw",
                             "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t.
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        //#:- Set PCP.
        header |= (static_cast<uint32_t>(_pcp_a) << 13);
        //#:- Write header back into pot.
        pot_t::write(NH_RAW(&header), EXTENSION_802_1Q_SIZE,
                                      EXTENSION_802_1Q_START); }

      uint8_t ethernet_t::extension_802_1q_pcp() const throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw", "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t and extract 3-bit field..
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        uint8_t pcp = (header >> 13);
        return pcp; }

      void ethernet_t::extension_802_1q_dei(bool _dei_a) throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw", "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t.
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        //#:- Set DEI.
        uint8_t dei = (_dei_a ? 1 : 0);
        header |= (static_cast<uint32_t>(dei) << 12);
        //#:- Write header back into pot.
        pot_t::write(NH_RAW(&header), EXTENSION_802_1Q_SIZE,
                                      EXTENSION_802_1Q_START); }

      bool ethernet_t::extension_802_1q_dei() const throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw", "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t and extract 1-bit field..
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        uint8_t dei = (header >> 12) & NH_BINARY(00000000000000000000000000000001);
        return (dei ? true : false); }

      void ethernet_t::extension_802_1q_vdi(uint16_t _vdi_a) throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw", "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t.
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        header |= (static_cast<uint32_t>(_vdi_a) & NH_BINARY(00000000000000000000111111111111));
        //#:- Write header back into pot.``
        pot_t::write(NH_RAW(&header), EXTENSION_802_1Q_SIZE,
                                      EXTENSION_802_1Q_START); }

      uint16_t ethernet_t::extension_802_1q_vdi() const throw (exception_t)
      { //#:- Check if extension is enabled.
        if (!extension_802_1q_m)
         throw (RuntimeError("NH::Protocols::Raw", "802.1Q extension is not enabled."));
        //#:- Read 802.1Q extension header.
        std::unique_ptr<uint8_t[]> extension_header(pot_t::read(EXTENSION_802_1Q_SIZE,
                                                                EXTENSION_802_1Q_START));
        //#:- Interpret it as uint32_t.
        uint32_t header = (*TO_UINT32_T(extension_header.get()));
        return (header & NH_BINARY(00000000000000000000111111111111)); }

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
