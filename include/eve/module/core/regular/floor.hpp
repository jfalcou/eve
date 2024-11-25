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
  struct floor_t : strict_elementwise_callable<floor_t, Options, almost_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
//      static_assert( valid_tolerance<T, Options>::value, "[eve::floor] simd tolerance requires simd parameter." );
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    template<value T, only_if<signed, unsigned>  U>
    constexpr EVE_FORCEINLINE as_integer_t<T, U> operator()(T v, as<U> target) const  noexcept
    {
//      static_assert( valid_tolerance<T, Options>::value, "[eve::floor] simd tolerance requires simd parameter." );
      return this->behavior(as<as_integer_t<T, U>>{}, eve::current_api, this->options(), v, target);
    }

    EVE_CALLABLE_OBJECT(floor_t, floor_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var floor
//!   @brief `elementwise_callable` object computing the largest integer not greater than the input.
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
//!      constexpr auto floor(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto floor[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto floor[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto floor[almost = tol](floating_value auto x)   noexcept; // 3
//!      constexpr auto floor[almost](floating_value auto x)         noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :[value](@ref eve::value) argument.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!     * `tol` [scalar valued](@ref eve::value) tolerance.
//!
//!   **Return value**
//!
//!       1. The largest integer not greater than `x`.
//!          The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!          `FE_TOWARDZERO`. This function object implements the `FE_DOWNWARD` version.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!       3. `almost` allows a fuzzy interpretation of ceil associated to a scalar tolerance.
//!           - with an integral value `tol`: computes the floor of the next nth
//!             representable value in the `x` type.
//!           - with a floating  value `tol`: computes the floor with a tolerance `tol`
//!             using Hagerty's FL5 function.
//!       4. with no tolerance value, the call is equivalent to `ceil[tolerance = 3*eps(as(x))(x)`
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/ceil)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Floor_and_ceiling_functions)
//!   *  [Hagerty's FL5](https://dl.acm.org/doi/pdf/10.1145/586032.586036)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/floor.cpp}
//================================================================================================
  inline constexpr auto floor = functor<floor_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/floor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/floor.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/floor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/floor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/floor.hpp>
#endif
