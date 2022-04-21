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
//! @defgroup compensated Compensated function
//! @brief Compensated functions
//!
//! This module provides implementation of some compensated algorithms.
//!
//! these algoritms are mainly summations algorithms on ranges that ensure better accuracy without
//! using extended registers to perform computations.
//! All these algorithm expect an IEEE conformant floting point implementation.
//!
//! **Required header:** @code{.cpp} #include <eve/module/compensated.hpp> @endcode
//!
//! @}
//==================================================================================================
#include <eve/module/compensated/decorator/compensated.hpp>
#include <eve/module/compensated/regular/compensated.hpp>
