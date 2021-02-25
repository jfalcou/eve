//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/top_bits.hpp>
#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>

namespace eve::detail
{

  template<real_scalar_value T, typename N, arm_abi ABI, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(
    EVE_SUPPORTS(neon128_), C const &cond, logical<wide<T, N, ABI>> const &v0) noexcept
  {

         if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr ( N() * sizeof(T) <= 4 )              return first_true(top_bits{v0, cond});
    // for chars better do any first
    else if constexpr ( sizeof(T) == 1 )                    return first_true_(EVE_RETARGET(cpu_), cond, v0);
    else if constexpr ( std::same_as<ABI, arm_64_> )
    {
      // top bits for anything but chars on asimd are optimal for 8 byte registers
      // but without it we better do any first
      if constexpr ( eve::current_api >= eve::asimd )       return first_true(top_bits{v0, cond});
      else                                                  return first_true_(EVE_RETARGET(cpu_), cond, v0);
    }
    // On arm v7 any will cast to a half type anyway, but on asimd it won't
    else if ( eve::current_api >= eve::asimd )              return first_true_(EVE_RETARGET(cpu_), cond, v0);
    else
    {
      using half_e_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto halved = eve::convert(v0, eve::as_<eve::logical<half_e_t>>{});
      return eve::first_true[cond](halved);
    }
  }
}
