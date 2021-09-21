//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @addtogroup simd
//! @{
//! @defgroup memory Memory Management
//!
//! **EVE** provides various element to simplify the management of SIMD-compatible memory like
//! functions and allocators for requesting SIMD-compatible block of memory, pointer wrapper
//! to discriminate aligned memory from regular one, and alignment computation functions.
//!
//! **Convenience header:** @code{.cpp} #include <eve/memory.hpp> @endcode
//!
//! @}
//================================================================================================

#include <eve/memory/align.hpp>
#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_dealloc.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/power_of_2.hpp>
