//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/module/core/decorator/compensated.hpp>
#include <eve/module/core/decorator/cyl.hpp>
#include <eve/module/core/decorator/fuzzy.hpp>
#include <eve/module/core/decorator/kind.hpp>
#include <eve/module/core/decorator/musl.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/decorator/plain.hpp>
#include <eve/module/core/decorator/promote.hpp>
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/decorator/regular.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/decorator/sph.hpp>
#include <eve/module/core/decorator/successor.hpp>

//======================================================================================================================
// New option style  - TODO rename later without the '2'
//======================================================================================================================
#include <eve/detail/raberu.hpp>

namespace eve
{
  struct almost_mode      {};
  struct compensated_mode {};
  struct definitely_mode  {};
  struct kind_1_mode      {};
  struct kind_2_mode      {};
  struct musl_mode        {};
  struct numeric_mode     {};
  struct p_kind_mode      {};
  struct pedantic_mode    {};
  struct plain_mode       {};
  struct promote_mode     {};
  struct q_kind_mode      {};
  struct raw_mode         {};
  struct regular_mode     {};
  struct saturated_mode   {};
  struct spherical_mode   {};
  struct successor_mode   {};
  struct tolerant_mode    {};

  struct rounding_key_t : rbr::as_keyword<rounding_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<rounding_key_t,Value>{};
    }
  };
  [[maybe_unused]] inline constexpr rounding_key_t rounding_key = {};

  template<int N>
  [[maybe_unused]] inline constexpr auto rounding = (rounding_key = eve::index<N>);

  [[maybe_unused]] inline constexpr auto almost2      = ::rbr::flag( almost_mode{}    );
  [[maybe_unused]] inline constexpr auto compensated2 = ::rbr::flag( compensated_mode{});
  [[maybe_unused]] inline constexpr auto definitely2  = ::rbr::flag( definitely_mode{});
  [[maybe_unused]] inline constexpr auto downward2    = rounding<(0x01 | 0x08)>;
  [[maybe_unused]] inline constexpr auto kind_12      = ::rbr::flag( kind_1_mode{}    );
  [[maybe_unused]] inline constexpr auto kind_22      = ::rbr::flag( kind_2_mode{}    );
  [[maybe_unused]] inline constexpr auto musl2        = ::rbr::flag( musl_mode{}      );
  [[maybe_unused]] inline constexpr auto numeric2     = ::rbr::flag( numeric_mode{}   );
  [[maybe_unused]] inline constexpr auto p_kind2      = ::rbr::flag( p_kind_mode{}    );
  [[maybe_unused]] inline constexpr auto pedantic2    = ::rbr::flag( pedantic_mode{}  );
  [[maybe_unused]] inline constexpr auto plain2       = ::rbr::flag( plain_mode{}     );
  [[maybe_unused]] inline constexpr auto promote2     = ::rbr::flag( promote_mode{}   );
  [[maybe_unused]] inline constexpr auto q_kind2      = ::rbr::flag( q_kind_mode{}    );
  [[maybe_unused]] inline constexpr auto raw2         = ::rbr::flag( raw_mode{}       );
  [[maybe_unused]] inline constexpr auto regular2     = ::rbr::flag( regular_mode{}   );
  [[maybe_unused]] inline constexpr auto saturated2   = ::rbr::flag( saturated_mode{} );
  [[maybe_unused]] inline constexpr auto spherical    = ::rbr::flag( spherical_mode{} );
  [[maybe_unused]] inline constexpr auto successor2   = ::rbr::flag( successor_mode{} );
  [[maybe_unused]] inline constexpr auto to_nearest2  = rounding<(0x00 | 0x08)>;
  [[maybe_unused]] inline constexpr auto tolerant2    = ::rbr::flag( tolerant_mode{}  );
  [[maybe_unused]] inline constexpr auto toward_zero2 = rounding<(0x03 | 0x08)>;
  [[maybe_unused]] inline constexpr auto upward2      = rounding<(0x02 | 0x08)>;

  struct almost_option      : detail::exact_option<almost2>       {};
  struct compensated_option : detail::exact_option<compensated2>  {};
  struct definitely_option  : detail::exact_option<definitely2>   {};
  struct kind_1_option      : detail::exact_option<kind_12>       {};
  struct kind_2_option      : detail::exact_option<kind_22>       {};
  struct musl_option        : detail::exact_option<musl2>         {};
  struct numeric_option     : detail::exact_option<numeric2>      {};
  struct p_kind_option      : detail::exact_option<p_kind2>       {};
  struct pedantic_option    : detail::exact_option<pedantic2>     {};
  struct plain_option       : detail::exact_option<plain2>        {};
  struct promote_option     : detail::exact_option<promote2>      {};
  struct q_kind_option      : detail::exact_option<q_kind2>       {};
  struct raw_option         : detail::exact_option<raw2>          {};
  struct regular_option     : detail::exact_option<regular2>      {};
  struct rounding_option    : detail::exact_option<rounding_key>  {};
  struct saturated_option   : detail::exact_option<saturated2>    {};
  struct spherical_option   : detail::exact_option<spherical>     {};
  struct successor_option   : detail::exact_option<successor2>    {};
  struct tolerant_option    : detail::exact_option<tolerant2>     {};

  // ----------------------------------------------------------------------------------
  // [TEMPORARY] Will be removed when all decorator have been converted
  // ----------------------------------------------------------------------------------
  inline constexpr auto as_option(almost_type       const&) { return almost2;       }
  inline constexpr auto as_option(compensated_type  const&) { return compensated2;  }
  inline constexpr auto as_option(definitely_type   const&) { return definitely2;   }
  inline constexpr auto as_option(downward_type     const&) { return downward2;     }
  inline constexpr auto as_option(kind_1_type       const&) { return kind_12;       }
  inline constexpr auto as_option(kind_2_type       const&) { return kind_22;       }
  inline constexpr auto as_option(musl_type         const&) { return musl2;         }
  inline constexpr auto as_option(numeric_type      const&) { return numeric;       }
  inline constexpr auto as_option(p_kind_type       const&) { return p_kind2;       }
  inline constexpr auto as_option(pedantic_type     const&) { return pedantic2;     }
  inline constexpr auto as_option(plain_type        const&) { return plain2;        }
  inline constexpr auto as_option(promote_type      const&) { return promote2;      }
  inline constexpr auto as_option(q_kind_type       const&) { return q_kind2;       }
  inline constexpr auto as_option(raw_type          const&) { return raw2;          }
  inline constexpr auto as_option(regular_type      const&) { return regular2;      }
  inline constexpr auto as_option(saturated_type    const&) { return saturated2;    }
  inline constexpr auto as_option(sph_type          const&) { return spherical;     }
  inline constexpr auto as_option(successor_type    const&) { return successor2;    }
  inline constexpr auto as_option(to_nearest_type   const&) { return to_nearest2;   }
  inline constexpr auto as_option(tolerant_type     const&) { return tolerant2;     }
  inline constexpr auto as_option(toward_zero_type  const&) { return toward_zero2;  }
  inline constexpr auto as_option(upward_type       const&) { return upward2;       }
}
