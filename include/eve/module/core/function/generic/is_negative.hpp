//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NEGATIVE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NEGATIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/meta/traits.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_negative_(EVE_SUPPORTS(cpu_)
                                             , T const &v) noexcept
  {
    if constexpr(unsigned_value<T>)        return False(as(v));
    else if constexpr(native<T>)
    {
     if constexpr(signed_integral_value<T>) return is_ltz(v);
      else if constexpr(simd_value<T>)
      {
        using elt_t =  element_type_t<T>;
        using swi_t = as_wide_t<eve::detail::as_integer_t<elt_t, signed>, cardinal_t<T>>;
        using lwi_t = as_logical_t<as_wide_t<elt_t, cardinal_t<T>>>;
        return bit_cast(is_ltz(bit_cast(v,as_<swi_t>())), as_<lwi_t>());
      }
      else
      {
        using si_t = eve::detail::as_integer_t<T, signed>;
        return bit_cast(is_ltz(bit_cast(v,as_<si_t>{})), as_<as_logical_t<T>>{});
      }
    }
    else return apply_over(is_negative, v);
  }
}

#endif
