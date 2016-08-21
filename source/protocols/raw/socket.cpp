#include "protocols/raw/socket.hxx"

namespace Protocols
{ namespace Raw
  { socket_t::socket_t(const std::string& _interface_name_a) noexcept
    { //#:- Create RAW socket.
      socket_m = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
      if (socket_m == -1) throw (RuntimeError("NH::Protocols::Raw", strerror(errno)));
      //#:- Bound it to the network interface.
      if (setsockopt(socket_m, SOL_SOCKET, SO_BINDTODEVICE,
                     _interface_name_a.c_str(), _interface_name_a.size() == -1)
       throw (RuntimeError("NH::Protocols::Raw", strerror(errno)));
      

    }

  }

}
