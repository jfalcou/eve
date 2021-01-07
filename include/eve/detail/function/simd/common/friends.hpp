//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    if constexpr(is_native_v<ABI>)
    {
      auto that = v;
      that ^= allbits(eve::as(v));
      return that;
    }
    else
    {
      return apply_over([]<typename E>(E const& e) { return E(~e); }, v);
    }
  }

  //================================================================================================
  template<real_simd_value Wide>
  EVE_FORCEINLINE auto self_lognot(Wide const& v) noexcept
  {
    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr( is_logical_v<Wide> )  return bit_cast(~v.bits(), as_<Wide>{});
      else                                return v != 0;
    }
    else
    {
      return apply_over([]<typename E>(E const& e){ return as_logical_t<E>(!e); }, v);
    }
  }
}
