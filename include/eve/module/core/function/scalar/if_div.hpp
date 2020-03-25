//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IF_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IF_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/is_nez.hpp>
#include <type_traits>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr
  auto  div_(EVE_SUPPORTS(cpu_)
            , U const &cond
            , T const &a
            , T const &b) noexcept
  Requires( T, Vectorizable<T>, Vectorizable<U> )
  {
    return is_nez(cond) ? a/b : a;
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated Masked case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_)
                                     , U const & cond
                                     , saturated_type const &
                                     , T const &a
                                     , T const &b) noexcept
  Requires(T, Vectorizable<T>, Vectorizable<U>)
  {
    auto tst = is_nez(cond);
    if constexpr(std::is_floating_point_v<T>) return  tst ? a/b : a;
    else return tst ? saturated_(div)(a, b) : a;
  }
}

#endif
