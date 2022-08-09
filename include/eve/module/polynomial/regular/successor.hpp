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
struct successor_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using successor_type = decorated<successor_()>;

//==================================================================================================
//! @addtogroup polynomial
//! @{
//! @var successor
//!
//! @brief  Higher-order @callable imbuing incrementing behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the same kind of operation but incrementing some parameter(s) v
//!
//!  @}
//==================================================================================================
inline constexpr successor_type const successor = {};
}
