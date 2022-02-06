//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


#include <eve/module/core.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/constant/maxexponent.hpp>
#include <eve/module/core/constant/nbmantissabits.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <string>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  requires(std::same_as<element_type_t<T>, element_type_t<U>>)
  {
    return ldexp(a, int_(trunc(b)));
  }

  template<floating_real_scalar_value T, integral_scalar_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  {
    auto ik =  int(b)+maxexponent(eve::as<T>());
    ik <<= nbmantissabits(eve::as<T>());
    return a*bit_cast(ik,as<T>());
  }

  template<floating_real_scalar_value T, integral_simd_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  {
   using i_t =  as_integer_t<T>;
    using w_t =  wide<T,  cardinal_t<U>>;
    auto bb = convert(b, as<i_t>());
    auto ik =  bb + i_t(maxexponent(eve::as<T>()));
    ik <<= nbmantissabits(eve::as<T>());
    return a*bit_cast(ik, as<w_t>());
  }

  template<floating_real_simd_value T, integral_scalar_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  {
    using elt_t = element_type_t<T>;
    using i_t =  as_integer_t<elt_t>;
    i_t bb = convert(trunc(b), as<i_t>());
    auto ik =  bb+maxexponent(eve::as<T>());
    ik <<= nbmantissabits(eve::as<T>());
    return a*bit_cast(ik, as<T>());
  }

  template<floating_real_simd_value T, integral_simd_value U>
  EVE_FORCEINLINE auto ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  requires (cardinal_v<T> == cardinal_v<U>)
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      using elt_t = element_type_t<T>;
      auto ik =  b+maxexponent(eve::as<elt_t>());
      ik <<= nbmantissabits(eve::as<elt_t>());
      return a*bit_cast(ik, as<T>());
    }
    else
    {
      return apply_over(ldexp, a, b);
    }
  }

  template<conditional_expr C, floating_real_value T0, real_value T1>
  auto ldexp_(EVE_SUPPORTS(cpu_), C const &cond, T0 a0, T1 a1)
  requires floating_value<common_compatible_t<T0, T1>>
  {
   return mask_op(  cond, ldexp, a0, a1);
  }

}
