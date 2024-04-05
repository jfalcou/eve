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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct tchebeval_t : callable<tchebeval_t, Options, pedantic_option>
  {
    template<floating_value X, value T, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<X, T, Ts...>
    operator()(X x, T t,  Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, t, ts...); }

    template<floating_value X, kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<kumi::apply_traits_t<eve::common_value,Tup>, X>
    operator()(X x, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    EVE_CALLABLE_OBJECT(tchebeval_t, tchebeval_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var tchebeval
//!   @brief Evaluates a polynomial on the Tchebytchev polynomial basis.
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial,
//!   the Tchebeval scheme evaluates the polynom \f$\sum_0^{n-1} a_i T_{i}(x)\f$,
//!   where \f$T_{i}\f$ is the \f$i^{th}\f$ Tchebytchev polynomial of the first kind.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::floating_ordered_value T, eve::floating_ordered_value Cs ...>
//!     T tchebeval(T x, Cs ... cs) noexcept;                                     // 1
//!
//!     template< eve::floating_ordered_value T, kumi::tuple Tup>
//!     T tchebeval(T x, Tup t) noexcept;                                           // 2
//!   }
//!   @endcode
//!
//!   1. Evaluates the Tchebytchev polynomial using a variadic list of coefficients.
//!   2. Evaluates the Tchebytchev polynomial using a range of coefficients.
//!   3. Evaluates the Tchebytchev polynomial using a range of coefficients in interval `[a,b]`.
//!
//!   **Parameters**
//!
//!     * `x` : [real floating argument](@ref eve::floating_ordered_value).
//!     * `a`, `b` : [real floating arguments](@ref eve::floating_ordered_value).
//!       If present,  they are the bounds of   the interval for which the Tchebytchev polynomial
//!       must be evaluated ( -1 and 1 by default). A change of variable
//!       \f$ x -> \frac{2x-a-b}{b-a}\f$ is internally performed.
//!     * `cs`: [values ](@ref eve::value) expansion pack associated to the
//!        coefficients \f$(a_i)_{0\le i \lt n}\f$.
//!     * `r` : Range containing The polynomial coefficients.
//!
//!    **Return value**
//!
//!    the value of the polynom at  `x` is returned.
//!
//!    **Notes**
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/math/tchebeval.cpp}
//! @}
//================================================================================================
  inline constexpr auto tchebeval = functor<tchebeval_t>;

  namespace detail
  {
