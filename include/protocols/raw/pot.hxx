#ifndef _POT_HXX_
#define _POT_HXX_

#include <cstdint>

namespace NH
{ namespace Protocols
  { namespace Raw
    { class pot_t
      { public:
         //#:- Construction
         Pot() noexcept;
         Pot();
         Pot(const Pot&) noexcept;
         Pot(Pot&&) noexcept;
         ~Pot() noexcept;
         //#:- Copying
         const Pot& operator=(const Pot&) noexcept;
         const Pot& operator=(Pot&&) noexcept;
         //#:- Interface

        private:
         uint8_t* data_m;
         uint32_t size_m; };

    }

  }

}

#endif
