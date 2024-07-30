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
#include <eve/module/core.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>
#include <eve/module/math/constant/invlog10_2.hpp>
#include <eve/module/math/constant/maxlog10.hpp>
#include <eve/module/math/constant/minlog10.hpp>
#include <eve/module/math/constant/minlog10denormal.hpp>

namespace eve
{
  template<typename Options>
  struct exp10_t : elementwise_callable<exp10_t, Options, pedantic_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(exp10_t, exp10_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var exp10
//!
//! @brief Callable object computing  \f$10^x\f$.
//!
//!   @groupheader{Header file}
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
//!      constexpr auto exp10(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto exp10[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto exp10[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1.  Returns the [elementwise](@ref glossary_elementwise) exponential of base 10 of the input.
//!       In particular, for floating inputs:
//!       * If the element is \f$\pm0\f$, \f$1\f$ is returned
//!       * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!       * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!       * If the element is a `NaN`, `NaN` is returned
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/exp10.cpp}
//================================================================================================
  inline constexpr auto exp10 = functor<exp10_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T exp10_(EVE_REQUIRES(cpu_), O const& , T x)
    {
      using elt_t  = element_type_t<T>;

      // Adapt lower bound depending on options
      auto minlogval = [&]()
        {
          if constexpr((eve::platform::supports_denormals) && O::contains(pedantic2))
          return minlog10denormal(as(x));
          else
            return minlog10(as(x));
        };

      const T Log10_2hi   = ieee_constant<0x1.3400000p-2f, 0x1.3440000000000p-2>(as(x));
      const T Log10_2lo   = ieee_constant<0x1.04d4280p-12f, 0x1.3509f79fef312p-18>(as(x));
      auto    xltminlog10 = x <= minlogval();
      auto    xgemaxlog10 = x >= maxlog10(as(x));

      // Scalar early returns
      if constexpr( scalar_value<T> )
      {
        if( is_nan(x)   ) return nan(as(x));
        if( xgemaxlog10 ) return inf(as(x));
        if( xltminlog10 ) return zero(as(x));
      }

      auto c = nearest(invlog10_2(as(x)) * x);
      auto k = c;
      x      = fnma(c, Log10_2hi, x);
      x      = fnma(c, Log10_2lo, x);

      if constexpr( std::same_as<elt_t, float> )
      {
        c = inc ( eve::reverse_horner ( x
                                      , T(0x1.26bb1cp+1f), T(0x1.53524cp+1f), T(0x1.046fb4p+1f)
                                      , T(0x1.2bd698p+0f), T(0x1.1559dep-1f), T(0x1.a9bfe2p-3f)
                                      ) * x
                );
      }
      else if constexpr( std::same_as<elt_t, double> )
      {
        T xx = sqr(x);
        T px = x * eve::reverse_horner( xx
                                      , T(0x1.2b4798e134a01p+11)
                                      , T(0x1.96b7a050349e4p+8)
                                      , T(0x1.77d9474c55934p+3)
                                      , T(0x1.4fd75f3062dd4p-5)
                                      );
        T x2 = px / (eve::reverse_horner( xx
                                        , T(0x1.03f37650df6e2p+11)
                                        , T(0x1.3e05eefd67782p+10)
                                        , T(0x1.545fdce51ca08p+6)
                                        , T(0x1.0p0)
                                        ) - px
                    );
        c = inc(x2 + x2);
      }

      auto z = ldexp[pedantic](c, k);

      // SIMD value fixes
      if constexpr( simd_value<T> )
      {
        z = if_else(is_nan(x), x, z);
        z = if_else(xltminlog10, zero, z);
        z = if_else(xgemaxlog10, inf(as(x)), z);
      }
      return z;
    }
  }
}
