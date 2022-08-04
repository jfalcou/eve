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
// Function decorator - splat mode
struct splat_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using splat_type = decorated<splat_()>;

//================================================================================================
//! @addtogroup core_simd
//! @{
//! @var splat
//!
//! @brief  Higher-order @callable allowing reduction to generate wide results instead of scalars.
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
//! A @callable performing the same kind of operation but returning its result as a
//! [SIMD value](@ref eve::simd_value).
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr splat_type const splat = {};
}
