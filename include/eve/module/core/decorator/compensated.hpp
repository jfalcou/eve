//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
struct compensated_
{
  template<auto N> static constexpr auto combine(decorated<diff_<N>()> const&) noexcept
  {
    return decorated<diff_<N>(compensated_)> {};
  }
};

using compensated_type = decorated<compensated_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var compensated
//!
//! @brief  Higher-order @callable imbuing more more accuracy onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if compensated(eve::fname) is to be called then
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
//! A @callable performing the same kind of operation but ensuring a higher accuracy.
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr compensated_type const compensated = {};
}
