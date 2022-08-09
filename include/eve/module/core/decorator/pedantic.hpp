//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
template<auto Param> struct diff_;
//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct pedantic_
{
  template<auto N> static constexpr auto combine(decorated<diff_<N>()> const&) noexcept
  {
    return decorated<diff_<N>(pedantic_)> {};
  }
};

using pedantic_type = decorated<pedantic_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var pedantic
//!
//! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if pedantic(eve::fname) is to be called then
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  #include <eve/module/core.hpp>
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!  must be included.
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
//! A @callable performing the same kind of operation but while insuring compatibility with
//! the standard in corner cases, whenever possible.
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr pedantic_type const pedantic = {};
}
