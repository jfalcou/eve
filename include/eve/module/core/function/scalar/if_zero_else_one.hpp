//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_zero_ const &,
           eve::callable_one_ const &) noexcept requires(T, Vectorizable<T>)
  {
    return static_cast<bool>(cond) ? Zero<T>() : One<T>();
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           logical<T> const &cond,
           eve::callable_zero_ const &,
           eve::callable_one_ const &) noexcept requires(T, Vectorizable<T>)
  {
    return static_cast<bool>(cond) ? Zero<T>() : One<T>();
  }

  template<typename TARGET, typename T>
  EVE_FORCEINLINE constexpr auto if_else_(
      EVE_SUPPORTS(cpu_),
      as_<TARGET> const &,
      T const &cond,
      eve::callable_zero_ const &,
      eve::callable_one_ const &) noexcept requires(TARGET, Vectorizable<TARGET>, Vectorizable<T>)
  {
    return is_nez(cond) ? Zero<TARGET>() : One<TARGET>();
  }
}

#endif
