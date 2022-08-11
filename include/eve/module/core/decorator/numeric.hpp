//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct numeric_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using numeric_type = decorated<numeric_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var numeric
//!
//! @brief  Higher-order @callable imbuing non invalid return  preference semantic onto other
//! @callable{s}.
//!
//! #### Synopsis
//!
//!  if numeric(eve::fname) is to be called then
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
//! A @callable performing the same kind of operation but while insuring a preference to return
//! numeric values instead of Nans, whenever possible.
//!
//!  @}
//================================================================================================
inline constexpr numeric_type const numeric = {};
}
