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
  template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
  requires (same_lanes_or_scalar<T0, T1>)
  EVE_FORCEINLINE constexpr eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
  { return EVE_DISPATCH_CALL(a, b); }

  EVE_CALLABLE_OBJECT(gamma_p_inv_t, gamma_p_inv_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var gamma_p_inv
//!   @brief Computes the inverse of the normalized lower incomplete \f$\Gamma\f$ function.
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
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      eve:common_value_t<T,U>  gamma_p_inv(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!  The value of the  inverse of the normalized lower incomplete \f$\Gamma\f$ function
//!  relative to the first parameter is returned as  :
//!  \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/gamma_p.cpp}
//! @}
//================================================================================================
  inline constexpr auto gamma_p_inv = functor<gamma_p_inv_t>;

  namespace detail
  {
    template<typename T, callable_options O>
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
      auto       d   = rec[pedantic2](9 * k);
      auto       omp = oneminus(p);
      auto       y   = oneminus(d - sqrt_2(as(omp)) * erfc_inv(2 * omp) * eve::sqrt(d));

      x       = if_else(notdone, k * sqr(y) * y, x);
      auto x0 = x;
      int  i  = 10;
      if( eve::none(notdone) ) return x;
      auto dgamma_p = [](auto x, auto k) { return exp(dec(k) * log(x) - x - log_abs_gamma(k)); };
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
