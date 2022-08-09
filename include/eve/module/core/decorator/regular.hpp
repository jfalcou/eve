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
//================================================================================================
// Function decorators mark-up used in function overloads
struct regular_type : decorator_
{
  template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
  {
    return [f](auto&&...args) { return f(EVE_FWD(args)...); };
  }
};

//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var regular
//!
//! @brief  Higher-order @callable having identity semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  #include <eve/module/core.hpp>
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! #### Members Functions
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  auto operator()(eve::callable auto const& f ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//! @param f
//! An instance of eve::callable
//!
//! @return
//! The same @callable as input.
//!
//!  @}
//================================================================================================
inline constexpr regular_type const regular = {};
}
