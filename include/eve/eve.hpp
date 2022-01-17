//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @defgroup   functions Functions
//! @brief  This module provides all the numerical functions and function objects
//==================================================================================================

//==================================================================================================
//! @defgroup   constant  Constants
//! @brief  This module provides all the function and function objects for generating constants
//!
//! **EVE** provides callable objects able to generate the value of various constants used in
//! various settings from a [type specifier](@ref eve::as) passed as argument. The constant `name`
//! is available by using the following directive:
//! @code
//! #include <eve/constant/name.hpp>
//! @endcode
//! @groupheader{Example}
//! @godbolt{quick-start/constant.cpp}
//==================================================================================================

//==================================================================================================
//! @defgroup   arch    Architecture related Types and Helpers
//! @brief  This module defines the types and helpers functions to properly handle
//!         architecture specific components
//==================================================================================================

//==================================================================================================
//! @defgroup   simd      SIMD Types and Helpers
//! @brief  This module defines the types and helpers functions to properly handle SIMD registers
//==================================================================================================

//==================================================================================================
//! @namespace  eve       Main EVE namespace
//==================================================================================================

#include <eve/as.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/version.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/module/core.hpp>
