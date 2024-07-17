//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct trunc_t : strict_elementwise_callable<trunc_t, Options, almost_option, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
//      static_assert( valid_tolerance<T, Options>::value, "[eve::trunc] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v);
    }

    template<eve::value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const noexcept
    {
//      static_assert( valid_tolerance<T, Options>::value, "[eve::trunc] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(trunc_t, trunc_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var trunc
//!   @brief `elementwise_callable` object computing  the integral part of `x` with the same sign as  `x`.
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
//!      // Regular overload
//!      constexpr auto trunc(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto trunc[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto trunc[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto trunc[almost = tol](floating_value auto x)   noexcept; // 3
//!      constexpr auto trunc[almost](floating_value auto x)         noexcept; // 4
//!      constexpr auto trunc[raw](floating_value auto x)            noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :[value](@ref value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!     * `tol` [scalar_value](@ref value) tolerance.
//!
//!   **Return value**
//!
//!     1. The integral part of `x` with the same sign as  `x`.
//!        The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!        `FE_TOWARDZERO`. This function object implements the `FE_TOWARDZERO` version.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. `almost` allows a fuzzy interpretation of ceil associated to a scalar tolerance.
//!         - with an integral value `tol`: computes the ceil of the previous nth
//!           representable value in the `x` type.
//!         - with a floating  value `tol`: computes the ceil with a tolerance `tol`.
//!     4. with no tolerance value, the call is equivalent to `ceil[tolerance = 3*eps(as(x))(x)`
//!     5. Faster for floating inputs, but only correct if as an integer, the truncation  that can be
//!        exactly represented in the associated integral type.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/trunc)
//! @}
//================================================================================================
  inline constexpr auto trunc = functor<trunc_t>;
}

#include <eve/module/core/regular/impl/trunc.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/trunc.hpp>
#endif
