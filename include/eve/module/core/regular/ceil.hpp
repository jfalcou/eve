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
  struct ceil_t : strict_elementwise_callable<ceil_t, Options, almost_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
      //     static_assert( valid_tolerance<T, Options>::value, "[eve::ceil] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v);
    }

    template<eve::value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const noexcept
    {
      //      static_assert( valid_tolerance<T, Options>::value, "[eve::ceil] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(ceil_t, ceil_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var ceil
//!   @brief `elementwise_callable` object computing the smallest integer not less than the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @codeabs
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto ceil(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ceil[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto ceil[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto ceil[almost = tol](floating_value auto x)   noexcept; // 3
//!      constexpr auto ceil[almostl](floating_value auto x)        noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :[value](@ref value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!     * `tol' [scalar_value](@ref value) tolerance.
//!
//!   **Return value**
//!
//!     1. The smallest integer not less than `x`.
//!        The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!        `FE_TOWARDZERO`. This function object implements the `FE_UPWARD` version.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. `almost` allows a fuzzy interpretation of ceil associated to a scalar tolerance.
//!         - with an integral value `tol`: computes the ceil of the previous nth
//!           representable value in the `x` type.
//!         - with a floating  value `tol`: computes the ceil with a tolerance `tol`
//!           using Hagerty's FL5 function.
//!     4. with no tolerance value, the call is equivalent to `ceil[tolerance = 3*eps(as(x))(x)`
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/ceil)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions)
//!   *  [Hagerty's FL5](https://dl.acm.org/doi/pdf/10.1145/586032.586036)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/ceil.cpp}
.//! @}
//================================================================================================
inline constexpr auto ceil = functor<ceil_t>;
}

#include <eve/module/core/regular/impl/ceil.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/ceil.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/ceil.hpp>
#endif
