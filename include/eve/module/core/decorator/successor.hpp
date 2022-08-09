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
//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct successor_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using successor_type = decorated<successor_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var successor
//!
//! @brief  Higher-order @callable imbuing incrementation behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the same kind of operation but incrementind some parameter(s) v
//!
//! Actually supported by eve::laguerre
//!
//!  @}
//================================================================================================
inline constexpr successor_type const successor = {};
}
