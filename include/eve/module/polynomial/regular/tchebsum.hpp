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
  struct tchebsum_t : callable<tchebsum_t, Options, pedantic_option, increasing_option,
                               decreasing_option, widen_option>
  {
    template<floating_value X, value ... Ts>
    requires(eve::same_lanes_or_scalar<X, Ts...>)
    EVE_FORCEINLINE constexpr upgrade_if_t<Options, common_value_t<X, Ts...>>
    operator()(X x, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(x, ts...); }

    template<floating_value X, eve::product_type Tup>
    EVE_FORCEINLINE constexpr
    upgrade_if_t<Options, eve::common_value_t<kumi::apply_traits_t<eve::common_value,coefficients<Tup>>, X>>
    operator()(X x, coefficients<Tup> const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    template<floating_value X, eve::detail::range R>
    EVE_FORCEINLINE constexpr
    upgrade_if_t<Options, eve::common_value_t<typename R::value_type, X>>
    operator()(X x, R const& t) const noexcept
    { return EVE_DISPATCH_CALL(x, t); }

    EVE_CALLABLE_OBJECT(tchebsum_t, tchebsum_);
  };

//================================================================================================
//! @addtogroup math
//! @{
//!   @var tchebsum
//!   @brief Implement the evaluation of tchebytchev  polynomials with coefficients
//!   in increasing or decreasing power order
//!
//!
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!   power order,  the Tchebsum scheme evaluates :
//!   \f$\qquad\displaystyle p(x) = c_0/2+\sum_1^n c_n T_n(x))\f$
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
//!      constexpr auto tchebsum(floating_value auto x, value auto ...ci)                      noexcept; // 1
//!      constexpr auto tchebsum(floating_value auto x, eve::coefficients auto tci)            noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto tchebsum[conditional_expr auto c](*any of the above overloads*/)       noexcept; // 3
//!      constexpr auto tchebsum[logical_value auto m](*any of the above overloads*/)          noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto tchebsum[pedantic](/*any of the above overloads*/)                     noexcept; // 4
//!      constexpr auto tchebsum[kahan](/*any of the above overloads*/)                        noexcept; // 5
//!      constexpr auto tchebsum[widen](/*any of the above overloads*/)                        noexcept; // 6
//!      constexpr auto tchebsum[increasing](/*any of the above overloads*/)                   noexcept; // 1
//!      constexpr auto tchebsum[decreasing](/*any of the above overloads*/)                   noexcept; // 7
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [evaluation point floating value](@ref eve::floating_value) arguments.
//!    * `ci...`: [floating values](@ref eve::floating_value) tchebytchev coefficients in increasing power order,
//!        Note that the values of the `ci` are not necessarily floating but the non floating ones
//!        are to be scalar
//!    * `tci`: eve::coefficients is a specialization of [tuple](@ref eve::product_type) of floating values,
//!             used to avoid possible ambiguities
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     If \f$(c_i)_{0\le i\le n-1}\f$ denotes the Tchebytchev coefficients of the polynomial
//!     The Tchebsum scheme evaluates  :
//!     \f$\qquad\displaystyle p(x) = c_0/2+\sum_1^n c_n T_n(x))\f
//!
//!     1. The value at  `x` f the polynom based on first kind Tchebytchev function is returned.
//!     2. Same as the call with the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!     4. `fma[pedantic]` instead of `fma` is used in internal computations.
//!     5. a Kahan like compensated algorithm is used to enhance accuracy.
//!     6. the computation is applied to upgraded types values when available.
//!     7. the order of the given coefficients is reversed
//!
//!    @note If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Tchebsum's_method)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/math/tchebsum.cpp}
//================================================================================================
  inline constexpr auto tchebsum = functor<tchebsum_t>;
//================================================================================================
//! @}
//================================================================================================
}

namespace eve::detail
{

  template<value T, typename... Cs, callable_options O>
  EVE_FORCEINLINE constexpr auto
  tchebsum_(EVE_REQUIRES(cpu_), O const & o, T xx, Cs... cs) noexcept
  {
    using r_t   = common_value_t<T, Cs...>;
    using elt_t = element_type_t<r_t>;
    constexpr auto N =  sizeof...(Cs);
    if constexpr(N == 0)
      return zero(as(xx));
   else if constexpr(std::same_as<elt_t, eve::float16_t>)
      return eve::detail::apply_fp16_as_fp32(eve::tchebsum[o], xx, cs...);
    else if constexpr(O::contains(widen))
      return tchebsum(upgrade(xx), upgrade(cs)...);
    else if constexpr( N == 1 )
      return r_t((cs/r_t(2))...);
    else if constexpr(!O::contains(decreasing))
    {
      using e_t = element_type_t<r_t>;
      using t_t = kumi::result::fill_t<sizeof...(cs), e_t>;
      t_t tup{e_t(cs)...};
      return kumi::apply( [&](auto... m) { return tchebsum[o][decreasing](xx, m...); }, kumi::reverse(tup));
    }
    else
    {
      //This code is a C++ vectorized version of Alan Macleod's Fortran code
      auto x = r_t(xx);
      auto sgn = eve::signnz(x);

      auto br_clemshaw  = [ = ](){
        auto tt = x+x;
        auto d1 =  zero(as<r_t>());
        auto u0 = d1;
        auto u1 = d1;
        auto u2 = d1;

        auto clemshaw_step = [&](auto ci)
        {
          u2=u1;
          u1=u0;
          u0 = fma[o](tt, u1, ci-u2);
          return u0;
        };
        r_t that(0);
        ((that = clemshaw_step(cs)), ...);
        return eve::average(that, -u2);
      };

      auto br_reinch  = [ = ](){
        auto d1 = zero(as<r_t>());
        auto d2 = d1;
        auto u1 = d1;
        auto u2 = d1;
        auto shalf = sgn/2;
        auto tt = (x-shalf)-shalf;
        tt += tt;

        auto reinch_step = [&](auto ci)
        {
          d2=d1;
          u2=u1;
          d1=fma[o](tt, u2, fam[o](ci, sgn, d2));
          u1=d1+sgn*u2;
          return d1;
        };
        r_t that(0);
        ((that = reinch_step(cs)), ...);
        return eve::average(that, sgn*d2);
      };
      auto r       = nan(as(x));
      auto notdone = is_not_nan(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_clemshaw, notdone, eve::is_less(eve::abs(x), r_t(0.6)), r);
        if( eve::any(notdone) )
        {
          last_interval(br_reinch, notdone, r);
        }
      }
      return r;
    }
  }

  template<value X, eve::product_type Tuple, callable_options O>
  EVE_FORCEINLINE constexpr auto
  tchebsum_(EVE_REQUIRES(cpu_), O const & o, X x, coefficients<Tuple> const& tup) noexcept
  {
    if constexpr(Tuple::size() == 0)
      return eve::zero(as(x));
    else if constexpr(!O::contains(decreasing))
      return kumi::apply( [&](auto... m) { return tchebsum[o](x, m...); }, kumi::reverse(tup));
    else
      return kumi::apply( [&](auto... m) { return tchebsum[o](x, m...); }, tup);
  }


  template<typename X, range R, callable_options O>
  EVE_FORCEINLINE constexpr auto
  tchebsum_(EVE_REQUIRES(cpu_), O const & o, X xx, R const& r) noexcept
  {
    using r_t = common_value_t<X, typename R::value_type>;
    auto up_if = [](auto a){
      if constexpr(O::contains(widen)) return upgrade(r_t(a));
      else return r_t(a);
    };
    auto x    = up_if(xx);
    auto current  = [&r](){
      if constexpr(O::contains(increasing))
         return std::rbegin(r);
      else
        return std::begin(r);
    };
    auto der  = [&r](){
      if constexpr(O::contains(increasing))
         return std::rend(r);
      else
        return std::end(r);
    };
    if( der() == current() )
    {
      return up_if(zero(as<r_t>()));
    }
    else if( std::distance(current(), der()) == 1 )
    {
      return up_if((*current())/2);
    }
    else
    {
      auto sgn = eve::signnz(x);
      auto br_clemshaw  = [&](){
        auto cur = current();
        auto last= der();
        using std::advance;
        auto that = up_if(0);
        auto u0 = that;
        auto u1 = that;
        auto u2 = that;
        auto tt = x+x;

        for(; cur != last; advance(cur, 1) ) {
          u2=u1;
          u1=u0;
          u0=eve::fma[o](tt, u1, (*cur)-u2);
        }
        return eve::average(u0, -u2);
      };

      auto br_reinch  = [ & ](){
        auto cur = current();
        auto last= der();
        using std::advance;
        auto that = up_if(0);
        auto d1 = that;
        auto d2 = d1;
        auto u1 = d1;
        auto u2 = d1;
        auto shalf = sgn/2;
        auto tt = (x-shalf)-shalf;
        tt += tt;

        for(; cur != last; advance(cur, 1) ) {
          d2=d1;
          u2=u1;
          d1=fma[o](tt, u2, fam[o](*cur, sgn, d2));
          u1=d1+sgn*u2;
        };
        return eve::average(d1, sgn*d2);
      };

      auto res     = nan(as(x));
      auto notdone = is_not_nan(x);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_clemshaw, notdone, eve::is_less(eve::abs(x), r_t(0.6)), res);
        if( eve::any(notdone) )
        {
          last_interval(br_reinch, notdone, res);
        }
      }
      return res;
    }
  }
}
