//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @defgroup concepts Concepts
//!
//! The following concepts provide definitions of fundamental library concepts used throughout
//! **EVE** to perform compile-time validation of template arguments and perform function dispatch
//! based on properties of those types.
//!
//! Based on the general properties and reasoning style from the C++ Standard library, **EVE**
//! concepts caters to the specific needs of SIMD computations.
//!
//! **Convenience header:** @code{.cpp} #include <eve/concept.hpp> @endcode
//!
//================================================================================================

#include <eve/concept/abi.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/pattern.hpp>
#include <eve/concept/properly_convertible.hpp>
#include <eve/concept/range.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/vectorizabel.hpp>
#include <eve/concept/vectorized.hpp>
