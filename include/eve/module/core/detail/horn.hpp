//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
template<typename T>
EVE_FORCEINLINE constexpr auto
horn(T const&) noexcept
{
  return eve::zero(eve::as<T>());
}

template<typename T, auto Coef>
EVE_FORCEINLINE constexpr auto
horn(T const&) noexcept
{
  using t_t = element_type_t<T>;
  return T(eve::Constant<t_t, Coef>());
}

template<typename T, auto Coef0, auto Coef1, auto... Args>
EVE_FORCEINLINE constexpr auto
horn(T const& x) noexcept
{
  using t_t = element_type_t<T>;
  return eve::fma(x, horn<T, Coef1, Args...>(x), T(eve::Constant<t_t, Coef0>()));
}
}
