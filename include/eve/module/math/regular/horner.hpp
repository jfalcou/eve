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
  struct horner_t : callable<horner_t, Options, pedantic_option>
  {
    template<floating_value X, value T, value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<X, T, Ts...> operator()(X x, T t,  Ts...ts) const noexcept
      requires (same_lanes_or_scalar<X, T, Ts...>)
    {
      return this->behavior(as<common_value_t<X, T, Ts...>>{}, eve::current_api, this->options(), x, t, ts...);
    }

    template<floating_value X, kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr common_value_t<kumi::apply_traits_t<common_value, Tup>, X> operator()(X x, Tup const& t) const noexcept
      requires (same_lanes_or_scalar_tuple<Tup> && same_lanes_or_scalar<X, kumi::element_t<0, Tup>>)
    {
      return this->behavior(as<common_value_t<kumi::apply_traits_t<common_value, Tup>, X>>{}, eve::current_api, this->options(), x, t);
    }

    EVE_CALLABLE_OBJECT(horner_t, horner_);
  };

//================================================================================================
//! @addtogroup mathsq
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials with coefficients
//!   in decreasing power order
//!
//!
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!
//!   \f$\qquad\displaystyle p(x) = (((c_0x+c_1)x+ ... )x + c_{n-1})\f$
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
//!      constexpr auto horner(floating_value auto x, value auto ...ci)                      noexcept; // 1
//!      constexpr auto horner(floating_value auto x, kumi::non_empty_product_type auto tci) noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto horner[conditional_expr auto c](*any of the above overloads*/)       noexcept; // 3
//!      constexpr auto horner[logical_value auto m](*any of the above overloads*/)          noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto horner[pedantic](/*any of the above overloads*/)                     noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [evaluation point floating value](@ref floating_value) arguments.
//!     * `ci...`: [floating values](@ref floating_value) polynom coefficients in decreasing power order,
//!        Note that the values of the `ci` are not necessarily floating but the non floating ones
//!        are to be scalar
//!     * `tci`: [non empty tuple](@ref kumi::non_empty_product_type) of floating values.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!     power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!     \f$\qquad\qquad\displaystyle p(x) = (((c_0x+c_1)x+ ... )x + c_{n-1})\f$
//!
//!     1. The value of the polynom at  `x` is returned.
//!     2. Same as the call with the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!     4. `fma[pedantic]` instead of `fma` is used in internal computations.
//!
//!    @note If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Horner's_method)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/math/horner.cpp}
//================================================================================================
  inline constexpr auto horner = functor<horner_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename X, typename C, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<X, C, Cs...>
    horner_(EVE_REQUIRES(cpu_), O const & o, X xx, C c, Cs... cs) noexcept
    {
      using r_t          = common_value_t<X, Cs...>;

      if constexpr( sizeof...(Cs) == 0 ) return r_t(c);
      else
      {
        auto x = r_t(xx);
        r_t  that{0};

        that = fma[o](that, x, c);
        ((that = fma[o](that, x, cs)), ...);

        return that;
      }
    }

    template<typename X, kumi::product_type Tuple, callable_options O>
    EVE_FORCEINLINE constexpr auto
    horner_(EVE_REQUIRES(cpu_), O const & o, X x, Tuple const& tup) noexcept
    {
      return kumi::apply( [&](auto... m) { return horner[o](x, m...); }, tup);
    }
  }
}
