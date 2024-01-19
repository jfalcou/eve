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
struct associated_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using associated_type = decorated<associated_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var associated
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
//! Actually supported by eve::laguerre and legendre in module polynomial
//!
//!  @}
//================================================================================================
inline constexpr associated_type const associated = {};
}
