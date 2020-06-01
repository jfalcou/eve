//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_FUNCTION_GENERIC_REMPIO2_HPP_INCLUDED
#define EVE_MODULE_MATH_FUNCTION_GENERIC_REMPIO2_HPP_INCLUDED

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/scalar/rempio2_kernel.hpp>
#include <eve/module/math/detail/simd/rempio2_kernel.hpp>

#include <tuple>
#include <type_traits>

namespace eve::detail
{
  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto rempio2_(EVE_SUPPORTS(cpu_), D const &deco, T const &xx) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( std::is_same_v<D, eve::small_type> )
      {
        return rempio2_small(xx);
      }
      else if constexpr( std::is_same_v<D, eve::medium_type> )
      {
        return rempio2_medium(xx);
      }
      else if constexpr( std::is_same_v<D, eve::big_type> )
      {
        return rempio2_big(xx);
      }
      else if constexpr( std::is_same_v<D, eve::regular_type> )
      {
        return rempio2(xx);
      }
    }
    else
      return apply_over3(D()(rempio2), xx);
  }

  template<floating_value T> EVE_FORCEINLINE auto rempio2_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if( all(x <= Rempio2_limit(restricted_type(), as(x))) )
        return std::make_tuple(T(0), x, T(0));
      else if( all(x <= Rempio2_limit(small_type(), as(x))) )
        return small_(rempio2)(x);
      else if( all(x <= Rempio2_limit(medium_type(), as(x))) )
        return medium_(rempio2)(x);
      else
        return big_(rempio2)(x);
    }
    else
      return apply_over3(rempio2, x);
  }
}

#endif
