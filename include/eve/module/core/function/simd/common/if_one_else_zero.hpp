//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/is_nez.hpp>
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
           eve::callable_one_ const &,
           eve::callable_zero_ const &) noexcept requires(T, vectorized<T>)
  {
    return if_else(cond, One<T>(), zero_);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_one_ const &,
           eve::callable_zero_ const &) noexcept requires(T, vectorized<T>)
  {
    return if_else(is_nez(cond), One<T>(), eve::zero_);
  }

  template<typename TARGET, typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           as_<TARGET> const &,
           logical<T> const &cond,
           eve::callable_one_ const &,
           eve::callable_zero_ const &) noexcept requires(TARGET, vectorized<TARGET>)
  {
    return if_else(cond, One<TARGET>(), eve::zero_);
  }

  template<typename TARGET, typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           as_<TARGET> const &,
           T const &cond,
           eve::callable_one_ const &,
           eve::callable_zero_ const &) noexcept requires(TARGET, vectorized<TARGET>)
  {
    return if_else(is_nez(cond), One<TARGET>(), eve::zero_);
  }

}

#endif
