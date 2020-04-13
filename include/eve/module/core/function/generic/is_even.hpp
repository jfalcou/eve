//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_even_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_even_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_even_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto aisflt = is_flint(a * Half(as(a)));
        auto aa = eve::abs(a);
        if constexpr(eve::platform::supports_denormals)
          return aisflt && (aa != Mindenormal<T>());
        else
          return aisflt && (aa != Smallestposval<T>());
      }
      else if constexpr(scalar_value<T>) return (!(a & One(as(a))));
      else                               return is_eqz((a & One(as(a))));
    }
    else                                 return apply_over(is_even, a);
  }
}

#endif
