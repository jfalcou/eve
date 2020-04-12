//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_SELECT_HPP_INCLUDED

#include <eve/forward.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires bit_compatible_values<T,U> && bit_compatible_values<T,V>
  {
    return bit_call(bit_select, a, b, c);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  {
    return eve::bit_or(eve::bit_and(b, a), eve::bit_andnot(c, a));
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto bit_select_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  {
    return  bit_or(bit_and(b, a), bit_andnot(c, a)); // fallback never taken if proper intrinsics are at hand
  }

   template<real_simd_value T>
  EVE_FORCEINLINE logical<T> bit_select_(EVE_SUPPORTS(cpu_)
                                  , logical<T> const &a
                                  , logical<T> const &b
                                  , logical<T> const &c) noexcept
  {
    return bit_cast(bit_or(bit_and(b.bits(), a.bits()), bit_andnot(c.bits(), a.bits())), as(logical<T>()));
  }

}

#endif
