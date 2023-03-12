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
struct compensated_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
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
