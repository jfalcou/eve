//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/convert.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_less_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_less, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto is_less_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return as_logical_t<T>(a < b);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto is_less_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    std::cout << "ccccccccccc" << std::endl;
    return apply_over(is_less, a, b);
  }

  template<real_simd_value T, real_simd_value U>
  EVE_FORCEINLINE  auto is_less_(EVE_SUPPORTS(cpu_)
                                , T const &a
                                , U const &b) noexcept
  requires (size_compatible_values<T, U>)
    && (sizeof(element_type_t<T>)!= sizeof(element_type_t<U>)) =  delete;
//   {

//     if constexpr(std::is_signed_v<element_type_t<T>> != std::is_signed_v<element_type_t<U>>)
//     {
//       static_assert(std::is_signed_v<element_type_t<T>> == std::is_signed_v<element_type_t<U>>
//                     , "[eve::is_less] - comparison of different signedness parameters");
//     }
//     if constexpr(sizeof(T) >  sizeof(U))
//     {
//       return  arithmetic_call(is_less, a, convert(b, as<element_type_t<T>>()));
//     }
//     else
//     {
//       return  arithmetic_call(is_less, convert(a, as<element_type_t<U>>()), b);
//     }
//   }
}

namespace eve
{
  template<value T, value U>
  EVE_FORCEINLINE auto operator <(T const &v0, U const &v1) noexcept
  -> decltype( eve::is_less(v0,v1) )
  requires (compatible_values<T, U>)
  {
    return eve::is_less(v0, v1);
  }

  template<real_simd_value T, real_simd_value U>
  EVE_FORCEINLINE  auto operator <(T const &a
                                  , U const &b) noexcept
  requires (size_compatible_values<T, U>)
    && (sizeof(element_type_t<T>)!= sizeof(element_type_t<U>)) =  delete;

}
