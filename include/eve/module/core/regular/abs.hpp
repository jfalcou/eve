//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct abs_t : elementwise_callable<abs_t, Options, accept<saturated2>>
{
  template<eve::value T>
  EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(abs_t, abs_);
};

//======================================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var abs
//!   @brief Computes the absolute value of the parameter.
//!
//!   Computes the absolute value of the parameter.
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
//!      template< eve::value T > T abs(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [SIMD or scalar arithmetic value](@ref eve::value).
//!
//!    **Return value**
//!
//!    The [elementwise](@ref glossary_elementwise) absolute value of `x`, if it is representable.
//!    More specifically, for signed integers : the absolute value of eve::valmin is not representable and
//!    the result is undefined.
//!
//!   @warning
//!   `abs` is also a standard library function name and there possibly
//!   exists a C macro version which may be called instead of the EVE version.<br/>
//!   To avoid confusion, use the eve::abs notation.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/regular/abs.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::abs[mask](x)` provides a masked version of `eve::abs` which is
//!     equivalent to `if_else (mask, abs(x), x)`.
//!
//!     **Example**
//!     @godbolt{doc/core/masked/abs.cpp}
//!
//!   * eve::saturated
//!
//!     The call `eve::abs[eve::saturated](x)` computes a saturated version of eve::abs.
//!     More specifically, for any signed integer value `x`, the expression
//!     `eve::abs[eve::saturated](eve::valmin(as(x)))` evaluates to `eve::valmax(as(x))`.
//!
//!     **Example**
//!     @godbolt{doc/core/saturated/abs.cpp}
//! @}
//======================================================================================================================
inline constexpr auto abs = functor<abs_t>;
}

#include <eve/module/core/regular/impl/abs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/abs.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/abs.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/abs.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/abs.hpp>
#endif
