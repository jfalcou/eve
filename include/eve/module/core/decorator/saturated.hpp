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
//================================================================================================
// Function decorators mark-up used in function overloads
struct saturated_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using saturated_type = decorated<saturated_()>;

//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var saturated
//!
//! @brief  Higher-order @callable imbuing saturation semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if saturated(eve::fname) is to be called then
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
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the same kind of operation but while taking care of saturating
//! its return value so that it always fit into the input type range.
//!
//! saturated is currently supported by
//!
//!   - eve::abs,
//!   - eve::add,
//!   - eve::convert,
//!   - eve::dec,
//!   - eve::div,
//!   - eve::inc,
//!   - eve::mul,
//!   - eve::sub,
//!   - eve::oneminus,
//!   - eve::next,
//!   - eve::prev
//!   - eve::sqr.
//!
//!  @}
//================================================================================================
inline constexpr saturated_type const saturated = {};
}
