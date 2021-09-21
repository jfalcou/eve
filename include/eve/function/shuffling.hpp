//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup shuffling Shuffling and Swizzling
//!
//! These functions provide functions to reorder the elements of one or more SIMD types.
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/shuffling.hpp> @endcode
//!
//!@}
//================================================================================================
#include <eve/function/broadcast.hpp>
#include <eve/function/broadcast_group.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/slide_right.hpp>
#include <eve/function/swap_adjacent_groups.hpp>
