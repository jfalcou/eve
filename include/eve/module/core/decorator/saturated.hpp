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
//!   - eve::absmax,
//!   - eve::absmin,
//!   - eve::add,
//!   - eve::convert,
//!   - eve::dec,
//!   - eve::dist,
//!   - eve::div,
//!   - eve::inc,
//!   - eve::maxabs,
//!   - eve::maxmag,
//!   - eve::minabs,
//!   - eve::minmag,
//!   - eve::minus,
//!   - eve::mul,
//!   - eve::negabsmax,
//!   - eve::negabsmin,
//!   - eve::next,
//!   - eve::oneminus,
//!   - eve::prev
//!   - eve::sqr,
//!   - eve::sub.
//!
//!  @}
//================================================================================================
}
