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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct cot_t : elementwise_callable<cot_t, Options, quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(cot_t, cot_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var cot
  //! @brief `elementwise_callable` object computing the cotangent of the input.
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
  //!      constexpr auto cot(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto cot[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto cot[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto cot[quarter_circle](floating_value auto x)          noexcept; // 3.a
  //!      constexpr auto cot[half_circle](floating_value auto x)             noexcept; // 3.b
  //!      constexpr auto cot[full_circle](floating_value auto x)             noexcept; // 3.c
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
  //!      In particular:
  //!        * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
  //!        * If the element is \f$\pm\infty\f$, Nan is returned.
  //!        * If the element is a `Nan`, `Nan` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. These are optimized calls providing a balance between speed and range limitation.
  //!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
  //!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
  //!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Cotangent.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/cot.cpp}
  //================================================================================================
  inline constexpr auto cot = functor<cot_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cot_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      auto x =  eve::abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        auto aa0nlepio4 = is_not_less_equal(x, pio_4(eve::as<T>()));
        if constexpr( scalar_value<T> )
        {
          return (aa0nlepio4) ? nan(eve::as<T>()) : rec[pedantic](tancot_eval(a0));
        }
        else { return if_else(aa0nlepio4, eve::allbits, rec[pedantic](tancot_eval(a0))); }
      }
      else if constexpr(O::contains(half_circle))
      {
        auto xleeps = x <= eps(as<T>());
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});
            auto xr     = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;
          if( xleeps ) return rec[pedantic](a0);
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          i_t n = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            T    y  = tancot_eval(xr);
            return bit_xor(bitofsign(a0), -y);
          }
          else { return rec[pedantic](tancot_eval(a0)); }
        }
        else
        {
          auto xnlepio4 = is_not_less_equal(x, pio_4(eve::as(x)));
          auto fn       = one[xnlepio4](eve::as(x));
          auto xr       = if_else(fn, reduce(x), x);
          auto y        = tancot_eval(xr);
          y             = if_else(is_not_finite(a0), eve::allbits, if_else(xnlepio4, -y, rec[pedantic](y)));
          return if_else(xleeps, rec[pedantic](a0), bit_xor(bitofsign(a0), y));
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return cot_finalize(a0, fn, xr, dxr);
      }
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return cot[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return cot[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return cot[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return cot[medium](a0);
        else
          return cot[big](a0);
      }
    }
  }
}
