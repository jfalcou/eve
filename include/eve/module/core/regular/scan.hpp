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
//! @addtogroup core
//! @{
//! @var scan
//!
//! @brief Callable object computing a generalized scan operation.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! #### Member Functions
//!
//! | Member       | Effect                                          |
//! |:-------------|:------------------------------------------------|
//! | `operator()` | the computation of a generalized scan operation |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template<simd_value T, Callable F, typename Zero>
//!  auto operator()( T v, F binary_op, Zero zero ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//! `v`:   [simd value](@ref eve::simd_value) to scan.
//!
//! `binary_op`:   Binary callable object that perform a binary, commutative and associative
//! operation.
//!
//! `zero`  :   An identity element for `binary_op` (binary_op(zero, v) == v) for any v.
//!             Acceptable:
//!                T
//!                anything convertible to T
//!                eve::zero
//!
//! `eve::zero`
//!
//! **Return value**
//!
//! Generalized scan of `v.get(0)`, `v.get(1)`, ... `v.get(v.size()-1)` over `binary_op`,
//! T(v.get(0), binary_op(v.get(0), v.get(1)), binary_op(binary_op(v.get(0), v.get(1)), v.get(2))
//! ...)
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template<simd_value T> auto operator()( T v ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//!  Same as scan(v, eve::plus, eve::zero)
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(scan_, scan);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/scan.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/scan.hpp>
#endif
