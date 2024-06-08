//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/none.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/regular/zip.hpp>

namespace eve
{
template<typename Options>
struct rat_t : elementwise_callable<rat_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE zipped<T,T>
  operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  template<eve::floating_value T, eve::floating_value U>
  constexpr EVE_FORCEINLINE zipped<common_value_t<T,U>,common_value_t<T,U>>
  operator()(T v, U t) const  { return EVE_DISPATCH_CALL(v, t); }

  EVE_CALLABLE_OBJECT(rat_t, rat_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rat
//!   @brief Computes a rational approximation.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template<eve::floating_value T>
//!      eve::zipped<T,T> rat(T x, T tol = T(1.0e-6)*eve::abs(x)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `tol`: [floating_value](@ref eve::value). By  default `tol`
//!       is equal to `T(1.0e-6)*``eve::abs``(x)`.
//!
//!   **Return value**
//!
//!     A tuple of values with the same type as `x` containing the
//!     [elementwise](@ref glossary_elementwise) numerator and denominator of the rational
//!     number approximating `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rat.cpp}
//! @}
//================================================================================================
inline constexpr auto rat = functor<rat_t>;

namespace detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto rat_(EVE_REQUIRES(cpu_), O const& o, T const& x) noexcept
  {
    return rat[o](x, T(1.0e-6) * eve::abs(x));
  }

  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr auto
  rat_(EVE_REQUIRES(cpu_), O const&, T const& x, T const& tol) noexcept
  {
     if constexpr(scalar_value<T>)
    {
      if( is_infinite(x) || is_eqz(x) ) return zip(sign(x), T{0});
      auto n     = nearest(x);
      auto d     = one(as(x));
      auto frac  = x - n;
      auto lastn = one(as(x));
      auto lastd = zero(as(x));

      while( abs(x - n / d) >= tol )
      {
        auto flip   = rec[pedantic2](frac);
        auto step   = nearest(flip);
        frac        = flip - step;
        auto savedn = n;
        auto savedd = d;
        n           = fma(n, step, lastn);
        d           = fma(d, step, lastd);
        lastn       = savedn;
        lastd       = savedd;
      }
      n *= sign(d);
      d = eve::abs(d);
      return zip(n, d);
    }
    else
    {
      auto is_inf = is_infinite(x);
      auto y      = if_else(is_inf, zero, x);
      auto n      = nearest(y);
      auto d      = one(as(y));
      auto frac   = y - n;
      auto lastn  = one(as(y));
      auto lastd  = zero(as(y));

      while( true )
      {
        auto notdone = is_nez(y) && (abs(y - n / d) >= tol);
        if( none(notdone) ) break;
        auto flip   = rec[notdone][pedantic2](frac);
        auto step   = if_else(notdone, nearest(flip), zero);
        frac        = flip - step;
        auto savedn = n;
        auto savedd = d;
        n           = fma[notdone](n, step, lastn);
        d           = fma[notdone](d, step, lastd);
        lastn       = savedn;
        lastd       = savedd;
      }
      n *= sign(d);
      d = abs(d);
      n = if_else(is_inf, sign(x), n);
      d = if_else(is_inf, zero, d);
      return zip(n, d);
    }
  }
}
}
