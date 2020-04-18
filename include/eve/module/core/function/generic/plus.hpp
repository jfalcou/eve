//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_PLUS_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE  auto plus_(EVE_SUPPORTS(cpu_)
                            , T const &a) noexcept
  requires compatible_values<T, U>
  {
    return a;
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_),
                            T const &v0,
                            U const &v1) noexcept
  requires compatible_values<T, U>
  {
    return add(a, b);
  }

  template<real_value T, real_value U, value COND>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_),
                            COND const & cond,
                            T const &v0,
                            U const &v1) noexcept
  requires compatible_values<T, U>
  {
    return add[cond](a, b);
  }

  template<real_value T, real_value U, value COND,  typename D>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_),
                            COND const & cond,
                            D const &
                            T const &v0,
                            U const &v1) noexcept
  requires compatible_values<T, U>
  {
    return D()(add[cond])(a, b);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<simd_value T>
  EVE_FORCEINLINE auto operator+(T const &v) noexcept
  {
    return v;
  }
#endif
