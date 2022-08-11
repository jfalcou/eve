/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var combine
//!   @brief Computes the TODO
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      TODO
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
//!
//!    **Return value**
//!
//!      * TODO
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/combine.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(combine_, combine);
}

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE auto
combine_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return as_wide_t<T, typename cardinal_t<T>::combined_type>(a, b);
}
}
