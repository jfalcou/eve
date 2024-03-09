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
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>

namespace eve
{
template<typename Options>
struct acos_t : elementwise_callable<acos_t, Options, raw_option>
{
  template<eve::floating_ordered_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(acos_t, acos_);
};

//======================================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var acos
//!
//! @brief Callable object computing the arc cosine.
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
//!     template< eve::floating_ordered_value T > T acos(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating ordered value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!    * Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//!      input in the range \f$[0 , \pi]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acos.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!     The call `acos[raw](x)` uses a faster implementation which can be slightly less accurate near 1.
//!  @}
//======================================================================================================================
inline constexpr auto acos = functor<acos_t>;

namespace detail
{
  template<typename T, callable_options O>
  constexpr EVE_FORCEINLINE T acos_(EVE_REQUIRES(cpu_), O const&, T const& a0)
  {
    if constexpr(O::contains(raw2))
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto tmp  = pio_2(eve::as(a0))
                  + (ieee_constant<-0x1.777a5c0p-25f, 0x1.1a62633145c07p-54>(eve::as<T>{}) - asin(a0));
        return if_else(a0 == T(1), eve::zero, tmp);
      }
      else return apply_over(acos[raw], a0);
    }
    else
    {
      if constexpr( simd_value<T> )
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto const half  = eve::half(eve::as(a0));
          auto const mhalf = eve::mhalf(eve::as(a0));

          auto x           = eve::abs(a0);
          auto x_larger_05 = x > half;

          x = if_else(x_larger_05, eve::sqrt(fma(mhalf, x, half)), a0);
          x = asin(x);
          x = add[x_larger_05](x, x);
          x = eve::if_else((a0 < mhalf), eve::pi(eve::as(a0)) - x, x);

          return eve::if_else(x_larger_05, x, eve::pio_2(eve::as(a0)) - x);
        }
        else return apply_over(acos, a0);
      }
      else if constexpr( scalar_value<T> )
      {
        if( a0 == T(1) )          return T(0);
        if( eve::abs(a0) > T(1) ) return nan(eve::as<T>());

        if constexpr( std::same_as<T, float> )
        {
          if( a0 < -0.5f )      return pi(eve::as<T>()) - 2.0f * eve::asin(eve::sqrt(inc(a0) * 0.5f));
          else if( a0 > 0.5f )  return 2.0f * eve::asin(eve::sqrt(oneminus(a0) * 0.5f));
          else                  return pio_2(eve::as<T>()) - eve::asin(a0);
        }
        else if constexpr( std::same_as<T, double> )
        {
          if( a0 > 0.5 ) return 2.0 * eve::asin(eve::sqrt(fma(-0.5, a0, 0.5)));

          T const pio4 = pio_4(eve::as<T>());

          T z = pio4 - eve::asin(a0);
          z += T(0x1.1a62633145c07p-55); // Pio_4lo(as<T>());
          z += pio4;

          return z;
        }
      }
    }
  }
}
}
