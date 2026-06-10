//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup special Special functions
//! @brief Special functions
//!
//! This module provides implementation for various special functions
//!
//! Most of them provide besides the regular call `raw` and `fast` options clls that are speedier but
//! with possible limitations on corner cases response, valid range and accuracy, `raw`
//! always being the most dirty.
//!
//! These version are to be used with caution.
//!
//! **Required header:** @code{.cpp} #include <eve/module/special.hpp> @endcode
//!
//! @}
//==================================================================================================

#include <eve/module/special/regular/special.hpp>
