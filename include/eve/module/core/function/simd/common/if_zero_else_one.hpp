//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/is_nez.hpp>
//#include "if_zero_else.hpp"
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           logical<T> const &cond,
           eve::callable_zero_ const &,
           eve::callable_one_ const &) noexcept requires(T, vectorized<T>)
  {
    return if_else(cond, zero_, One<T>());
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_zero_ const &,
           eve::callable_one_ const &) noexcept requires(T, vectorized<T>)
  {
    return if_else(is_nez(cond), eve::zero_, One<T>());
  }

  template<typename TARGET, typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           as_<TARGET> const &,
           T const &cond,
           eve::callable_zero_ const &,
           eve::callable_one_ const &) noexcept requires(TARGET, vectorized<TARGET>)
  {
    return if_else(cond, eve::zero_, One<TARGET>());
  }
}

#endif
