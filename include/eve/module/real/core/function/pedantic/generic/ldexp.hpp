//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/any.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T a
                             , U b) noexcept
  requires(std::same_as<element_type_t<T>, element_type_t<U>>)
  {
    return pedantic(ldexp)(a, int_(trunc(b)));
  }

  template<floating_real_value T, integral_real_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , pedantic_type const &
                               , T a
                               , U b) noexcept
  {
    if constexpr(floating_real_scalar_value<T> && integral_simd_value<U>)
    {
      using i_t =  as_integer_t<T>;
      using w_t =  wide<T,  cardinal_t<U>>;
      auto bb = convert(b, as<i_t>());
      w_t aa(a);
      return pedantic(ldexp)(aa, bb);
    }
    else if constexpr(floating_real_simd_value<T> && integral_scalar_value<U>)
    {
      using elt_t = element_type_t<T>;
      using i_t =  as_integer_t<elt_t>;
      using wi_t = wide<i_t, cardinal_t<T>>;
      i_t bb = convert(trunc(b), as<i_t>());
      return pedantic(ldexp)(a, wi_t(bb));
    }
    else
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
      {
        using elt_t = element_type_t<T>;
        auto denormal =  is_less(b, minexponent(eve::as<elt_t>()));
        auto f = one(eve::as<T>());
        if (eve::any(denormal))
        {
          if constexpr( eve::platform::supports_denormals)
          {
            b = sub[denormal]( b, decltype(b)(minexponent(eve::as<elt_t>())));
            f = if_else(denormal, smallestposval(eve::as<elt_t>()), eve::one);
          }
          auto test = (b == decltype(b)(limitexponent(eve::as<elt_t>())));
          f = inc[test](f);
          b = dec[test](b);
          b += maxexponent(eve::as<elt_t>());
          b <<=  nbmantissabits(eve::as<elt_t>());
          return a*bit_cast(b, as(T()))*f;
        }
        else return ldexp(a, b);
      }
      else  return apply_over(pedantic(ldexp), a, b);
    }
  }
}
