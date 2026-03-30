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
  struct lpnorm_t : strict_elementwise_callable<lpnorm_t, Options, raw_option, pedantic_option,
                                                kahan_option, widen_option>
  {
    template<value P, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) !=  0))
      EVE_FORCEINLINE constexpr as_wide_as_t<upgrade_if_t<Options, common_value_t<Ts...>>, P>
    operator()(P p, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(p, ts...); }

    template<value P, eve::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>, P>
    operator()(P p, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(p, t); }

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
//!      constexpr auto lpnorm(value auto p, floating_value auto... xs )                                  noexcept; // 1
//!      constexpr auto lpnorm(value auto p, non_empty_product_type tup)                                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto lpnorm[conditional_expr auto c](value auto p, floating_value auto... xs)          noexcept; // 3
//!      constexpr auto lpnorm[logical_value auto m](value auto p,floating_value auto... xs)              noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto lpnorm[pedantic](/* any of the above overloads */)                                noexcept; // 4
//!      constexpr auto lpnorm[widen](/* any of the above overloads */)                                   noexcept; // 5
//!      constexpr auto lpnorm[kahan](/* any of the above overloads */)                                   noexcept; // 6
//!      constexpr auto lpnorm[raw](/* any of the above overloads */)                                     noexcept; // 7
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `p`: [positive value](@ref eve::floating_value)
//!   * `x`, `... xs`: [floating values](@ref eve::floating_value)
//!   * `tup': kumi tuple (of the xs)
//!   * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!   * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!   1. \f$ \left(\sum_{i = 0}^n |x_i|^p\right)^{\frac1p} \f$ and \f$ \max_{i = 0}^n |x_i|} \f$ if 'p' is infinite.
//!   2. same as 1. on the tuple elements.
//!   3. [The operation is performed conditionnaly](@ref conditional)
//!   4. returns \f$\infty\f$ as soon as after disabling possible `Nan` parameters the result is \f$\infty\f$.
//!   5. The summation is computed in the double sized element type (if available).
//!   6. Kahan like compensated algorithm is used in internal summation for better precision (see [add](@ref eve::add)).
//!   7. This option is speedier, but does not care about avoiding overflows or treating 'Nans' in special ways.
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
    template<callable_options O, typename... Ts>
    EVE_FORCEINLINE constexpr auto lpnorm_(EVE_REQUIRES(strict_elementwise_emulated_), O const & o, Ts... ts) noexcept
    requires (O::contains(widen) && detail::fp16_should_apply<common_value_t<Ts...>>)
    {
      return lpnorm[o.drop(widen)](upgrade(ts)...);
    }

    template<typename P, floating_value... Ts, callable_options O>
    EVE_NOINLINE constexpr auto
    lpnorm_(EVE_REQUIRES(cpu_), O const & o, P p, Ts... args) noexcept
    requires(sizeof...(Ts) >=  1)
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
        else if(!O::contains(pedantic) && eve::all(p == eve::inf(as(p))) ) return maxabs[o.drop(kahan)](r_t(args)...);
        else
        {
          if (O::contains(pedantic))
          {
            auto nan_found = eve::false_(eve::as<r_t>());
            auto rp = r_t(p);
            auto e  = -maxmag(if_else(is_nan(args), zero, exponent(r_t(args)))...);
            auto f = [&](auto a){
              nan_found = eve::is_nan(a);
              return if_else(eve::is_nan(a), zero, pow_abs(ldexp[o](r_t(a), e), rp));
            };
            r_t that = eve::add[o](f(args)...);
            auto r = ldexp[pedantic](pow_abs(that, rec[pedantic](rp)), -e);
            r = if_else(nan_found && !is_infinite(r), allbits, r);
            auto isinfp = is_infinite(rp);
            if (eve::none(isinfp))
              return r;
            else
            {
              auto rinf = maxabs[o](r_t(args)...);
              r = if_else(isinfp, rinf, r);
              return if_else(nan_found && !is_infinite(r), allbits, r);
            }
          }
          else if constexpr(O::contains(raw))
          {
            auto rp = r_t(p);
            r_t that = manhattan[o](pow(r_t(args), rp)...);
            auto r = pow(that, rec[pedantic](rp));
            auto isinfp = is_infinite(rp);
            if (eve::none(isinfp)) return r;
            else return if_else(is_infinite(rp), eve::maxabs[o](args...), r);
          }
          else
          {
            auto rp = r_t(p);
            auto e  = -maxmag(if_else(is_nan(args), zero, exponent(r_t(args)))...);
            auto f = [&](auto a){ return pow_abs(ldexp[o](r_t(a), e), rp);};
            r_t that = eve::add[o](f(args)...);
            return ldexp[pedantic](pow_abs(that, rec[pedantic](rp)), -e);
          }
        }
      }
    }

    template<typename P, eve::non_empty_product_type Tup, callable_options O>
    EVE_FORCEINLINE constexpr auto
    lpnorm_(EVE_REQUIRES(cpu_), O const & o, P p, Tup tup) noexcept
    {
      return kumi::apply( [&](auto... m) { return lpnorm[o](p, m...); }, tup);
    }
  }
}
