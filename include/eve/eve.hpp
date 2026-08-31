//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//======================================================================================================================
//! @defgroup eve_simd      EVE
//! @brief  This module defines all the types and functions provided by EVE
//======================================================================================================================

//======================================================================================================================
//! @addtogroup eve_simd
//! @{
//!
//!   @defgroup eve_simd_types  SIMD related types
//!   @brief      SIMD related types
//!
//!   Types and functions wrappers for SIMD registers and related operations
//!
//!   @defgroup eve_functions Functions
//!   @brief  Numerical function objects
//!
//!   This module provides all the numerical functions and function objects usable on **EVE** types.
//!
//! @}
//======================================================================================================================

//======================================================================================================================
//! @defgroup eve_simd_concepts SIMD Concepts
//! @brief Provides Concepts for SIMD related components
//======================================================================================================================

//======================================================================================================================
//! @brief  EVE Main Namespace
//!
//! This namespace contains all the elements required to use EVE
//======================================================================================================================
namespace eve {}

//======================================================================================================================
//! @defgroup eve_arch Architecture related Types and Helpers
//! @brief Architecture related Types and Helpers
//!
//! This module defines the types and helpers functions to properly handle architecture specific components
//======================================================================================================================

#include <eve/module/core.hpp>
#include <eve/version.hpp>
