//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup simd_types
//! @{
//! @defgroup doublereal double_double Numbers
//! @brief double_double Numbers
//!
//!  This module provides types and functions to handle double_double numbers,  i.e.
//!  doublereal<T> is defined for floating scalar or simd types and provides floating
//!  representations  of real numbers able to handle
//!  at least 43 bits (for floats) and 106 bits of significand (for double)
//!  but with the same exponent precision that the underlying IEEE type.
//!
//! @}
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/module/doublereal/regular/doublereal.hpp>
#include <eve/module/doublereal/doublereal.hpp>
