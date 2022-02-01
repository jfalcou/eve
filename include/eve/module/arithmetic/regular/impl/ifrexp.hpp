//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/arithmetic/constant/exponentmask.hpp>
#include <eve/module/arithmetic/constant/maxexponentm1.hpp>
#include <eve/module/arithmetic/constant/nbmantissabits.hpp>
#include <eve/module/arithmetic/constant/twotonmb.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/logical_notand.hpp>
#include <eve/function/raw.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , T a0) noexcept

  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto r1   = bit_and(exponentmask(as<T>()),  a0);
      auto x    = bit_notand(exponentmask(as<T>()), a0);
      return  kumi::make_tuple( bit_or(half(eve::as<T>()), x)
                              , bit_shr(r1,nbmantissabits(eve::as<elt_t>()))
                              - maxexponentm1(eve::as<elt_t>())
                              );
    }
    else  return apply_over2(raw(ifrexp), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , T a0) noexcept

  {
    if constexpr(has_native_abi_v<T>)
    {
      auto [m, e] =  raw(ifrexp)(a0);
      auto a0eqz = is_eqz(a0);
      if constexpr(scalar_value<T>)
      {
        using i_t = as_integer_t<T>;
        if (a0eqz) return kumi::make_tuple(T(0),i_t(0));
      }
      return kumi::make_tuple(if_else(a0eqz, eve::zero, m)
                            , if_else(a0eqz, eve::zero, e)
                            );
    }
    else  return apply_over2(ifrexp, a0);
  }
}
