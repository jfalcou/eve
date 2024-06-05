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
  struct lpnorm_t : strict_elementwise_callable<lpnorm_t, Options, pedantic_option>
  {
    template<value P, floating_value T0, floating_value T1, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
     EVE_FORCEINLINE constexpr as_wide_as_t<common_value_t<T0, T1, Ts...>, P>
    operator()(P p, T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(p, t0, t1, ts...);
    }

    template<value P, kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<kumi::apply_traits_t<eve::common_value,Tup>, P>
    operator()(P p, Tup const& t) const noexcept { return EVE_DISPATCH_CALL(p, t); }

    EVE_CALLABLE_OBJECT(lpnorm_t, lpnorm_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var lpnorm
//!
//! @brief Callable object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n
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
//!      template< floating_value P, floating_value T, floating_value ... Ts>
//!      auto operator()(P p, T x,Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   *  `p`            :   [floating values](@ref eve::floating_value)
//!   *  `x`, `... args`:   [floating real values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   The result type is the [common value type](@ref common_value_t) of the absolute
//!   values of the  parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/lpnorm.cpp}
//!
//!  @}
//================================================================================================
inline constexpr auto lpnorm = functor<lpnorm_t>;
}
namespace eve::detail
{
  template<typename P, typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr as_wide_as_t<common_value_t<T0, T1, Ts...>, P>
  lpnorm_(EVE_REQUIRES(cpu_), O const & o, P p, T0 a0, T1 a1, Ts... args) noexcept
  {
    using c_t = common_value_t<T0, T1, Ts...>;
    using r_t = as_wide_as_t<c_t, P>;
    if constexpr( integral_value<P> )
    {
      using e_t =  element_type_t<r_t>;
      auto fp =  convert(p, eve::as<e_t>());
      return lpnorm[o](fp, r_t(a0), r_t(a1), r_t(args)...);
    }
    else
    {
      if( eve::all(p == P(2)) ) return hypot[o](r_t(a0), r_t(a1), r_t(args)...);
      else if( eve::all(p == P(1)) ) return manhattan/*[o]*/(r_t(a0), r_t(a1), r_t(args)...);
      else if( eve::all(p == eve::inf(as(p))) ) return maxabs[numeric](r_t(a0), r_t(a1), r_t(args)...);
      else
      {
        if (O::contains(pedantic2))
        {
          auto rp = r_t(p);
          auto any_is_inf = is_infinite(r_t(a0)) || (is_infinite(r_t(a1)) || ... || is_infinite(r_t(args)));
          auto e  = -maxmag(exponent(r_t(a0)), exponent(r_t(a1)), exponent(r_t(args))...);
          auto f = [&](auto a){return pow_abs(ldexp[o](r_t(a), e), rp); };
          r_t that = add(f(a0), f(a1), f(args)...);
          auto r = ldexp[pedantic](pow_abs(that, rec[pedantic](rp)), -e);
          auto isinfp = is_infinite(rp);
          auto rinf = maxabs(r_t(a0), r_t(a1), r_t(args)...);
          r = if_else(isinfp, rinf, r);
          return if_else(any_is_inf, inf(as<r_t>()), r);
        }
        else
        {
          auto rp = r_t(p);
          r_t that = add(pow_abs(r_t(a0),rp), pow_abs(r_t(a1), rp), pow_abs(r_t(args), rp)...);
          auto r = pow(that, rec[pedantic](rp));
          auto isinfp = is_infinite(rp);
          if (eve::none(isinfp)) return r;
          else return if_else(is_infinite(rp), eve::maxabs(a0, a1, args...), r);
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
