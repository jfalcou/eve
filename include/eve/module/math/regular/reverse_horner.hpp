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
#include <eve/module/math/regular/horner.hpp>

namespace eve
{
  template<typename Options>
  struct reverse_horner_t : callable<reverse_horner_t, Options, pedantic_option>
  {
    template<floating_value X, value T, value... Ts>
    requires(eve::same_lanes_or_scalar<X, T, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<X, T, Ts...>
    operator()(X x, T t, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, t, ts...); }

    template<floating_value X, kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<kumi::apply_traits_t<eve::common_value,Tup>, X>
    operator()(X x, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    EVE_CALLABLE_OBJECT(reverse_horner_t, reverse_horner_);
  };


//================================================================================================
//! @addtogroup math
//! @{
//!   @var reverse_horner
//!   @brief implement the horner scheme to evaluate polynomials with coefficients
//!   in increasing power order
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto reverse_horner(floating_value auto x, value auto ci...)                       noexcept; // 1
//!      constexpr auto reverse_horner(floating_value auto x, kumi::non_empty_product_type auto tci)  noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto reverse_horner[pedantic](/*any of the above overloads*/)                      noexcept; // 3
//!   }
//!   @endcode
//!
//!   1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!   2. Polynom is evaluated at x the other input is a range or a kumi::tuple containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x`: [evaluation point floating value](@ref floating_value) arguments.
//!     * `ci...`: [floating values](@ref floating_value) polynom coefficients in increasing power order,
//!     * `tci`: [non empty tuple](@ref kumi::non_empty_product_type) of floating values.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!      power order,  the Reverse Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ using the
//!      following formula:
//!
//!     \f$\qquad\qquad\displaystyle p(x) = (((c_{n-1}x+c_{n-2})x+ ... )x + c_0)\f$
//!
//!     1. The value of the polynom at  `x` is returned.
//!     2. same as the call with the elements of the tuple.
//!     3.`fma[pedantic]` instead of `fma` is used in internal computations.
//!        This is intended to insure more accurate computations where needed. This has no cost (and is
//!        automatically done) if the system has hard wired `fma` but is very expansive if it is not the case.
//!
//!    @note If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Horner's_method)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/reverse_horner.cpp}
//! @}
//================================================================================================
  inline constexpr auto reverse_horner = functor<reverse_horner_t>;

  namespace detail
  {
    template<typename X, typename C, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<X, Cs...>
    reverse_horner_(EVE_REQUIRES(cpu_), O const & o, X xx, C c0, Cs... cs) noexcept
    {
      if constexpr((... && scalar_value<Cs>))
      {
        using e_t =  element_type_t<X>;
        using t_t = kumi::result::generate_t<sizeof...(cs)+1, e_t>;
        t_t c{e_t(c0), e_t(cs)...};
        return reverse_horner[o](xx, c);
      }
      else
      {
        using r_t = common_value_t<X, Cs...>;
        auto x = r_t(xx);
        using t_t = kumi::result::generate_t<sizeof...(cs)+1, r_t>;
        t_t c {r_t{c0}, r_t{cs}...};
        return reverse_horner[o](x, c);
      }
    }

    template<typename X, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<X, Cs...>
    reverse_horner_(EVE_REQUIRES(cpu_), O const & o, X x,  kumi::tuple<Cs...> tup) noexcept
    {
      return horner[o](x, kumi::reverse(tup));
    }
  }
}
