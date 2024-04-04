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
  struct horner_t : elementwise_callable<horner_t, Options, pedantic_option>
  {
    template<floating_value X, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<X, Ts...>
    operator()(X x, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, ts...); }

    template<floating_value X, kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<kumi::apply_traits_t<eve::common_value,Tup>, X>
    operator()(X x, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    EVE_CALLABLE_OBJECT(horner_t, horner_);
  };

//================================================================================================
//! @addtogroup math
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials/
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$
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
//!     template< eve::floating_ordered_value T, eve::floating_ordered_value C ...>
//!     T horner(T x, C ... coefs) noexcept;                                   //1
//!
//!     template< eve::floating_ordered_value T, eve::Range R>
//!     T horner(T x, R r) noexcept;                                           //2
//!
//!   }
//!   @endcode
//!
//!   1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!   2. Polynom is evaluated at x the other input is a range or a kumi::tuple containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!     * `coefs...` :  [real floating arguments](@ref eve::floating_ordered_value).
//!        The coefficients by decreasing power order
//!
//!     * `r` : Range or kumi::tuple containing The coefficients by decreasing power order.
//!
//!   **Return value**
//!
//!   The value of the polynom at  `x` is returned.
//!
//!    **Notes**
//!
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/math/horner.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::pedantic, eve::numeric
//!
//!       If d denotes one of these modifiers, the expression `d(eve::horner)(...)`
//!       computes the result using `d(eve::fma)` instead of `eve::fma` in internal computations.
//!
//!       This is intended to insure more accurate computations where needed. This has no cost if
//!       the system has hard wired fma but is very expansive if it is not the case.
//! @}
//================================================================================================
  inline constexpr auto horner = functor<horner_t>;

  namespace detail
  {
    template<typename X, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<X, Cs...>
    horner_(EVE_REQUIRES(cpu_), O const & o, X xx, Cs... cs) noexcept
    {
      using r_t          = common_value_t<X, Cs...>;
      constexpr size_t N = sizeof...(Cs);
      if constexpr( N == 0 ) return r_t(0);
      else if constexpr( N == 1 ) return (r_t(cs), ...);
      else
      {
        auto x    = r_t(xx);
        r_t  that(zero(as<r_t>()));
        auto next = [&](auto that, auto arg) { return fma[o](that, x, arg); };
        ((that = next(that, cs)), ...);
        return that;
      }
    }

    template<typename X, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<X, Cs...>
    horner_(EVE_REQUIRES(cpu_), O const & o, X x,  kumi::tuple<Cs...> tup) noexcept
    {
      return kumi::apply( [&](auto... m) { return horner(x, m...); }, tup);
    }
  }
}
