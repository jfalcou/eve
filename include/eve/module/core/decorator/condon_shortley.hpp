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
struct condon_shortley_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using condon_shortley_type = decorated<condon_shortley_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var condon_shortley
//!
//! @brief  Higher-order @callable imbuing incrementation behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A modified @callable
//!
//! Actually supported by eve::legendre in module polynomial
//!
//!  @}
//================================================================================================
inline constexpr condon_shortley_type const condon_shortley = {};
}
