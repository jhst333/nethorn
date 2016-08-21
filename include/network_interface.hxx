#ifndef _NH_NETWORK_INTERFACE_HXX_
#define _NH_NETWORK_INTERFACE_HXX_

#include <map>
#include <ifaddrs.hpp>

#include "exception.hxx"
#include "helpers.hxx"

namespace NH
{ using network_interfaces_t = std::map<std::string, network_interface_t>;
  /*! \brief \class network_interface_t Parses \struct ifaddrs structure.
   *
   * This class is used to ease accessing network interface parameters. */
  class network_interface_t
  { private:
     //#:- Constants
     static const uint32_t NETWORK_INTERFACE_MAX_LENGTH;
     //#:- Construction
     /*! \brief Default constructor.
      * \throw Nothing.
      * \return Nothing. */
     network_interface_t() noexcept;
     /*! \brief Non-default constructor.
      *
      * Constructs an object using information from \struct ifaddrs structure.
      * \throw \class exception_t.
      * \return Nothing. */
     network_interface_t(const ifaddrs* _ifaddrs_a) throw (exception_t);
     /*! \brief Copy-constructor.
      * \throw Nothing.
      * \return Nothing. */
    public:
     network_interface_t(const network_interface_t& _network_interface_a) noexcept;
     /*! \brief Move-constructor.
      * \throw Nothing.
      * \return Nothing. */
     network_interface_t(network_interface_t&& _network_interface_a) noexcept;
     /*! \brief Default deconstructor.
      * \throw Nothing.
      * \return Nothing. */
     virtual ~network_interface_t() noexcept;
     /*! \brief Assign operator.
      * \throw Nothing.
      * \return \class network_interface_t Copy. */
     const network_interface_t& operator=(const network_interface_t& _network_interface_a) noexcept;
     /*! \brief Assign operator.
      * \throw Nothing.
      * \return \class network_interface_t Copy. */
     const network_interface_t& operator=(network_interface_t&& _network_interface_a) noexcept;
     //#:- Interface
     /*! \brief Returns name of the network interface.
      * \throw Nothing.
      * \return Name of network interface. */
     const std::string& name() const noexcept;
     /*! \brief Returns address of the network interface.
      * \throw Nothing.
      * \return Address of the network interface. */
     const std::string& address() const noexcept;
     /*! \brief Returns netmask of the network interface.
      * \throw Nothing.
      * \return Netmask of the network interface. */
     const std::string& netmask() const noexcept;
     /*! \brief Returns broadcast address of the network interface.
      * \throw Nothing.
      * \return Broadcast address of the network interface. */
     const std::string& broadcast() const noexcept;
     /*! \brief Returns end of link address.
      * \throw Nothing.
      * \return End of link address. */
     const std::string& end_of_link() const noexcept;
     /*! \brief Returns state if this network interface is P2P.
      * \throw Nothing.
      * \return True if the network interface is P2P, false otherwise. */
     bool is_p2p() const noexcept;
     //TODO: WRITE DOC
     static network_interfaces_t get_interfaces() noexcept
    private:
     std::string name_m;
     std::string address_m;
     std::string netmask_m;
     std::string broadcast_address_m;
     std::string end_of_link_address_m;
     bool p2p_device_m; };

  const uint32_t network_interface_t::NETWORK_INTERFACE_MAX_LENGTH = 255;

}

#endif
