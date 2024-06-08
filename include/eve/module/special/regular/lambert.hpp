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
  struct lambert_t : elementwise_callable<lambert_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    zipped<T,T> operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(lambert_t, lambert_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lambert
//!   @brief Computes the inverse of the function \f$ x \rightarrow xe^x \f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      zipped<T,T> lambert(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!   A tuple of the two branch values of the Lambert function is returned with the following
//!   considerations:
//!
//!     * The branches are not defined for input less than \f$e^{-1}\f$ in that case the values
//!       returned are NaN.
//!     * If the inputs are positive, only one branch exist and the two returned values are equal.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lambert.cpp}
//! @}
//================================================================================================
inline constexpr auto lambert = functor<lambert_t>;

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto lambert_serie_utility(T r)
    {
      using elt_t = element_type_t<T>;
      using A3    = kumi::result::generate_t<3, elt_t>;
      if constexpr( sizeof(elt_t) == 8 )
      {
        constexpr A3 P = { 0.000000000000000000000e+00, 2.331643981597117584689e+00, 1.931973535237478945863e+00 };
        constexpr A3 Q = { 1.000000000000000000000e+00, 1.605803223118019582808e+00, 4.174677763382451962312e-01 };
        return dec(reverse_horner(r, P) / reverse_horner(r, Q));
      }
      else
      {
        return fam(mone(as(r)), r, eve::horner(r, -1.80949529206e+00f, 2.33164314895e+00f));
      }
    }

    template<typename T, callable_options O>
    constexpr  kumi::tuple<T, T> lambert_(EVE_REQUIRES(cpu_), O const&, T x)
    {
      auto halley = [](auto x, auto w_i, auto max_iters)
        {
          auto w = w_i;
          for( int i = 0; i < max_iters; i++ )
          {
            T e = eve::exp(w);
            T p = inc(w);
            T t = fms(w, e, x);
            t /= if_else(is_gtz(w), e * p, e * p - T(0.5) * inc(p) * t / p);
            w -= t;
            T tol = 10 * eps(as(x)) * eve::max(eve::abs(w), rec[pedantic2](eve::abs(p) * e));
            if( eve::all(eve::abs(t) < tol) ) break;
          }
          return w;
        };

      T    q              = x + T(0.367879441171442);
      auto lambert0_small = [](auto q) { // branch 0 q <= 1.0e-3
        return lambert_serie_utility(eve::sqrt(q));
      };

      auto lambert0_other = [&halley](auto x, auto q){ // branch 0 q <= 1.0e'3
        auto p  = eve::sqrt(T(5.436563656918090) * q);
        auto w1 = dec(p * (inc(p * fam(T(-1.0 / 3), p, T(1.0 / 72)))));
        auto w2 = log(x);
        w2 -= if_else(x > 3, zero, log(w2));
        auto init = if_else(x < one(as(x)), w1, w2);
        return halley(x, init, 10);
      };

      auto lambert1 = [&halley](auto x, auto q, auto positivex){ // branch 1 q > 0
        T    r    = -eve::sqrt(q);
        auto test = (x < T(-1.0e-6));
        T    w1(0);
        if( eve::any(test) ) w1 = lambert_serie_utility(r);
        if( eve::all(test) && eve::all(q < T(3.0e-3)) ) return w1;
        T l1 = log(-x);
        T l2 = log(-l1);
        T w2 = l1 - l2 + l2 / l1;
        return if_else(is_eqz(x) && !positivex, minf(as(x)), halley(x, w2, 30));
      };

      auto r       = nan(as<T>());                // nan case treated here
      r            = if_else(is_eqz(x), zero, r); // zero case treated here
      r            = if_else(x == inf(as(x)), x, r);
      auto notdone = is_nlez(q) && (q != inf(as(x)));

      if( eve::any(notdone) )
      {
        notdone = next_interval(lambert0_small, notdone, q < T(1.0e-3), r, q);
        if( eve::any(notdone) ) { notdone = last_interval(lambert0_other, q >= T(1.0e-3), r, x, q); }
      }
      auto positivex = is_positive(x);
      if( eve::all(positivex) ) return eve::zip(r, r);
      auto r1 = if_else(positivex, r, lambert1(x, q, positivex));
      return eve::zip(r, r1);
    }
  }
}
