//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/real/core/detail/generic/multi_mul.hpp>
#include <eve/assert.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/regular.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/mul.hpp>
#include <eve/assert.hpp>

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

#include <eve/module/real/core/function/regular/generic/div_downward.hpp>
#include <eve/module/real/core/function/regular/generic/div_tonearest.hpp>
#include <eve/module/real/core/function/regular/generic/div_upward.hpp>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////////
  //== toward_zero
  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(D()(div), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), toward_zero_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( floating_real_value<T> )
        return trunc(div(a, b));
      else
      {
        EVE_ASSERT(all(a!= 0), "[eve] - div(0, 0) is undefined");
        return div(a, b);
      }
    }
    else
      return apply_over(toward_zero(div), a, b);
  }

  //================================================================================================
  //== Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto div_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::div, t, f);
  }

  template<conditional_expr C, decorator D, real_value U, real_value V>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), C const &cond, D const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, D()(div), t, f);
  }

  //================================================================================================
  //==  regular N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto div_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
    requires compatible_values<T0, T1> && (compatible_values<T0, Ts> && ...)
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    r_t that(a1);
    that = mul(that,r_t(args)...);
    EVE_ASSERT(all(is_nez(that)), "[eve] div - 0/0 is undefined");
    return div(r_t(a0), that);
  }

}

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
