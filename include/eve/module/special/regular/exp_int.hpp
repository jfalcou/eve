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
    template<floating_value T, value I>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, I> operator()(I n, T v) const noexcept
      requires (same_lanes_or_scalar<I, T>)
    {
      return this->behavior(as<as_wide_as_t<T, I>>{}, eve::current_api, this->options(), n, v);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(exp_int_t, exp_int_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var exp_int
  //!   @brief  `elementwise_callable` object computing the exponential integral
  //!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$.
  //!
  //!   @groupheader{Header file}
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
  //!      // Regular overload
  //!      constexpr auto exp_int(floating_value auto x)                                   noexcept; // 1
  //!      constexpr auto exp_int(unsigned_value auto n, floating_value auto x)            noexcept; // 2
  //!
  //!      // Lanes masking
  //!      constexpr auto exp_int[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
  //!      constexpr auto exp_int[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`: [unsigned argument](@ref eve::unsigned_value). If not present taken to be 1.
  //!     * `x`: [real floating argument](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the exponential integral
  //!   \f$ \mathbf{E}_n(x) = \displaystyle \int_1^\infty \frac{e^{-xt}}{t^n}\;\mbox{d}t\f$, is returned.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld:Exponential Integral ](https://mathworld.wolfram.com/ExponentialIntegral.html)
  //!   *  [DLMF: Generalized Exponential Integral](https://dlmf.nist.gov/8.19#i)
  //!   *  [Wikipedia: Exponential integral](https://en.wikipedia.org/wiki/Exponential_integral)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/special/exp_int.cpp}
  //================================================================================================
  inline constexpr auto exp_int = functor<exp_int_t>;
  //================================================================================================
  //! @}
  //================================================================================================
  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T exp_int_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      return exp_int(T(1), x);
    }

    template<callable_options O, typename I, typename T>
    constexpr as_wide_as_t<T, I> exp_int_(EVE_REQUIRES(cpu_), O const&, I in, T x) noexcept
    {
      if constexpr (scalar_value<I> && scalar_value<T>)
      {
        if( in == 0 ) return exp(-x) / x;
        if( in < 0 ) return nan(as<T>());
        return exp_int(T(in), x);
      }
      else if constexpr (integral_scalar_value<I> && simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        auto n = T(convert(in, as<elt_t>()));
        return exp_int(n, x);
      }
      else if constexpr (integral_simd_value<I> && simd_value<T>)
      {
        using elt_t = element_type_t<T>;
        return exp_int(convert(in, as<elt_t>()), x);
      }
      else if constexpr (integral_simd_value<I> && scalar_value<T>)
      {
        using elt_t = element_type_t<T>;
        using w_t   = wide<elt_t, cardinal_t<I>>;
        using i_t   = as_integer_t<elt_t>;
        return exp_int(convert(in, as<i_t>()), w_t(x));
      }
    }

    template<callable_options O, typename T>
    constexpr T exp_int_(EVE_REQUIRES(cpu_), O const&, T n, T x)
    {
      using elt_t = element_type_t<T>;
      auto notdone  = is_gez(x) && is_flint(n) && is_gez(n);
      T    r        = nan(as(x));  // if_else(notdone, zero, nan(as(x)));
      auto br_zeron = [](auto p) { return exp(-p) / p; };
      notdone = next_interval(br_zeron, notdone, is_eqz(n), r, x); // n == 0
      if( eve::any(notdone) )
      {
        auto br_largen = [](auto pn, auto px) { // n >  5000
          auto xk  = px + pn;
          auto yk  = rec[pedantic](sqr(xk));
          auto t   = pn;
          auto ans = yk * t * (6 * sqr(px) - 8 * t * px + sqr(t));
          ans      = yk * (ans + t * (t - 2 * px));
          ans      = yk * (ans + t);
          return inc(ans) * exp(-px) / xk;
        };
        notdone = next_interval(br_largen, notdone, n > 5000, r, n, x); // n >  5000
        if( eve::any(notdone) )
        {
          auto br_xlt1 = [](auto pn, auto px) { // here x is always le 1
            auto eqzx    = is_eqz(px);
            px           = inc[eqzx](px); // loop is infinite for x == 0
            auto    psi1 = zero(as(px));
            int32_t maxn = dec(max(1, int32_t(eve::maximum(pn))));
            for( int32_t i = maxn; i != 0; --i ) psi1 = add[T(i) < pn](psi1, rec[pedantic](T(i)));
            auto euler = ieee_constant<0x1.2788d00p-1f, 0x1.2788cfc6fb619p-1>(eve::as<T>{});
            auto psi   = -euler - log(px) + psi1;
            T    t;

            auto z   = -px;
            auto xk  = zero(as(px));
            auto yk  = one(as(px));
            auto pk  = oneminus(pn);
            auto ans = if_else(is_eqz(pk), zero, rec[pedantic](pk));
            do {
              xk = inc(xk);
              yk *= z / xk;
              pk  = inc(pk);
              ans = add[is_nez(pk)](ans, yk / pk);
              t   = if_else(is_nez(ans), abs(yk / ans), one);
            }
            while( eve::any(t > epso_2(as(px))) );
            auto in = convert(pn, int_from<T>());
            return add[eqzx]((eve::pow(z, dec(in)) * psi / tgamma(pn)) - ans, inf(as(px)));
          };
          auto xlt1 = x < 1;
          T    xx   = if_else(xlt1, x, one);
          notdone   = next_interval(br_xlt1, notdone, xlt1, r, n, xx); // x <  1
          if( eve::any(notdone) )
          {
            auto br_xge1 = [](auto pn, auto px) { // here x is always gt 1
              auto    exp_intbig = (sizeof(elt_t) == 8) ? T(1ull << 57) : T(1ull << 24);
              auto    rr          = exp_intbig;
              int32_t sk         = 1;
              T       t;
              auto    pkm2 = one(as(px));
              auto    qkm2 = px;
              auto    pkm1 = one(as(px));
              auto    qkm1 = px + pn;
              auto    ans  = pkm1 / qkm1;
              do {
                auto stest = is_odd(T(++sk));
                auto k_2   = T(sk >> 1);
                auto yk    = if_else(stest, one, px);
                auto xk    = add[stest](k_2, pn);
                auto pk    = pkm1 * yk + pkm2 * xk;
                auto qk    = qkm1 * yk + qkm2 * xk;
                rr          = pk / qk;
                auto test  = is_nez(qk);
                t          = if_else(test, abs((ans - rr) / rr), one);
                ans        = if_else(test, rr, ans);
                pkm2       = pkm1;
                pkm1       = pk;
                qkm2       = qkm1;
                qkm1       = qk;
                test       = abs(pk) > exp_intbig;
                auto fac   = if_else(test, epso_2(as(px)), one);
                pkm2 *= fac;
                pkm1 *= fac;
                qkm2 *= fac;
                qkm1 *= fac;
              }
              while( eve::any(t > eps(as(px))) );
              return add[px < maxlog(as(px))](zero(as(px)), ans * exp(-px));
            };
            notdone = last_interval(br_xge1, notdone, r, n, if_else(xlt1, T(2), x));
          }
        }
      }
      return if_else(is_eqz(x), rec[pedantic](dec(n)), r);
    }
  }
}
