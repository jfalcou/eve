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
  struct average_t : tuple_callable<average_t, Options, raw_option, upper_option, lower_option,
                                    strict_option, kahan_option, widen_option>
  {
 //    template<value T,  value U>
//     requires(eve::same_lanes_or_scalar<T, U> && !Options::contains(widen))
//     constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
//     { return EVE_DISPATCH_CALL(a, b); }

//    template<value T,  value U>
//     requires(eve::same_lanes_or_scalar<T, U> && Options::contains(widen))
//      constexpr EVE_FORCEINLINE common_value_t<eve::upgrade_t<T>, eve::upgrade_t<U>> operator()(T a, U b) const
//     { return EVE_DISPATCH_CALL(a, b); }

    template<value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr common_value_t<Ts...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<value... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<Ts...> && Options::contains(widen))
      EVE_FORCEINLINE constexpr common_value_t<eve::upgrade_t<Ts>...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<integral_value T0,  integral_value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
      EVE_FORCEINLINE common_value_t<T0, T1>
    constexpr operator()(T0 t0, T1 t1)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup>)
//     EVE_FORCEINLINE constexpr
//     kumi::apply_traits_t<eve::common_value,Tup>
//     operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
//     {
//       return EVE_DISPATCH_CALL(t);
//     }

    EVE_CALLABLE_OBJECT(average_t, average_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var average
//!   @brief `tuple_callable` computing the arithmetic mean of its arguments.
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
//!      // Regular overloads
//!      constexpr auto average(eve::integral_value auto x, eve::integral_value auto y)             noexcept; // 1
//!      constexpr auto average(eve::floating_value auto x, eve::floating_value auto ... xs)        noexcept; // 2
//!      constexpr auto average(kumi::non_empty_product_type auto const& tup)                       noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto average[conditional_expr auto c](/* any of the above overloads */)          noexcept; // 4
//!      constexpr auto average[logical_value auto m](/* any of the above overloads */)             noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto average[raw] (/* any of the above overloads */)                             noexcept; // 5
//!      constexpr auto average[upper](eve::value auto x, eve::value auto y)                        noexcept; // 6
//!      constexpr auto average[lower](eve::value auto x, eve::value auto y)                        noexcept; // 7
//!      constexpr auto average[upper][strict](eve::value auto x, eve::value auto y)                noexcept; // 6
//!      constexpr auto average[lower][strict](eve::value auto x, eve::value auto y)                noexcept; // 7
//!      constexpr auto average[widen](/* any of the above overloads */)                            noexcept; // 8
//!      constexpr auto average[kahan](/* any of the above overloads */)                            noexcept; // 9
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [integral value](@ref eve::integral_value) arguments.
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the arithmetic mean  of the arguments is returned.
//!
//!     1. For two integral parameters half the sum of `x` and `y`. No overflow occurs.
//!        If the sum is odd, the result is a rounded value at a distance guaranteed
//!        to be less than or equal to 0.5 of the average floating value, but may differ
//!        by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
//!        simd intrinsics to perform the operation, the scalar results may differ by one unit from
//!        simd ones which are system dependent.
//!
//!        However the `dowward` (respectively `upward`) options can be used to ensure the result is equivalent to
//!        the integral conversion of `floor((x+y)/2)`, (respectively  `ceil((x+y)/2)`).
//!     2. the arithmetic mean of its arguments. No overflow occurs.
//!     3. the arithmetic mean of the tuple arguments. No overflow occurs.
//!     4. [The operation is performed conditionnaly](@ref conditional)
//!     5. No provision is made to avoid overflows for more than 2 parameters.
//!     6. The average is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!        to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries, these are similar to `ceil((x+y)/2)`, but converted to an integral value.
//!     7. The average is computed in a 'round toward \f$ +\infty\f$ mode. The result is guaranted
//!        to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries,  these are similar to `floor((x+y)/2)` but converted to an integral value.
//!      8. The average is computed in the double sized element type (if available).
///!     9. Compesated algorithm for better precision.
//!
//!  @note unless raw option is used no spurious overflow can be obtained.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/average.cpp}
//================================================================================================
  inline constexpr auto average = functor<average_t>;
//================================================================================================
//! @}
//================================================================================================

}

#include <eve/module/core/regular/impl/average.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/average.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/average.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/average.hpp>
#endif
