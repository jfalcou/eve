//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/max.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto maxmag_(EVE_SUPPORTS(cpu_)
                                        , T const &a0
                                        , T const &a1) noexcept
  requires(T, Vectorizable<T>)
  {
    auto aa0 = eve::abs(a0);
    auto aa1 = eve::abs(a1);
      return aa0 < aa1 ? a1 : aa1 <  aa0 ? a0 : eve::max(a0, a1);
  }

  // -----------------------------------------------------------------------------------------------
  // Pedantic case
  template<typename T>
  EVE_FORCEINLINE constexpr auto maxmag_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T const &a0
                                        , T const &a1) noexcept
  requires(T, Vectorizable<T>)
  {
      auto aa0 = eve::abs(a0);
      auto aa1 = eve::abs(a1);
      return aa0 < aa1 ? a1 : aa1 <  aa0 ? a0 : eve::pedantic_(eve::max)(a0, a1);
  }

  // -----------------------------------------------------------------------------------------------
  // numeric case
  template<typename T>
  EVE_FORCEINLINE constexpr auto maxmag_(EVE_SUPPORTS(cpu_)
                                        , numeric_type const &
                                        , T const &a0
                                        , T const &a1) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      if (is_nan(a0)) return a1;
    return maxmag(a0, a1);
  }
}

#endif
