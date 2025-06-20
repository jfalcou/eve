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
  struct newton_t : callable<newton_t, Options, pedantic_option>
  {
    template<floating_value X, value... CsNs>
    requires(eve::same_lanes_or_scalar<X, CsNs...>)
    EVE_FORCEINLINE constexpr common_value_t<X, CsNs...>
    operator()(X x, CsNs... csns) const noexcept
    {
      constexpr auto s = sizeof...(CsNs);
      static_assert((s == 0) || s&1, "[eve::newton]: nodes and coefs have incompatible sizes");
      return EVE_DISPATCH_CALL(x, csns...);
    }

    template<floating_value X, value... Cs, value... Ns>
    requires(eve::same_lanes_or_scalar<X, Cs..., Ns...>)
    EVE_FORCEINLINE constexpr
    eve::common_value_t<X, Cs...,  Ns...>
    operator()(X x, coefficients<kumi::tuple<Cs...>> const & t1, nodes<kumi::tuple<Ns...>> const & t2) const noexcept
    {
      static_assert((sizeof...(Cs) == 0 && sizeof...(Ns) == 0)||
                 (sizeof...(Cs) ==  sizeof...(Ns)+1), "[eve::newton]: nodes and coefs have incompatible sizes");
      return EVE_DISPATCH_CALL(x, t1, t2);
    }

    template<floating_value X, eve::detail::range R1, eve::detail::range R2>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<X, typename R1::value_type, typename R2::value_type>
    operator()(X x, R1 const& t1,  R2 const & t2) const noexcept
    {
      return EVE_DISPATCH_CALL(x, t1, t2);
    }

    EVE_CALLABLE_OBJECT(newton_t, newton_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var newton
//!   @brief Implement the Newton scheme to evaluate polynomials.
//!
//!   If \f$(c_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  and \f$(m_i)_{0\le i\le n-2}\f$ the nodes, the Newton scheme evaluates
//!   the polynom \f$p\f$ at \f$x\f$ using the following formula :
//!
//!   \f$\qquad\displaystyle p(x) = (((c_0(x-m_0)+c_1)(x-m_1)+ ... )(x-m_{n-2}) + c_{n-1})\f$
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
//!      constexpr auto newton(floating_value auto x, floating_value auto ... cmi)         noexcept; // 1
//!      constexpr auto newton(floating_value auto x, eve::coefficients ci
//!                                                   eve::nodes auto ni)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto newton[conditional_expr auto c](*any of the above overloads*/)     noexcept; // 3
//!      constexpr auto newton[logical_value auto m](*any of the above overloads*/)        noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto newton[pedantic](/*any of the above overloads*/)                   noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`:  [real floating argument](@ref eve::floating_value).
//!    * `ci`:  eve::coefficients tuple  containing the coefficients by decreasing power order.
//!    * `cn`:  eve::nodes tuple  containing the nodes by decreasing power order.
//!    * `cni...`: all the coefficients followed by all the nodes, both in decreasing power order.
//!                The total number of values is to be odd. If s is this number, the (s+1)/2 first
//!                are taken as the coefs and the others are the nodes.
//!                Note that the values of the cmi are not necessarily floating but the non floating ones
//!                are to be scalar
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the polynom at  `x` is returned.
//!      2. same as the call with the elements of the tuples.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!      4. `fma[pedantic]` instead of `fma` is used in internal computations.
//!
//!   @note If the coefficients or nodes are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/newton.cpp}
//================================================================================================
  inline constexpr auto newton = functor<newton_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename X, typename ...Coefs, typename... Nodes, callable_options O >
    EVE_FORCEINLINE constexpr auto
    newton_(EVE_REQUIRES(cpu_), O const &o, X xx,  coefficients<kumi::tuple<Coefs...>> const& cs
           , nodes<kumi::tuple<Nodes...>> const& ns)
    {

      using r1_t  =  common_value_t<X, Coefs...>;
      using r2_t  =  common_value_t<X, Nodes...>;
      using r_t   = common_value_t<r1_t, r2_t>;
      if constexpr(kumi::size_v<decltype(cs)> == 0)
      {
        return zero(as<r_t>());
      }
      else if constexpr(kumi::size_v<decltype(cs)> == 1)
      {
        return r_t(get<0>(cs));
      }
      else
      {
        r_t that = r_t(get<0>(cs));
        auto ans = kumi::zip(kumi::pop_front(cs), ns);
        auto compute = [&](auto ... args){
          auto doit = [&](auto an){
            auto [a, n] = an;
            that =  fma[o](that, xx-n, a);
          };
          ((doit(args), ...));
          return that;
        };
        return kumi::apply(compute, ans);
      }
    }

    template<typename X, typename ...CsNs, callable_options O >
    EVE_FORCEINLINE constexpr auto
    newton_(EVE_REQUIRES(cpu_), O const &o, X xx, CsNs... cns)
    {
      using r_t = common_value_t<X, CsNs...>;
      auto x = r_t(xx);
      constexpr auto s   = sizeof...(cns);
      if constexpr(s == 0)
        return zero(as(xx));
      else
      {
         kumi::result::fill_t<s, r_t> tcn{r_t{cns}...};
        auto [tc, tn] = split(tcn, kumi::index<(s+1)/2>);
        return newton[o](x,coefficients{tc},nodes{tn});
      }
    }

    template<typename X, typename RC,  typename RN, callable_options O >
    EVE_FORCEINLINE constexpr auto
    newton_(EVE_REQUIRES(cpu_), O const &o, X xx,  RC const& rc, RN const & rn)
    {
      using r_t   = common_value_t<X, typename RC::value_type, typename RN::value_type>;
      auto x      = r_t(xx);
      auto firstc = begin(rc);
      auto lastc  = end(rc);
      if( firstc == lastc ) return r_t(0);
      else
      {
        auto siz = std::distance(firstc, lastc);
//     EVE_ASSERT(siz == inc(std::distance(begin(rn), end(rn))),
//                "number of nodes must equal to the number of coefficients minus 1");
        if( siz == 1 ) return r_t(*firstc);
        else
        {
          using std::advance;
          auto firstn = begin(rn);
          auto curn   = firstn;
          auto curc   = firstc;
          advance(curc, 1);
          advance(curn, 1);
          auto dfma = fma[o];
          r_t  that(dfma(*firstc, sub(x, *firstn), *curc));
          auto step = [&](auto that, auto argc, auto argn) { return dfma( that, sub(x, argn), argc); };
          for( advance(curc, 1); curc != lastc; advance(curc, 1), advance(curn, 1) )
            that = step(that, *curc, *curn);
          return that;
        }
      }
    }
  }
}
