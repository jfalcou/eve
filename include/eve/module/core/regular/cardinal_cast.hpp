//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup memory
//! @{
//!   @var cardinal_cast
//!
//!   @brief Fundamental operation for pointer-like (TODO: concept) - producing a different pointer-like
//!   with a smaller alignment requirement
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Pointer-like, have some minimal alignment requirement associated with them. Often we need to relax
//!   it. The interface allows to pass a bigger new alignment requirement, but that a noop.
//!   algo uses this as a customization point.
//!
//!   @code
//!   template <typename I, typename N>
//!   cardinal_cast(I ptr, N)
//!   @endcode
//!
//!   Parameters:
//!    * ptr - input pointer like
//!    * N - cardinal (eve::fixed)
//!
//!   Return value:
//!    * std::contigious_iterator - returns itself
//!    * For an aligned_ptr - returns unalign(ptr)
//!    * For soa_ptr - applies to each field
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(cardinal_cast_, cardinal_cast);

//================================================================================================
//! @addtogroup memory
//! @{
//!  @typedef cadinal_cast_t
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @code
//!   template <typename T, typename N>
//!   using cardinal_cast_t = decltype(cardinal_cast(std::declval<T>(), N{}));
//!   @endcode
//================================================================================================
template<typename T, typename N> using cardinal_cast_t = decltype(cardinal_cast(std::declval<T>(), N{}));

}
