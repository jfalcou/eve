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
#include <eve/module/math/regular/hypot.hpp>
#include <eve/module/math/regular/pow_abs.hpp>
#include <eve/module/math/regular/pow.hpp>

namespace eve
{
  template<typename Options>
  struct lpnorm_t : strict_elementwise_callable<lpnorm_t, Options, pedantic_option,
                                                kahan_option, widen_option>
  {
    template<value P, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) !=  0) && !Options::contains(widen))
     EVE_FORCEINLINE constexpr as_wide_as_t<common_value_t<Ts...>, P>
    operator()(P p, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(p, ts...);
    }

    template<value P, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) !=  0) && Options::contains(widen))
     EVE_FORCEINLINE constexpr as_wide_as_t<upgrade_t<common_value_t<Ts...>>, P>
    operator()(P p, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(p, ts...);
    }

    template<value P, kumi::non_empty_product_type Tup>
    requires(!Options::contains(widen))
    EVE_FORCEINLINE constexpr
    as_wide_as_t<kumi::apply_traits_t<eve::common_value,Tup>, P>
    operator()(P p, Tup const& t) const noexcept { return EVE_DISPATCH_CALL(p, t); }

    template<value P, kumi::non_empty_product_type Tup>
    requires(Options::contains(widen))
      EVE_FORCEINLINE constexpr
    as_wide_as_t<upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>, P>
    operator()(P p, Tup const& t) const noexcept { return EVE_DISPATCH_CALL(p, t); }
    EVE_CALLABLE_OBJECT(lpnorm_t, lpnorm_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var lpnorm
//!
//! @brief `strict_elementwise_callable` object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n
//! |x_i|^p\right)^{\frac1p} \f$.
//!
//!   **Defined in Header**
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
//!      // Regular overload
//!      constexpr auto lpnorm(floating_value auto p, floating_value auto x,floating_value auto... xs )                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto lpnorm[conditional_expr auto c](loating_value auto p, floating_value auto x,floating_value auto... xs)  noexcept; // 2
//!      constexpr auto lpnorm[logical_value auto m](loating_value auto p, floating_value auto x,floating_value auto... xs)     noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto lpnorm[pedantic](/* any of the above overloads */)                                                     noexcept; // 3
//!      constexpr auto lpnorm[widen](/* any of the above overloads */)                                                        noexcept; // 4
//!      constexpr auto lpnorm[kahan](/* any of the above overloads */)                                                        noexcept; // 5
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `p`: [floating value](@ref eve::floating_value)
//!   * `x`, `... xs`: [floating values](@ref eve::floating_value)
//!   * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!   * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!   1. \f$ \left(\sum_{i = 0}^n |x_i|^p\right)^{\frac1p} \f$.
//!   2. [The operation is performed conditionnaly](@ref conditional)
//!   3. returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
//!   4. The summation is computed in the double sized element type (if available).
//!   5. Kahan like compensated algorithm is used in internal summation for better precision.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/lpnorm.cpp}
//================================================================================================
  inline constexpr auto lpnorm = functor<lpnorm_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename P, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    lpnorm_(EVE_REQUIRES(cpu_), O const & o, P p, Ts... args) noexcept
    {
      using c_t = common_value_t<Ts...>;
      using r_t = as_wide_as_t<c_t, P>;
      if constexpr(O::contains(widen))
        return lpnorm[o.drop(widen)](upgrade(p), upgrade(args)...);
      else if constexpr( integral_value<P> )
      {
        using e_t =  element_type_t<r_t>;
        auto fp =  convert(p, eve::as<e_t>());
        return lpnorm[o](fp, r_t(args)...);
      }
      else
      {
        if( eve::all(p == P(2)) )                 return hypot[o](r_t(args)...);
        else if( eve::all(p == P(1)) )            return manhattan[o](r_t(args)...);
        else if( eve::all(p == eve::inf(as(p))) ) return maxabs[o.drop(kahan)](r_t(args)...);
        else
        {
          if (O::contains(pedantic))
          {
            auto rp = r_t(p);
            auto any_is_inf = (is_infinite(r_t(args)) || ...);
            auto e  = -maxmag(exponent(r_t(args))...);
            auto f = [&](auto a){return pow_abs(ldexp[o](r_t(a), e), rp); };
            r_t that = add[o](f(args)...);
            auto r = ldexp[pedantic](pow_abs(that, rec[pedantic](rp)), -e);
            auto isinfp = is_infinite(rp);
            if (eve::none(isinfp))
              return force_if_any(o, r, eve::is_infinite, inf(eve::as(r)), args...);
            else
            {
              auto rinf = maxabs[o](r_t(args)...);
              r = if_else(isinfp, rinf, r);
              r = if_else(any_is_inf, inf(as<r_t>()), r);
              return force_if_any(o, r, eve::is_infinite, inf(eve::as(r)), args...);
            }
          }
          else
          {
            auto rp = r_t(p);
            r_t that = add[o](pow_abs(r_t(args), rp)...);
            auto r = pow(that, rec[pedantic](rp));
            auto isinfp = is_infinite(rp);
            if (eve::none(isinfp)) return r;
            else return if_else(is_infinite(rp), eve::maxabs[o](args...), r);
          }
        }
      }
    }

    template<typename P, typename T01, typename Tup, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<kumi::apply_traits_t<eve::common_value,Tup>, P>
    lpnorm_(EVE_REQUIRES(cpu_), O const & o, P p, Tup tup) noexcept
    {
      return kumi::apply( [&](auto... m) { return lpnorm[o](p, m...); }, tup);
    }
  }
}
