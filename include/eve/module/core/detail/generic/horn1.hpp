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

#include <eve/detail/overload.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/abi.hpp>
#include <cmath>

namespace eve::detail
{
  template < typename T>
  EVE_FORCEINLINE constexpr T horn1(T) noexcept
  {
    return eve::One<T>();
  }
  
  template < typename T,  auto Coef>
  EVE_FORCEINLINE constexpr T horn1(const T & x) noexcept
  {
    using t_t = detail::value_type_t<T>;
    return x +  eve::Constant<t_t, Coef>();
  }
  
  template < typename T, auto Coef0, auto Coef1, auto... Args>
  EVE_FORCEINLINE constexpr T horn1(const T & x) noexcept
  {
    using t_t = detail::value_type_t<T>;
    return eve::fma(x, horn1 < T, Coef1, Args...>(x),  eve::Constant<t_t, Coef0>());
  }
}

