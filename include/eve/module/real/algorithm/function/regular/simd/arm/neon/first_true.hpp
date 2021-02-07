//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE
  Copyright 2021 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>


namespace eve::detail
{

  template<real_scalar_value T, typename N, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(
    EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, arm_128_>> const &v0) noexcept
  {
    // We override the top_bits implementation here
    // because any will cast to smaller type anyways
         if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr ( sizeof(T) >= 2 )
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return eve::first_true[cond](halved);
    }
    else
    {
      // For chars on arm-v7 I am not sure what's the best approach is
      //  - will stick with default.
      return detail::first_true_(EVE_RETARGET(cpu_), cond, v0);
    }
  }
}
