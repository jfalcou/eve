//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EPS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EPS_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/min.hpp>
#include <eve/function/add.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  {
    if constexpr(floating_value<T>)
    {
      if constexpr(has_native_abi_v<T>)
      {
        auto a = eve::abs(a0);

        if constexpr(eve::platform::supports_denormals && scalar_value<T>)
        {
          auto altspv = is_less(a, Smallestposval<T>());
          if (altspv) return Mindenormal<T>();
        }

        using i_t = as_integer_t<T>;
        using v_t = value_type_t<T>;

        auto e1 = exponent(a)-Nbmantissabits<T>();
        auto e = bit_cast(bit_cast(T(1), as<i_t>())+(shl(e1,Nbmantissabits<v_t>())), as<T>());
        e =  add[is_not_finite(a)](e, Nan<T>());

        if constexpr(eve::platform::supports_denormals && simd_value<T>)
        {
          auto altspv = is_less(a, Smallestposval<T>());
          return if_else(altspv, Mindenormal<T>(), e);
        }
        else
        {
          return e;
        }
      }
      else
      {
        return apply_over(eps, a0);
      }
    }
    else if constexpr(integral_value<T>) return T(1);
  }
}

#endif
