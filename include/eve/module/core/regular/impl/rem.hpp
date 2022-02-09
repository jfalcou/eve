//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/binarize_not.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/roundings.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(rem, a, b);
  }

  template<decorator D, real_value T, real_value U>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept
  requires (compatible_values<T, U>  &&
            (is_one_of<D>(types<toward_zero_type, downward_type, upward_type
                         , downward_type,  to_nearest_type> {})))
  {
    return arithmetic_call(D()(rem), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_)
                           , T const &a
                           , T const &b) noexcept
  {
    return if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b)
                  , allbits
                  , if_else(is_eqz(a)
                           , a
                           , fnma(b, trunc(next(div(a,b))), a)
                           )
                  );
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), D const&
                            , T const &a, T const &b
                            ) noexcept
  requires  (is_one_of<D>(types<toward_zero_type, downward_type, upward_type
                         , downward_type,  to_nearest_type> {}))
  {
    if constexpr(has_native_abi_v<T>) return fnma(b, D()(eve::div)(a,b), a);
    else                              return apply_over(D()(rem), a, b);
  }
  template<floating_real_value T>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), to_nearest_type const&
                            , T const &a, T const &b
                            ) noexcept
 {
    if constexpr(has_native_abi_v<T>)
    {
      return if_else(is_eqz(b)||is_unordered(a, b)
                    ,  if_else(is_eqz(a) || is_infinite(b)
                              , a, allbits
                              )
                    , fnma(b, to_nearest(eve::div)(a,b), a)
                    ); //as remainder
    }
    else return apply_over(to_nearest(rem), a, b);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    auto g = if_else(cond, f, one);
    return mask_op(  cond, eve::rem, t, g);
  }

  template<conditional_expr C, decorator D, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), C const &cond, D const &, U const &t, V const &f) noexcept
  requires (compatible_values<V, U>  &&
            (is_one_of<D>(types<toward_zero_type, downward_type, upward_type
                         , downward_type,  to_nearest_type> {})))
  {
    auto g = if_else(cond, f, one);
    return mask_op(  cond, D()(rem), t, g);
  }
}
