//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup core Core functions
//! @brief Core functions
//!
//!  This module provides implementation for various fundamental functions
//!
//! @}
//==================================================================================================
//==================================================================================================
//! @addtogroup core
//! @{
//!
//! @defgroup core_accuracy  accuracy helpers
//! @ingroup core
//! These functions allows performing some basic arithmetis operations with greater acuracy
//! even when and upgraded type is not available.
//!
//! @defgroup core_arithmetic  arithmetic operations
//! @ingroup core
//! Core arithmetic functions
//!
//! @defgroup core_bitops bitwise functions
//! @ingroup core
//! These functions are low level and acting on the bit representation of the involved datas.
//!
//! @defgroup core_constants  constants
//! @ingroup core
//! Basic useful constants (scalar and SIMD)
//!
//! @defgroup core_decorators  decorators
//! @ingroup core
//! Core semantic modifiers
//!
//! @defgroup core_fma_family  fma family
//! @ingroup core
//! These functions implements acurate versions of the operations
//! \f$\pm x \pm yz\f$ and \f$\pm xy \pm z\f$.
//!
//! The required accuracy is in two directions
//!   1. the computation is done with only one rounding
//!   2. there is no intermediate overflow
//!
//! The implementation of these two properties can always be obtained calling
//! the decorated pedantic and numeric versions of these functions.
//!
//! Take care that can be very expansive if the proper hardware capabilities are not present.
//!
//! By themselves tne regular version of these function acts the naive (and less accurate way)
//! if the intrinsics are not at hand.
//!
//! @defgroup core_horizontal  horizontal operations
//! @ingroup core
//! Operations providing a scalar value from SIMD vectors
//!
//! @defgroup core_internal  internal representation and IEEE
//! @ingroup core
//! Operations related to classical IEEE libc functions
//!
//! @defgroup core_conversions Conversions
//! @ingroup core
//! Type conversions
//!
//! @defgroup core_simd Proper SIMD operations
//! @ingroup core
//! Proper SIMD operations as shuffling, splitting and merging SIMD vectors
//! @}
//==================================================================================================

#include <eve/module/core/constant/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/detail/core.hpp>
#include <eve/module/core/regular/core.hpp>
#include <eve/module/core/fuzzy/core.hpp>
#include <eve/module/core/numeric/core.hpp>
#include <eve/module/core/pedantic/core.hpp>
#include <eve/module/core/saturated/core.hpp>
