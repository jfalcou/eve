//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @defgroup   simd      EVE
//! @brief  This module defines all the types and functions provided by EVE
//==================================================================================================

//==================================================================================================
//! @addtogroup simd
//! @{
//!
//!   @defgroup   simd_types  SIMD related types
//!   @brief      SIMD related types
//!
//!   Types and functions wrappers for SIMD registers and related operations
//!
//!   @defgroup   functions Functions
//!   @brief  Numerical function objects
//!
//!   This module provides all the numerical functions and function objects usable on **EVE** types.
//!
//! @}
//==================================================================================================

//==================================================================================================
//! @addtogroup simd_types
//! @{
//!   @defgroup   arch    Architecture related Types and Helpers
//!   @brief Architecture related Types and Helpers
//!
//!   This module defines the types and helpers functions to properly handle
//!    architecture specific components
//! @}
//==================================================================================================

#include <eve/as.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/version.hpp>
#include <eve/traits/cardinal.hpp>
