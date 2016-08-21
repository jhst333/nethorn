#ifndef _NH_SOCKET_HXX_
#define _NH_SOCKET_HXX_

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <cstdint>
#include <errno.h>
#include <cstring>

#include "protocols/raw/pot.hxx"
#include "exception.hxx"

namespace NH
{ namespace Raw
  { class socket_t
    { public:
       //#:- Construction
       socket_t(const std::string& _interface_name_a = std::string("lo")) throw (exception_t);
       socket_t(const socket_t& _socket_a) noexcept;
       socket_t(socket_t&& _socket_a) noexcept;
       virtual ~socket_t() noexcept;
       //#:- Copying
       const socket_t& operator=(const socket_t& _socket_a) noexcept;
       const socket_t& operator=(socket_t&& _socket_a) noexcept;
       //#:- Interface
       uint32_t send(const pot_t& _pot_a);
      private:
       int32_t socket_m;

    };

  }

}

#endif
