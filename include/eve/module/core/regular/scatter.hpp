//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/memory.hpp>
#include <eve/traits/overload.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct scatter_t : callable<scatter_t, Options, relative_conditional_no_alternative_option>
{
  template<simd_value T, integral_simd_value Idx, simd_compatible_ptr<T> Ptr>
  EVE_FORCEINLINE void operator()(T const& v, Ptr ptr, Idx const& idx) const noexcept { EVE_DISPATCH_CALL(v,ptr,idx); }

  EVE_CALLABLE_OBJECT(scatter_t, scatter_);
};

//======================================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var scatter
//!   @brief
//!
//!   @groupheader{Header file}
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
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [SIMD or scalar arithmetic value](@ref eve::value).
//!
//!    **Return value**
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/regular/scatter.cpp}
//!
//! @}
//======================================================================================================================
inline constexpr auto scatter = functor<scatter_t>;
}

#include <eve/module/core/regular/impl/scatter.hpp>

// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/module/core/regular/impl/simd/x86/scatter.hpp>
// #endif

// #if defined(EVE_INCLUDE_POWERPC_HEADER)
// #  include <eve/module/core/regular/impl/simd/ppc/scatter.hpp>
// #endif

// #if defined(EVE_INCLUDE_ARM_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/neon/scatter.hpp>
// #endif

// #if defined(EVE_INCLUDE_SVE_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/sve/scatter.hpp>
// #endif
