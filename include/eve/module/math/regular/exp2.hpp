//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct exp2_t : strict_elementwise_callable<exp2_t, Options, pedantic_option, saturated_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr T operator()(T s) const noexcept
    {
      if constexpr(eve::integral_value<T>)
      {
        using vt_t = eve::element_type_t<T>;
        EVE_ASSERT(eve::all(is_gez(s)), "[eve::exp2] - with integral entries the parameter element(s) must be greater than 0");
        EVE_ASSERT(eve::all(is_less(s, sizeof(vt_t) * 8 - std::is_signed_v<vt_t>)), "[eve::exp2] - overflow caused by too large integral entry");
      }
      return EVE_DISPATCH_CALL(s);
    }

    template<eve::integral_value T, floating_scalar_value U>
    EVE_FORCEINLINE constexpr eve::as_wide_as_t<U, T>operator()(T v, eve::as<U> target ) const noexcept
    {
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(exp2_t, exp2_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var exp2
//!
//! @brief Callable object computing \f$2^x\f$.
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
//!      template< eve::ordered_value T >
//!      T exp2(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [ordered value](@ref eve::ordered_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) exponential of base 2 of the input.
//!       In particular, for floating inputs:
//!
//!       * If the element is \f$\pm0\f$, \f$1\f$ is returned
//!       * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!       * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!       * If the element is a `NaN`, `NaN` is returned
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/exp2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::exp2[mask](x)` provides a masked version of `eve::exp2` which is
//!     equivalent to `if_else (mask, exp2(x), x)`.
//!
//!     **Example**
//!
//!     @godbolt{doc/math/masked/exp2.cpp}
//!  @}
//================================================================================================
  inline constexpr auto exp2 = functor<exp2_t>;

  namespace detail
  {
    template<ordered_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    exp2_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      if constexpr(floating_value<T>)
      {
        using elt_t    = element_type_t<T>;
        auto minlogval = []()
          {
            if constexpr(O::contains(pedantic2) && eve::platform::supports_denormals)
            return minlog2denormal(eve::as<T>());
            else
              return minlog2(eve::as<T>());
          };
        auto xltminlog2 = x <= minlogval();
        auto xgemaxlog2 = x >= maxlog2(eve::as(x));
        if constexpr( scalar_value<T> )
        {
          if( is_nan(x)  ) return nan(eve::as(x));
          if( xgemaxlog2 ) return inf(eve::as(x));
          if( xltminlog2 ) return zero(eve::as(x));
        }
        auto k = nearest(x);
        x      = x - k;
        if constexpr( std::is_same_v<elt_t, float> )
        {
          T y =
            eve::reverse_horner(x, T(0x1.ebfbe2p-3f), T(0x1.c6add6p-5f)
                                , T(0x1.3b2844p-7f), T(0x1.602430p-10f), T(0x1.459188p-13f));
          x   = inc(fma(y, sqr(x), x * log_2(eve::as<T>())));
        }
        else if constexpr( std::is_same_v<elt_t, double> )
        {
          x *= log_2(eve::as<T>());
          T    t = sqr(x);
          auto h =
            eve::reverse_horner(t, T(0x1.555555555553ep-3), T(-0x1.6c16c16bebd93p-9)
                                , T(0x1.1566aaf25de2cp-14), T(-0x1.bbd41c5d26bf1p-20), T(0x1.6376972bea4d0p-25));
          T    c = fnma(t, h, x); // x-h*t
          x      = oneminus(((-(x * c) / (T(2) - c)) - x));
        }
        auto z = ldexp[pedantic](x, k);
        if constexpr( simd_value<T> )
        {
          z = if_else(is_nan(x),  x, z);
          z = if_else(xltminlog2, eve::zero, z);
          z = if_else(xgemaxlog2, inf(eve::as(x)), z);
        }
        return z;
      }
      else  // integral value
      {
        element_type_t<T> constexpr siz = sizeof(element_type_t<T>) * 8 - 1;
        auto test                       = is_ltz(x) || (x > siz);
        x                               = if_else(test, zero, x);
        auto tmp                        = if_else(test, eve::zero, shl(one(eve::as(x)), x));
        if constexpr( O::contains(saturated2))
        {
          using elt_t = element_type_t<T>;
          return if_else(is_gez(x, T(sizeof(elt_t))), valmax(eve::as<T>()), tmp);
        }
        else
          return tmp;
      }
    }

    template<ordered_value T, floating_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<U, T>
    exp2_(EVE_REQUIRES(cpu_), O const&, T xx, as<U> const & ) noexcept
    {
      using b_t = as_wide_as_t<U, T>;
      using i_t  = as_integer_t<b_t>;
      auto x  = to_<i_t>(xx);
      auto isnez  = is_nez(x);
      auto zz = eve::min(x + maxexponent(eve::as<U>()), 2 * maxexponent(eve::as<U>()) + 1) & isnez.mask();
      zz = zz << nbmantissabits(eve::as<U>());
      return if_else(isnez, bit_cast(zz, as<b_t>()), one);
    }
  }
}
