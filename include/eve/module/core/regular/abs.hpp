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
struct abs_t : elementwise_callable<abs_t, Options, saturated_option>
{
  template<eve::value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  { return EVE_DISPATCH_CALL(v); }

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
//!      constexpr auto abs(value auto x)                           noexcept;  // 1
//!      constexpr auto abs[conditional_expr auto c](value auto x)  noexcept;  // 2.1
//!      constexpr auto abs[logical_value auto m](value auto x)     noexcept;  // 2.2
//!      constexpr auto abs[saturated](value auto x)                noexcept;  // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : [SIMD or scalar value](@ref value).
//!     * `c` : [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m` : [Logical value](logical) masking the operation.
//!
//!
//!   **Return value**
//!
//!   1. the absolute value of `x` if it is representable.
//!   2. the absolute value of `x` if it is representable only in the lanes where `c` (2.1) or `m` (2.2) is true.
//!   3. the saturated absolute value of `x`. More specifically, for signed
//!      integral, `abs[saturated](valmin(as<T>{}))` is eve:valmax(as<T>{}))
//!
//!   @note
//!      the absolute value of `x` is always representable exxcept for the minimum value of integral signed values.
//!
//!   @warning
//!   `abs` is also a standard library function name and there possibly exists a C macro version which may be called
//!    instead of the EVE version.<br/>
//!    To avoid confusion, use the eve::abs notation.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/abs.cpp}
//!
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
