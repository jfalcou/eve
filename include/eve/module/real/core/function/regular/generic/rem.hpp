//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize_not.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/decorator.hpp>
#include <eve/function/trunc.hpp>
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
  requires compatible_values<T, U>
  {
    return arithmetic_call(D()(rem), a, b);
  }


//   template<real_value T, real_value U>
//   EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_)
//                             , pedantic_type const&,T const &a, U const &b
//                             ) noexcept requires compatible_values<T, U>
//   {
//     return if_else(is_nez(b), rem(a,b), a);
//   }

  template<floating_real_value T>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_)
                           , T const &a
                           , T const &b) noexcept
  {
    std::cout << "+++++++++++++++++++++" << std::setprecision(15) << std::endl;
    std::cout << "a " << a << std::endl;
    std::cout << "b " << b << std::endl;
    std::cout << "d(div)(a, b)  " << trunc(div(a, b)) << std::endl;
    std::cout << "rem           " << fnma(b, trunc(div(a,b)), a)<< std::endl;
    std::cout << "=====================" << std::endl;
    return fnma(b, trunc(div(a,b)), a);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), D const&
                            , T const &a, T const &b
                            ) noexcept
  requires has_native_abi_v<T>
  {
    return fnma(b, D()(eve::div)(a,b), a);
  }


  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::rem, t, f);
  }

  template<conditional_expr C, decorator D, real_value U, real_value V>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), C const &cond, D const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, D()(rem), t, f);
  }
}
