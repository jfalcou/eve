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
// Rounding decorator objects
struct upward_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  static constexpr auto value = 0x02 | 0x08; //_MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC;
};

struct downward_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  static constexpr auto value = 0x01 | 0x08; //_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC;
};

struct to_nearest_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  static constexpr auto value = 0x00 | 0x08; // _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC;
};

struct toward_zero_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
  static constexpr auto value = 0x03 | 0x08; // _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC;
};

//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var upward
//!
//! @brief  Higher-order @callable imbuing upward rounding semantic onto other @callable{s}.
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
//! A @callable performing the same kind of operation but rounding the result upward
//! or, in other words, to positive infinity
//!
//!
//!   - eve::div,
//!   - eve::fracscale
//!   - eve::rem
//!   - eve::round,
//!   - eve::roundscale.
//!
//!  @}
//================================================================================================
using upward_type = decorated<upward_()>;

//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var downward
//!
//! @brief  Higher-order @callable imbuing rounding downard semantic onto other @callable{s}.
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
//! A @callable performing the same kind of operation but rounding the result upward
//! or,  in other words, to negative infinity
//!
//!   - eve::div,
//!   - eve::fracscale
//!   - eve::rem
//!   - eve::round,
//!   - eve::roundscale.
//!
//!  @}
//================================================================================================
using downward_type = decorated<downward_()>;

//! @addtogroup core_decorators
//! @{
//! @var to_nearest
//!
//! @brief  Higher-order @callable imbuing rounding to nearest semantic onto other @callable{s}.
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
//! A @callable performing the same kind of operation but rounding the result to the nearest integer
//! (half integers are rounded to even)
//!
//!   - eve::div,
//!   - eve::fracscale
//!   - eve::rem
//!   - eve::round,
//!   - eve::roundscale.
//!
//!  @}
//================================================================================================
using to_nearest_type = decorated<to_nearest_()>;

//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var toward_zero
//!
//! @brief  Higher-order @callable imbuing rounding toward zero semantic onto other @callable{s}.
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
//! A @callable performing the same kind of operation but truncating the result
//! or,  in other words, rounding toward zero
//!
//!   - eve::div,
//!   - eve::fracscale
//!   - eve::rem
//!   - eve::round,
//!   - eve::roundscale.
//!
//!  @}
//================================================================================================
using toward_zero_type = decorated<toward_zero_()>;

inline constexpr upward_type const      upward      = {};
inline constexpr downward_type const    downward    = {};
inline constexpr to_nearest_type const  to_nearest  = {};
inline constexpr toward_zero_type const toward_zero = {};
}
