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

namespace eve
{
//================================================================================================
// Function decorators mark-up used in function overloads
struct musl_type : decorator_
{
  template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
  {
    return [f](auto&&...args) { return f(musl_type {}, EVE_FWD(args)...); };
  }
};

//================================================================================================
// Function decorator - musl mode
template<typename Function>
constexpr EVE_FORCEINLINE auto
musl_(Function f) noexcept
{
  return musl_type {}(f);
}
}
