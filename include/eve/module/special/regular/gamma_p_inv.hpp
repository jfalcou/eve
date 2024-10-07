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
#include <eve/module/special/regular/erfc_inv.hpp>
#include <eve/module/special/regular/gamma_p.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
template<typename Options>
struct gamma_p_inv_t : elementwise_callable<gamma_p_inv_t, Options>
{
  template<floating_value T0, floating_value T1>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    requires (same_lanes_or_scalar<T0, T1>)
  {
    return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1>), a, b);
  }

  EVE_CALLABLE_OBJECT(gamma_p_inv_t, gamma_p_inv_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var gamma_p_inv
//!   @brief `elementwise_callable` object computing  the inverse of the normalized lower
//!          incomplete \f$\Gamma\f$ function.
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
//!      constexpr auto gamma_p_inv(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gamma_p_inv[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto gamma_p_inv[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!    1. The value of the  inverse of the normalized lower incomplete \f$\Gamma\f$ function
//!       relative to the first parameter is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Incomplete gamma function](https://en.wikipedia.org/wiki/Incomplete_gamma_function)
//!   *  [DLMF](https://dlmf.nist.gov/8.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/gamma_p.cpp}
//================================================================================================
  inline constexpr auto gamma_p_inv = functor<gamma_p_inv_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr auto  gamma_p_inv_(EVE_REQUIRES(cpu_), O const&, T p, T k) noexcept
    {
      if constexpr( std::is_same_v<element_type_t<T>, float> )
      {
        return convert(gamma_p_inv(convert(p, as<double>()), convert(k, as<double>())), as<float>());
      }
      p                 = if_else(is_ltz(p) || p > one(as(p)), allbits, p);
      auto       iseqzp = is_eqz(p);
      auto       iseq1p = p == one(as(p));
      auto       x      = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), allbits));
      logical<T> notdone(is_not_nan(p) && !iseqzp && !iseq1p);
      auto       d   = rec[pedantic](9 * k);
      auto       omp = oneminus(p);
      auto       y   = oneminus(d - sqrt_2(as(omp)) * erfc_inv(2 * omp) * eve::sqrt(d));

      x       = if_else(notdone, k * sqr(y) * y, x);
      auto x0 = x;
      int  i  = 10;
      if( eve::none(notdone) ) return x;
      auto dgamma_p = [](auto px, auto pk) { return exp(dec(pk) * log(px) - px - log_abs_gamma(pk)); };
      while( i )
      {
        auto dx = if_else(notdone, (gamma_p(x, k) - p) / dgamma_p(x, k), zero);
        x -= dx;
        if( i < 7 )
          notdone = notdone && is_not_less(abs(dx), 4 * eps(as(x)) * max(eve::abs(x), one(as(x))));
        if( eve::none(notdone) ) return x;
        --i;
      }

      notdone  = notdone || is_ltz(y);
      x        = if_else(notdone, eve::abs(x0), x);
      auto xlo = if_else(notdone, eve::min(x / 2, zero(as(x))), x);
      auto xhi = if_else(notdone, eve::min(x * 2, eve::valmax(as(x))), x);
      auto inl = ((gamma_p(xlo, k) > p) || (gamma_p(xhi, k) < p)) && (xlo != xhi);
      while( eve::any(inl) )
      {
        xlo = if_else(inl, eve::max(xlo / 2, zero(as(x))), xlo);
        xhi = if_else(inl, eve::min(xhi * 2, eve::valmax(as(x))), xhi);
        inl = ((gamma_p(xlo, k) > p) || (gamma_p(xhi, k) < p)) && (xlo != xhi);
      }
      auto xmed = average(xlo, xhi);
      while( eve::any(notdone) )
      {
        auto gmp  = gamma_p(xmed, k);
        auto test = (gmp < p);
        xlo       = if_else(test, xmed, xlo);
        xhi       = if_else(test, xhi, xmed);
        notdone   = (ulpdist(xlo, xhi) > 1) && gmp != 0;
        xmed      = average(xlo, xhi);
      }
      xmed = if_else(iseq1p, inf(as(p)), if_else(iseqzp, zero(as(p)), xmed));
      return if_else(k == one(as(k)), -eve::log1p(-p), xmed);
    }
  }
}
