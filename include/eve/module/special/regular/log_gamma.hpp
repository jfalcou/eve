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
#include <eve/module/math.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve
{
  template<typename Options>
  struct log_gamma_t : elementwise_callable<log_gamma_t, Options, pedantic_option, raw_option, fast_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_gamma
//!   @brief `elementwise_callable` object computing the natural logarithm of the \f$\Gamma\f$ function.
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
//!      constexpr auto log_gamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto log_gamma[raw](floating_value auto x)                     noexcept; // 2
//!      constexpr auto log_gamma[fast](floating_value auto x)                    noexcept; // 2
//!      constexpr auto log_gamma[conditional_expr auto c](floating_value auto x) noexcept; // 3
//!      constexpr auto log_gamma[logical_value auto m](floating_value auto x)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [strictly positive real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of the  logarithm of the \f$\Gamma\f$ function is returned.
//!         this callable returns NaN if `eve::gamma(x)` is less than zero.
//!      2. speedier computations at accuracy price based on  "An accurate approximation formula for
//!         gamma function" of Zhen-Hang Yang and Jing-Feng Tian.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Log Gamma Function](https://mathworld.wolfram.com/LogGammaFunction.html
//!   *  [Zhen-Hang Yang & alias](https://pmc.ncbi.nlm.nih.gov/articles/PMC5840229/pdf/13660_2018_Article_1646.pdf)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/log_gamma.cpp}
//================================================================================================
  inline constexpr auto log_gamma = functor<log_gamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template<typename T, callable_options O>
    constexpr T
    log_gamma_(EVE_REQUIRES(cpu_), O const& o, T a0) noexcept
    {
      using elt_t = element_type_t<T>;
      if constexpr(O::contains(raw) || O::contains(fast))
      {
        if constexpr(std::same_as<elt_t, float>)
        {
          auto a0pos = eve::is_gez(a0) || eve::is_nan(a0);
          if (eve::all(a0pos))
          {
            if constexpr(O::contains(raw))
            {
              auto r = eve::fam(elt_t(-0.0810614667f) - a0 - log[o](a0), (eve::half(as<elt_t>()) + a0), eve::log[o](inc(a0)));
              return r;
            }
            else if constexpr(O::contains(fast))
            {
              T l = eve::log[o](a0*eve::inc(a0)*(2 + a0));
              T a0p3 = 3 + a0;
              auto r =eve::fam(elt_t(-2.081061466f) - a0 +  5/(6*a0p3) - l,  (elt_t(2.5) + a0), eve::log[o](a0p3));
              return r;
            }
          }
          else
          {
            auto aa0 = if_else(a0 == minf(as(a0)) || is_lez(signgam(a0)) ||(is_ltz(a0) && is_flint(a0)), allbits, a0);
            auto rp = log_gamma[o](eve::abs(aa0));
            auto rn = -log_gamma[fast](eve::abs(eve::oneminus(aa0))) + elt_t(1.144729885849400) -log[o](eve::sin[eve::radpi](aa0));
            return eve::if_else(a0pos, rp, rn);
          }
        }
        else if constexpr(std::same_as<elt_t,  double>)
        {
          auto xf = eve::convert(a0, eve::as<float>());
          return convert(log_gamma[o](xf),  eve::as<double>());
        }
      }
      else
      {
        auto aa0 = if_else(a0 == minf(as(a0)) || is_lez(signgam(a0)) ||(is_ltz(a0) && is_flint(a0)), allbits, a0);
        return log_abs_gamma(aa0);
      }
    }
  }
}
