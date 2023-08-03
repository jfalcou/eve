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
struct right_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using right_type = decorated<right_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var right
//!
//! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if right(eve::fname) is to be called then
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
//! A @callable performing the same kind of operation but on the right.
//! As an example:
//! horner(x, q0, q1, ...qn) (or left(horner)(x, q0, q1, ...qn)) computes
//  \f$\sum_0^n q_i*x^{n-i}\f$,
//! i.e. the left polynomial evaluation and right(horner)(x, q0, q1, ...qn)
//! computes \f$\sum_0^n x^{n-i}*q_i\f$, i.e. the right polynomial evalution
//! that are distinct if the product is not commutative as for the quaternions.
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr right_type const right = {};


struct left_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using left_type = decorated<left_()>;
[[maybe_unused]] inline constexpr left_type const left = {};
}
