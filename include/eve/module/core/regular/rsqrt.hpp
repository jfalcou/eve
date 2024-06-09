//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


namespace eve
{
  template<typename Options>
  struct rsqrt_t : elementwise_callable<rsqrt_t, Options, raw_option, pedantic_option>
  {
    template<eve::floating_value T>
    requires(eve::same_lanes_or_scalar<T>)
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(rsqrt_t, rsqrt_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rsqrt
//!   @brief Computes the inverse of the square root of the parameter.
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
//!      template< eve::floating_value T >
//!      T rsqrt(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::floatingvalue) argument.
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    inverse of the square root of `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rsqrt.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::rsqrt[mask](x)` provides a masked version of `eve::rsqrt` which is
//!     equivalent to `if_else (mask, rsqrt(x), x)`.
//!
//!   * eve::raw
//!
//!     The call `rsqr[raw](x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return. Otherwise it uses the non-decorated call.
//!
//! @}
//================================================================================================
  inline constexpr auto rsqrt = functor<rsqrt_t>;
}

#include <eve/module/core/regular/impl/rsqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rsqrt.hpp>
#endif
