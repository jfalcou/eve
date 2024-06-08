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
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve
{
  template<typename Options>
  struct geommean_t : tuple_callable<geommean_t, Options, pedantic_option>
  {
    template<eve::value T0, eve::value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0,T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0,T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept  requires(kumi::size_v<Tup> >= 2)  { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(geommean_t, geommean_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var geommean
//!
//! @brief Callable object computing the geometric mean of the inputs.\f$ \left(\prod_{i = 1}^n
//! x_i\right)^{1/n} \f$.
//!
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
//!      template<floating_value T, floating_value ... Ts>
//!      auto geommean( T x, Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   ``x`, `... args`:   [floating real values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   *  The geometric mean of the inputs is returned
//!
//!   *  The result type is the [common value type](@ref common_value_t) of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/geommean.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::geommean[mask](x, ...)` provides a masked version of `eve::geommean` which is
//!     equivalent to `if_else (mask, geommean(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/geommean.cpp}
//!  @}
//================================================================================================
 inline constexpr auto geommean = functor<geommean_t>;

  namespace detail
  {
    template<typename T0,typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    geommean_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... args) noexcept
    {

      using r_t   = common_value_t<T0, T1, Ts...>;
      using elt_t = element_type_t<r_t>;
      constexpr std::uint64_t sz = sizeof...(Ts);
      if constexpr(sz == 0)
      {
        auto a = r_t(a0);
        auto b = r_t(a1);
        if (O::contains(pedantic2))
        {
          auto m  = max(a, b);
          auto im = if_else(is_nez(m), rec[pedantic2](m), m);
          auto z  = min(a, b) * im;
          return if_else(is_nltz(a) || is_nltz(b), sqrt(z) * m, allbits);
        }
        else
        {
          return if_else(is_nltz(sign(a)*sign(b)), sqrt(abs(a))*sqrt(abs(b)), allbits);
        }
      }
      else
      {
        elt_t invn  = rec[pedantic2](elt_t(sizeof...(args) + 2u));
        if (O::contains(pedantic2))
        { //perhaps this is always more efficient TODO bench it
          auto e  = -maxmag(exponent(r_t(a0)), exponent(r_t(a1)), exponent(r_t(args))...);
          auto p  = mul( r_t(ldexp[o](a0, e)), r_t(ldexp[o](a1, e)), r_t(ldexp[o](args, e))...);
          auto sgn = sign(p);
          p = pow_abs(p, invn);
          p = ldexp[pedantic](p, -e);
          return if_else(eve::is_even(sz) && is_ltz(sgn), eve::allbits, sgn * p);
        }
        else
        {
          r_t   that(pow_abs(r_t(a0), invn) * pow_abs(r_t(a1), invn));
          r_t   sgn  = sign(r_t(a0)) * sign(r_t(a1));
          auto  next = [&](auto avg, auto x){
            sgn *= sign(x);
            return avg * pow_abs(r_t(x), invn);
          };
          ((that = next(that, args)), ...);
          return if_else(eve::is_even(sz) && is_ltz(sgn), eve::allbits, sgn * that);
        }
      }
    }
  }
}
