//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @addtogroup arch
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
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/memory/stack_buffer.hpp>
