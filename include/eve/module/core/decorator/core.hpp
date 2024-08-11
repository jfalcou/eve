//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
//#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/as_element.hpp>
#include <eve/as.hpp>

//======================================================================================================================
// New option style  - TODO rename later without the '2'
//======================================================================================================================
namespace eve
{
  struct almost_mode          {};
  struct associated_mode      {};
  struct compensated_mode     {};
  struct condon_shortley_mode {};
  struct definitely_mode      {};
  struct kind_1_mode          {};
  struct kind_2_mode          {};
  struct numeric_mode         {};
  struct p_kind_mode          {};
  struct promote_mode         {};
  struct q_kind_mode          {};
  struct spherical_mode       {};
  struct successor_mode       {};

  struct to_nearest_mode  { static constexpr int value = 0x08 | 0x00; }; // _MM_FROUND_TO_NEAREST_INT
  struct downward_mode    { static constexpr int value = 0x08 | 0x01; }; // _MM_FROUND_TO_NEG_INF
  struct upward_mode      { static constexpr int value = 0x08 | 0x02; }; // _MM_FROUND_TO_POS_INF
  struct toward_zero_mode { static constexpr int value = 0x08 | 0x03; }; // _MM_FROUND_TO_ZERO
  struct pedantic_mode    {};
  struct raw_mode         {};
  struct saturated_mode   {};

  [[maybe_unused]] inline constexpr auto associated       = ::rbr::flag( associated_mode{}      );
  [[maybe_unused]] inline constexpr auto compensated      = ::rbr::flag( compensated_mode{}     );
  [[maybe_unused]] inline constexpr auto condon_shortley  = ::rbr::flag( condon_shortley_mode{} );
  [[maybe_unused]] inline constexpr auto kind_1           = ::rbr::flag( kind_1_mode{}          );
  [[maybe_unused]] inline constexpr auto kind_2           = ::rbr::flag( kind_2_mode{}          );
  [[maybe_unused]] inline constexpr auto numeric          = ::rbr::flag( numeric_mode{}         );
  [[maybe_unused]] inline constexpr auto p_kind           = ::rbr::flag( p_kind_mode{}          );
  [[maybe_unused]] inline constexpr auto promote          = ::rbr::flag( promote_mode{}         );
  [[maybe_unused]] inline constexpr auto q_kind           = ::rbr::flag( q_kind_mode{}          );
  [[maybe_unused]] inline constexpr auto spherical        = ::rbr::flag( spherical_mode{}       );
  [[maybe_unused]] inline constexpr auto successor        = ::rbr::flag( successor_mode{}       );

  [[maybe_unused]] inline constexpr auto downward2    = ::rbr::flag( downward_mode{}    );
  [[maybe_unused]] inline constexpr auto pedantic2    = ::rbr::flag( pedantic_mode{}    );
  [[maybe_unused]] inline constexpr auto raw2         = ::rbr::flag( raw_mode{}         );
  [[maybe_unused]] inline constexpr auto saturated2   = ::rbr::flag( saturated_mode{}   );
  [[maybe_unused]] inline constexpr auto to_nearest2  = ::rbr::flag( to_nearest_mode{}  );
  [[maybe_unused]] inline constexpr auto toward_zero2 = ::rbr::flag( toward_zero_mode{} );
  [[maybe_unused]] inline constexpr auto upward2      = ::rbr::flag( upward_mode{}      );

  struct associated_option      : detail::exact_option<associated>      {};
  struct compensated_option     : detail::exact_option<compensated>     {};
  struct condon_shortley_option : detail::exact_option<condon_shortley> {};
  struct kind_1_option          : detail::exact_option<kind_1>          {};
  struct kind_2_option          : detail::exact_option<kind_2>          {};
  struct numeric_option         : detail::exact_option<numeric>         {};
  struct p_kind_option          : detail::exact_option<p_kind>          {};
  struct promote_option         : detail::exact_option<promote>         {};
  struct q_kind_option          : detail::exact_option<q_kind>          {};
  struct spherical_option       : detail::exact_option<spherical>       {};
  struct successor_option       : detail::exact_option<successor>       {};

  struct downward_option     : detail::exact_option<downward2>    {};
  struct pedantic_option     : detail::exact_option<pedantic2>    {};
  struct raw_option          : detail::exact_option<raw2>         {};
  struct saturated_option    : detail::exact_option<saturated2>   {};
  struct to_nearest_option   : detail::exact_option<to_nearest2>  {};
  struct toward_zero_option  : detail::exact_option<toward_zero2> {};
  struct upward_option       : detail::exact_option<upward2>      {};

  // ----------------------------------------------------------------------------------
  // Turn rounding mode option into the proper constexpr flags for x86 intrinsic
  // ----------------------------------------------------------------------------------
  template<typename S, typename T> consteval int rounding_mode(T) noexcept
  {
    // All set the _MM_FROUND_NO_EXC bit
    if      constexpr(S::contains(eve::to_nearest2 )) return to_nearest_mode::value;
    else if constexpr(S::contains(eve::downward2   )) return downward_mode::value;
    else if constexpr(S::contains(eve::toward_zero2)) return toward_zero_mode::value;
    else if constexpr(S::contains(eve::upward2     )) return upward_mode::value;
    else                                              return T::id_type::value;
  };

  // ----------------------------------------------------------------------------------
  // [TEMPORARY] Will be removed when all decorator have been converted
  // ----------------------------------------------------------------------------------
  inline constexpr auto as_option(downward_type     const&) { return downward2;     }
  inline constexpr auto as_option(pedantic_type     const&) { return pedantic2;     }
//  inline constexpr auto as_option(raw_type          const&) { return raw2;          }
  inline constexpr auto as_option(saturated_type    const&) { return saturated2;    }
  inline constexpr auto as_option(to_nearest_type   const&) { return to_nearest2;   }
  inline constexpr auto as_option(toward_zero_type  const&) { return toward_zero2;  }
  inline constexpr auto as_option(upward_type       const&) { return upward2;       }

  // New tolerance option that carry a value
  template<typename Value> struct almost_t;

  struct almost_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, almost_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };

  template<typename Value> struct definitely_t;

  struct definitely_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, definitely_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };
}
