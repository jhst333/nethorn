#include "network_interface.hxx"

namespace NH
{ network_interface_t::network_interface_t()
  { //#:- Initialize with default values.
    name_m = "(null)";
    address_m = "0.0.0.0";
    netmask_m = address_m;
    broadcast_address_m = address_m;
    end_of_link_address_m = address_m; }

  network_interface_t::network_interface_t(const ifaddrs* _ifaddrs_a) throw (exception_t)
  { //#:- Check parameters.
    if (!_ifaddrs_a) throw (ArgumentError("NH", "No network interface data."));
    //#:- Check structure.
    //#:- safe_string_length will throw if name contains illegal characters.
    Helpers::safe_string_length(_ifaddrs_a.ifa_name,
                                network_interface_t::NETWORK_INTERFACE_MAX_LENGTH);
    //#:- Get device name.
    name_m = _ifaddrs_a.ifa_name;
    //#:- Get interface address.
    address_m = Helpers::ip_to_string(_ifaddrs_a.ifa_addr);
    //#:- Get interface netmask.
    netmask_m = Helpers::ip_to_string(_ifaddrs_a.ifa_netmask);
    if (!_ifaddrs_a.ifa_broadaddr)
    { //#:- Get interface broadcast address.
      broadcast_m = Helpers::ip_to_string(_ifaddrs_a.ifa_broadaddr);
      //#:- Mark this device as non-P2P.
      end_of_link_address_m = "0.0.0.0";
      p2p_device_m = false; }
    else
    { //#:- Get end of link address.
      end_of_link_address_m = Helpers::ip_to_string(_ifaddrs_a.ifu_dstaddr);
      //#:- Mark this device as P2P.
      broadcast_m = "0.0.0.0";
      p2p_device_m = true; } }

  network_interface_t::network_interface_t(const network_interface_t& _network_interface_a) noexcept
  { //#:- Copy all variables.
    name_m = _network_interface_a.name_m;
    address_m = _network_interface_a.address_m;
    netmask_m = _network_interface_a.netmask_m;
    broadcast_address_m = _network_interface_a.broadcast_address_m;
    end_of_link_address_m = _network_interface_a.end_of_link_address_m;
    p2p_device_m = _network_interface_a.p2p_device_m; }

  network_interface_t::network_interface_t(network_interface_t&& _network_interface_a) noexcept
  { //#:- Copy all variables.
    name_m = _network_interface_a.name_m;
    address_m = _network_interface_a.address_m;
    netmask_m = _network_interface_a.netmask_m;
    broadcast_address_m = _network_interface_a.broadcast_address_m;
    end_of_link_address_m = _network_interface_a.end_of_link_address_m;
    p2p_device_m = _network_interface_a.p2p_device_m; }

  network_interface_t::~network_interface_t() noexcept
  { ; }

  const network_interface_t& network_interface_t::operator=(const network_interface_t& _network_interface_a) noexcept
  { //#:- Check if this is a different object.
    if (this == &_network_interface_a) return (*this);
    //#:- Copy all variables.
    name_m = _network_interface_a.name_m;
    address_m = _network_interface_a.address_m;
    netmask_m = _network_interface_a.netmask_m;
    broadcast_address_m = _network_interface_a.broadcast_address_m;
    end_of_link_address_m = _network_interface_a.end_of_link_address_m;
    p2p_device_m = _network_interface_a.p2p_device_m;
    return (*this); }

  const network_interface_t& network_interface_t::operator=(network_interface_t&& _network_interface_a) noexcept
  { //#:- Check if this is a different object.
    if (this == &_network_interface_a) return (*this);
    //#:- Copy all variables.
    name_m = _network_interface_a.name_m;
    address_m = _network_interface_a.address_m;
    netmask_m = _network_interface_a.netmask_m;
    broadcast_address_m = _network_interface_a.broadcast_address_m;
    end_of_link_address_m = _network_interface_a.end_of_link_address_m;
    p2p_device_m = _network_interface_a.p2p_device_m;
    return (*this); }

  const std::string& network_interface_t::name() const noexcept
  { return name_m; }

  const std::string& network_interface_t::address() const noexcept
  { return address_m; }

  const std::string& network_interface_t::netmask() const noexcept
  { return netmask_m; }

  const std::string& network_interface_t::broadcast() const noexcept
  { return broadcast_address_m; }

  const std::string& network_interface_t::end_of_link() const noexcept
  { return end_of_link_address_m; }

  bool network_interface_t::is_p2p() const noexcept
  { return p2p_device_m; }

  network_interfaces_t network_interface_t::get_interfaces() noexcept
  { network_interfaces_t map;
    //#:- Get interfaces.
    ifaddrs* interfaces;
    ifaddrs* interface;
    getifaddrs(&structures);
    //#:- Iterate over interface structures and create network_interface_t objects.
    for (interface = structures; interface; interface = interface->ifa_next)
    { network_interface_t device(interface);
      map[interface.name()] = device; }
    freeifaddrs(structures);
    return map; } }
