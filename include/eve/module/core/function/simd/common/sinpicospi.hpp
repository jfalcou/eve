//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINPICOSPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINPICOSPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/module/core/detail/simd/sincos_finalize.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/combine.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto internal_sinpicospi(restricted_type const &
                                      , eve::wide<T,N,ABI> const &a0) noexcept
  {
    return restricted_(sincos)(a0*Pi<T>());
  }

  //////////////////////////////////////////////////////////////////////////////
  /// big, medium, small
  template<typename D, typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto internal_sinpicospi(D const &, eve::wide<T,N,ABI> const &a0) noexcept
  {
    auto x = eve::abs(a0);
    auto y = if_else(is_not_finite(x), eve::allbits_ , x);
    auto z = bit_mask(y <= Maxflint(as(y))) & y;

    auto [n, xr, dxr] = eve::detail::rem2(z);
    return sincos_finalize(a0, n, xr, dxr);
  }

  template<typename T,  typename N,  typename ABI, typename TAG>
  EVE_FORCEINLINE auto sinpicospi_( EVE_SUPPORTS(cpu_), TAG const & tag
                                  , eve::wide<T,N,ABI> const &a0
                                  ) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      [[maybe_unused]] auto tsc = tag(sinpicospi);

      if constexpr(is_emulated_v<ABI> )
      {
        return map(tsc, a0);
      }
      else if constexpr(is_aggregated_v<ABI> )
      {
        auto  [lo, hi]    = a0.slice();
        auto  [xhi, ehi]  = tsc(hi);
        auto  [xlo, elo]  = tsc(lo);
        return std::make_tuple(eve::combine( xlo, xhi), eve::combine( elo, ehi));
      }
      else
      {
        return internal_sinpicospi(tag, a0);
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sinpicospi simd ] - type is not an IEEEValue");
    }
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sinpicospi_(EVE_SUPPORTS(cpu_), eve::wide<T,N,ABI> const &a0) noexcept
  {
    auto x =  eve::abs(a0);
    if (all(eve::abs(x) <= T(0.25))) return restricted_(sinpicospi)(a0);
    else                             return big_(sinpicospi)(a0);
  }
}

#endif
