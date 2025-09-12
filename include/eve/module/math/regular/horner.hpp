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
#include <eve/concept/range.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/traits/helpers.hpp>

namespace eve
{
  template<typename Options>
  struct horner_t : callable<horner_t, Options, pedantic_option, kahan_option, widen_option>
  {
    template<floating_value X, value ... Ts>
    requires(eve::same_lanes_or_scalar<X, Ts...> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr common_value_t<X, Ts...>
    operator()(X x, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, ts...); }

    template<floating_value X, value ... Ts>
    requires(eve::same_lanes_or_scalar<X, Ts...> && Options::contains(widen))
    EVE_FORCEINLINE constexpr upgrade_t<common_value_t<X, Ts...>>
    operator()(X x, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, ts...); }


    template<floating_value X, kumi::product_type Tup>
    requires(!Options::contains(widen))
    EVE_FORCEINLINE constexpr
    eve::common_value_t<kumi::apply_traits_t<eve::common_value,coefficients<Tup>>, X>
    operator()(X x, coefficients<Tup> const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    template<floating_value X, kumi::product_type Tup>
    requires(Options::contains(widen))
    EVE_FORCEINLINE constexpr
    upgrade_t<eve::common_value_t<kumi::apply_traits_t<eve::common_value,coefficients<Tup>>, X>>
    operator()(X x, coefficients<Tup> const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    template<floating_value X, eve::detail::range R>
    requires(!Options::contains(widen))
    EVE_FORCEINLINE constexpr
    eve::common_value_t<typename R::value_type, X>
    operator()(X x, R const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    template<floating_value X, eve::detail::range R>
    requires(Options::contains(widen))
    EVE_FORCEINLINE constexpr
    upgrade_t<eve::common_value_t<typename R::value_type, X>>
    operator()(X x, R const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    EVE_CALLABLE_OBJECT(horner_t, horner_);
  };

//================================================================================================
//! @addtogroup math
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
//!      constexpr auto horner(floating_value auto x, eve::coefficients auto tci)            noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto horner[conditional_expr auto c](*any of the above overloads*/)       noexcept; // 3
//!      constexpr auto horner[logical_value auto m](*any of the above overloads*/)          noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto horner[pedantic](/*any of the above overloads*/)                     noexcept; // 4
//!      constexpr auto horner[kahan](/*any of the above overloads*/)                        noexcept; // 5
//!      constexpr auto horner[widen](/*any of the above overloads*/)                        noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [evaluation point floating value](@ref eve::floating_value) arguments.
//!    * `ci...`: [floating values](@ref eve::floating_value) polynom coefficients in decreasing power order,
//!        Note that the values of the `ci` are not necessarily floating but the non floating ones
//!        are to be scalar
//!    * `tci`: eve::coefficients is a specialization of [tuple](@ref kumi::product_type) of floating values,
//!             used to avoid possible ambiguities
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
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
//!     5. a Kahan like compensated algorithm is used to enhance accuracy.
//!     6. the computation is applied to upgraded types values when available.
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
    template<value X, callable_options O>
    EVE_FORCEINLINE constexpr auto
    horner_(EVE_REQUIRES(cpu_), O const & o, X ) noexcept
    {
      if constexpr(O::contains(widen))
        return eve::zero(as<upgrade_t<X>>());
      else
        return eve::zero(as<X>());
    }

    template<value X, value C, typename... Cs, callable_options O>
    EVE_FORCEINLINE constexpr auto
    horner_(EVE_REQUIRES(cpu_), O const & o, X xx, C c, Cs... cs) noexcept
    {
      using r_t          = common_value_t<X, Cs...>;
      constexpr auto N =  sizeof...(Cs);
      if constexpr(O::contains(widen))
        return horner(upgrade(xx), upgrade(c), upgrade(cs)...);
      else if constexpr( sizeof...(Cs) == 0 )
        return r_t(c);
      else if constexpr(O::contains(kahan))
      {
        using a_t = std::array<r_t, N>;
        a_t err;
        auto i = 0;
        auto s = r_t(c);
        auto x = r_t(xx);
        auto step = [&s, &err, x, &i]( auto a){
          auto [pi, epi] = eve::two_prod(s, x);
          auto [si, esi] = eve::two_add(pi, a);
          s = si;
          err[i] = epi+esi;
          ++i;
          return s;
        };
        ((s = step(r_t(cs))), ...);
        using tup_t =  kumi::result::generate_t<N, decltype([](std::size_t){return r_t(); })>;
        auto t = std::bit_cast<tup_t, a_t>(err);
        return s+ eve::horner(x, coefficients(t));
      }
      else
      {
        auto x = r_t(xx);
        r_t  that{0};

        that = fma[o](that, x, c);
        ((that = fma[o](that, x, cs)), ...);

        return that;
      }
    }

    template<value X, kumi::product_type Tuple, callable_options O>
    EVE_FORCEINLINE constexpr auto
    horner_(EVE_REQUIRES(cpu_), O const & o, X x, coefficients<Tuple> const& tup) noexcept
    {
      if constexpr(Tuple::size() == 0)
        return eve::zero(as(x));
      else
        return kumi::apply( [&](auto... m) { return horner[o](x, m...); }, tup);
    }

    template<typename X, range R, callable_options O>
    EVE_FORCEINLINE constexpr auto
    horner_(EVE_REQUIRES(cpu_), O const & o, X xx, R const& r) noexcept
    {
      using r_t = common_value_t<X, typename R::value_type>;
      auto up_if = [](auto a){
        if constexpr(O::contains(widen)) return upgrade(a);
        else return a;
      };
      auto x    = up_if(xx);
      auto cur  = std::begin(r);
      auto last = std::end(r);
      if( last == cur ) return up_if(zero(as<r_t>()));
      else if( std::distance(cur, last) == 1 ) return up_if(*cur);
      else
      {
        using std::advance;
        auto that = up_if(*cur);
        auto step = [&](auto th, auto arg) { return fma[o](x, th, arg); };
        for( advance(cur, 1); cur != last; advance(cur, 1) ) that = step(that, up_if(*cur));
        return that;
      }
    }
  }
}
