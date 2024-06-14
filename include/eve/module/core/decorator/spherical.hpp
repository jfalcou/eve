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
struct spherical_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using spherical_type = decorated<spherical_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var spherical
//!
//! @brief  Higher-order @callable imbuing spherical semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if spherical(eve::fname) is to be called then
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
//! A @callable performing the same kind of operation but implying sphericalerical semantic.
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr spherical_type const spherical = {};
}
