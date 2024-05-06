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
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/saturated/add.hpp>
#include <eve/module/core/regular/inc.hpp>

namespace eve
{
  template<typename Options>
  struct next_t : strict_elementwise_callable<next_t, Options, pedantic_option,  saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_value N>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(T v, N n) const noexcept
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
      return EVE_DISPATCH_CALL(v, n);
    }

    EVE_CALLABLE_OBJECT(next_t, next_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var next
//!   @brief Computes the nth next representable element
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
//!      eve::common_value_t<T, U> next(T x, N n = 1) noexcept;
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
//!    The value of the nth representable value greater than `x` is returned.
//!    If `n` is zero returns `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/next.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::next[mask](x, ...)` provides a masked
//!     version of `next` which is
//!     equivalent to `if_else(mask, next(x, ...), x)`
//!
//!   * eve::pedantic
//!
//!     The call `eve::next[eve::pedantic](x, ...)` provides a pedantic
//!     version of `next` which ensures that the successor of eve::mzero is  eve::zero
//!     for floating points entries
//!
//!   * eve::saturated
//!
//!     The call `eve::next[eve::saturated](x, ...)` provides a saturated
//!     version of `next` which ensures that x is never less than the result of the call.
//!
//! @}
//================================================================================================
  inline constexpr auto next = functor<next_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    next_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic2))
        {
          auto pz   = bitinteger(a);
          auto z    = bitfloating(inc(pz));
          auto test = is_negative(a) && is_positive(z);
          auto nxt = if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
          if  constexpr(O::contains(saturated2))
          {
            nxt = if_else(a == inf(as(a)), a, nxt);
            if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          }
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), nxt);
        }
        else if  constexpr(O::contains(saturated2))
        {
          auto z = if_else(a == inf(as(a)), a, next(a));
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
          return bitfloating(inc(bitinteger(a)));
      }
      else
      {
        if  constexpr(O::contains(saturated2) || O::contains(pedantic2))
        {
          return if_else(a == valmax(as(a)), a, inc(a));
        }
        else
        {
          return inc(a);
        }
      }
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    next_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic2))
        {
          using i_t = as_integer_t<T>;
          auto pz   = dec(bitinteger(a) + convert(n, as<element_type_t<i_t>>(n)));
          auto z    = bitfloating(inc(pz));
          auto test = is_negative(a) && is_positive(z);
          if constexpr( scalar_value<T> && scalar_value<N> )
          {
            if( is_nan(a) ) return a;
            return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
          }
          else { return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z); }
        }
        else if  constexpr(O::contains(saturated2))
        {
          auto nxt = next(a, n);
          auto z = if_else(a != inf(as(a)) && nxt == nan(as(a)), inf(as(a)), nxt);
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
        {
          using i_t =as_integer_t<element_type_t<T>>;
          return bitfloating(bitinteger(a) + convert(n, as<i_t>()));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated2) || O::contains(pedantic2))
        {
          auto tmp = next(a, n);
          return if_else(a > tmp, a, tmp);
        }
        else
        {
          return a+convert(n, as<element_type_t<T>>());
        }
      }
    }
  }
}
