//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/detail/next_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct prev_t : strict_elementwise_callable<prev_t, Options, pedantic_option,  saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_value N>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(T v, N n) const noexcept
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
      return EVE_DISPATCH_CALL(v, n);
    }

    EVE_CALLABLE_OBJECT(prev_t, prev_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var prev
//!   @brief Computes the nth previous representable element
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
//!      template< eve::value T, eve::integral_value N >
//!      eve::common_value_t<T, U> prev(T x, N n = 1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating argument](@ref eve::floating_value).
//!
//!     * `n` :  [integral value argument](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!    The value of the nth representable value less than `x` is returned.
//!    If `n` is zero returns `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/prev.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::prev[mask](x, ...)` provides a masked
//!     version of `prev` which is
//!     equivalent to `if_else(mask, prev(x, ...), x)`
//!
//!   * eve::pedantic
//!
//!     The call `eve::prev[eve::pedantic](x, ...)` provides a pedantic
//!     version of `prev` which ensures that the predecessor of eve::zero is  eve::mzero
//!     for floating points entries
//!
//!   * eve::saturated
//!
//!     The call `eve::prev[eve::saturated](x, ...)` provides a saturated
//!     version of `prev` which ensures that that x is never greater than the result of the call.
//!//! @}
//================================================================================================
  inline constexpr auto prev = functor<prev_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic2))
        {
          auto pz   = bitinteger(a);
          auto z    = bitfloating(dec(pz));
          auto test = is_negative(z) && is_positive(a);
          auto prv = if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
          prv =  if_else(is_nan(a), eve::allbits, prv);
          if  constexpr(O::contains(saturated2))
          {
            prv = if_else(a == minf(as(a)), a, prv);
            if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, prv);
          }
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), prv);
        }
        else if  constexpr(O::contains(saturated2))
        {
          auto prv = prev(a);
          auto z = if_else(a == minf(as(a)), a, prv);
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
          return bitfloating(dec(bitinteger(a)));
      }
      else
      {
        if  constexpr(O::contains(saturated2) || O::contains(pedantic2))
        {
          return if_else(a == valmin(as(a)), a, dec(a));
        }
        else
        {
          return dec(a);
        }
      }
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic2))
        {
          using i_t = as_integer_t<T>;
          auto pz   = inc(bitinteger(a) - convert(n, as<element_type_t<i_t>>()));
          auto z    = bitfloating(dec(pz));
          auto test = is_negative(z) && is_positive(a);
          if constexpr( scalar_value<T> && scalar_value<N> )
          {
            if( is_nan(a) ) return a;
            return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
          }
          else { return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z); }
        }
        else if  constexpr(O::contains(saturated2))
        {
          auto prv = prev(a, n);
          auto z = if_else(a >  prv || is_nan(prv), minf(as(a)), prv);
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
        {
          using i_t =as_integer_t<element_type_t<T>>;
          return bitfloating(bitinteger(a) - convert(n, as<i_t>()));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated2) || O::contains(pedantic2))
        {
          auto tmp = prev(a, n);
          return if_else(a < tmp, a, tmp);
        }
        else
        {
          return a-convert(n, as<element_type_t<T>>());
        }
      }
    }
  }
}
