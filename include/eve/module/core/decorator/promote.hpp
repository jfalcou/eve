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
struct promote_{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using promote_type = decorated<promote_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var promote
//!
//! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
//!
//! #### Synopsis
//!
//!  if promote(eve::fname) is to be called then
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
//! A @callable performing the same kind of operation but called with promoted parameters to tha
//! comon compatible type.
//!
//!  @}
//================================================================================================
[[maybe_unused]] inline constexpr promote_type const promote = {};
}
