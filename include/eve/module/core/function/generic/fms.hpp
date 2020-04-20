//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FMS_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/add.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
#include <type_traits>
#include <eve/concept/compatible.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fms_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires compatible_values<T,U> && compatible_values<T,V>
  {
    return arithmetic_call(fms, a, b, c);
  }

  template<real_value T, real_value U, real_value V, typename D>
  EVE_FORCEINLINE auto fms_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires compatible_values<T,U> && compatible_values<T,V>
  {
    return arithmetic_call(D()(fms), a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE T fms_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return fma(a, b, T(-c));
  }

  template<real_value T, typename D>
  EVE_FORCEINLINE auto fms_(EVE_SUPPORTS(cpu_)
                                  , D const &
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return D()(fma)(a, b, T(-c));
  }
}

#endif
