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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/tgamma.hpp>

namespace eve
{
template<typename Options>
struct exp_int_t : strict_elementwise_callable<exp_int_t, Options, saturated_option>
{
  template<eve::floating_ordered_value T, eve::ordered_value I>
  requires (same_lanes_or_scalar<I, T>)
  EVE_FORCEINLINE  constexpr eve::as_wide_as_t<T, I>  operator()(I n, T v) const noexcept
  { return EVE_DISPATCH_CALL(n, v); }

  template<eve::floating_ordered_value T>
  EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(exp_int_t, exp_int_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var exp_int
//!   @brief Computes the exponential integral
//!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$.
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
//!      template< eve::floating_ordered_value T >
//!      T exp_int(T x) noexcept;
//!
//!      template< eve::unsigned_value N, eve::floating_ordered_value T >
//!      T exp_int(N n, T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value). If not present taken to be 1.
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the exponential integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/exp_int.cpp}
//! @}
//================================================================================================
inline constexpr auto exp_int = functor<exp_int_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr  EVE_FORCEINLINE T exp_int_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      return exp_int(T(1), x);
    }

    template<typename I, typename T, callable_options O>
    constexpr eve::as_wide_as_t<T, I> exp_int_(EVE_REQUIRES(cpu_), O const& , I in, T x) noexcept
    {
      if constexpr(scalar_value<I> && scalar_value<T>)
      {
        if( in == 0 ) return exp(-x) / x;
        if( in < 0 ) return nan(as<T>());
        return exp_int(T(in), x);
      }
      else if constexpr(integral_scalar_value<I> && simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        auto n = T(convert(in, as<elt_t>()));
        return exp_int(n, x);
      }
      else if constexpr(integral_simd_value<I> && simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        return exp_int(convert(in, as<elt_t>()), x);
      }
      else if constexpr(integral_simd_value<I> && scalar_value<T>)
      {
        using elt_t = element_type_t<T>;
        using w_t   = wide<elt_t, cardinal_t<I>>;
        using i_t   = as_integer_t<elt_t>;
        return exp_int(convert(in, as<i_t>()), w_t(x));
      }
    }

    template<typename T, callable_options O>
    T exp_int_(EVE_REQUIRES(cpu_), O const& , T n, T x)
    {
      using elt_t = element_type_t<T>;
      auto notdone  = is_gez(x) && is_flint(n) && is_gez(n);
      T    r        = nan(as(x));  // if_else(notdone, zero, nan(as(x)));
      auto br_zeron = [](auto x) { // n == 0
        return exp(-x) / x;
      };
      notdone = next_interval(br_zeron, notdone, is_eqz(n), r, x); // n == 0
      if( eve::any(notdone) )
      {
        auto br_largen = [](auto n, auto x) { // n >  5000
          auto xk  = x + n;
          auto yk  = rec[pedantic2](sqr(xk));
          auto t   = n;
          auto ans = yk * t * (6 * sqr(x) - 8 * t * x + sqr(t));
          ans      = yk * (ans + t * (t - 2 * x));
          ans      = yk * (ans + t);
          return inc(ans) * exp(-x) / xk;
        };
        notdone = next_interval(br_largen, notdone, n > 5000, r, n, x); // n >  5000
        if( eve::any(notdone) )
        {
          auto br_xlt1 = [](auto n, auto x) { // here x is always le 1
            auto eqzx    = is_eqz(x);
            x            = inc[eqzx](x); // loop is infinite for x == 0
            auto    psi1 = zero(as(x));
            int32_t maxn = dec(max(1, int32_t(eve::maximum(n))));
            for( int32_t i = maxn; i != 0; --i ) psi1 = add[T(i) < n](psi1, rec[pedantic2](T(i)));
            auto euler = ieee_constant<0x1.2788d00p-1f, 0x1.2788cfc6fb619p-1>(eve::as<T>{});
            auto psi   = -euler - log(x) + psi1;
            T    t;
            ;
            auto z   = -x;
            auto xk  = zero(as(x));
            auto yk  = one(as(x));
            auto pk  = oneminus(n);
            auto ans = if_else(is_eqz(pk), zero, rec[pedantic2](pk));
            do {
              xk = inc(xk);
              yk *= z / xk;
              pk  = inc(pk);
              ans = add[is_nez(pk)](ans, yk / pk);
              t   = if_else(is_nez(ans), abs(yk / ans), one);
            }
            while( eve::any(t > epso_2(as(x))) );
            auto in = convert(n, int_from<T>());
            return add[eqzx]((eve::pow(z, dec(in)) * psi / tgamma(n)) - ans, inf(as(x)));
          };
          auto xlt1 = x < 1;
          T    xx   = if_else(xlt1, x, one);
          notdone   = next_interval(br_xlt1, notdone, xlt1, r, n, xx); // x <  1
          if( eve::any(notdone) )
          {
            auto br_xge1 = [](auto n, auto x) { // here x is always gt 1
              auto    exp_intbig = (sizeof(elt_t) == 8) ? T(1ull << 57) : T(1ull << 24);
              auto    r          = exp_intbig;
              int32_t sk         = 1;
              T       t;
              auto    pkm2 = one(as(x));
              auto    qkm2 = x;
              auto    pkm1 = one(as(x));
              auto    qkm1 = x + n;
              auto    ans  = pkm1 / qkm1;
              do {
                auto stest = is_odd(T(++sk));
                auto k_2   = T(sk >> 1);
                auto yk    = if_else(stest, one, x);
                auto xk    = add[stest](k_2, n);
                auto pk    = pkm1 * yk + pkm2 * xk;
                auto qk    = qkm1 * yk + qkm2 * xk;
                r          = pk / qk;
                auto test  = is_nez(qk);
                t          = if_else(test, abs((ans - r) / r), one);
                ans        = if_else(test, r, ans);
                pkm2       = pkm1;
                pkm1       = pk;
                qkm2       = qkm1;
                qkm1       = qk;
                test       = abs(pk) > exp_intbig;
                auto fac   = if_else(test, epso_2(as(x)), one);
                pkm2 *= fac;
                pkm1 *= fac;
                qkm2 *= fac;
                qkm1 *= fac;
              }
              while( eve::any(t > eps(as(x))) );
              return add[x < maxlog(as(x))](zero(as(x)), ans * exp(-x));

            };
            T xx    = if_else(xlt1, T(2), x);
            notdone = last_interval(br_xge1, notdone, r, n, xx);
          }
        }
      }
      return if_else(is_eqz(x), rec[pedantic2](dec(n)), r);
    }
  }
}
