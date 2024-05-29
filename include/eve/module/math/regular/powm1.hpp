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
#include <eve/module/math/regular/pow.hpp>

namespace eve
{
  template<typename Options>
  struct powm1_t : elementwise_callable<powm1_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::value T, eve::value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(powm1_t, powm1_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var powm1
//!
//! @brief Callable object computing powm1: \f$x^y-1\f$.
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
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto powm1(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real values](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) power minus one, with good accuracy,
//! even when `y` is very small, or when `x` is close to 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/powm1.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::powm1[mask](x, y)` provides a masked version of `eve::powm1` which is
//!     equivalent to `if_else (mask, powm1(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/powm1.cpp}
//!  @}
//================================================================================================
  inline constexpr auto powm1 = functor<powm1_t>;

  namespace detail
  {

    template<floating_scalar_value T, integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    powm1_(EVE_REQUIRES(cpu_), O const & o, T a0, U a1) noexcept
    {
      return powm1[o](a0, T(a1));
    }

    template<typename T,  typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    powm1_(EVE_REQUIRES(cpu_), O const & o, T a, U b) noexcept
    {
      using r_t =  common_value_t<T, U>;
      if constexpr(O::contains(raw2))
      {
        return dec(pow[o](a, b));
      }
      else
      {
        if constexpr( has_native_abi_v<r_t> )
        {
          auto x = r_t(a);
          auto y = r_t(b);
          auto r = dec(pow(x, y));
          auto test = (abs(y * dec(x)) < r_t(0.5) || (abs(y) < r_t(0.2)));
          if( eve::any(test) )
          {
            // We don't have any good/quick approximation for log(x) * y
            // so just try it and see:
            auto l = y*log_abs(x);
            auto tmp0 = expm1(l);
            auto tmp1 = minus[is_ltz(x) && is_odd(x)](tmp0);
            return if_else(l < T(0.5), tmp1, r);
          }
          else return r;
        }
        else return apply_over(powm1, a, b);
      }
    }
  }
}
