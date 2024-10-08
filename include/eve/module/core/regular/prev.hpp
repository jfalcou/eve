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
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/is_normal.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct prev_t : strict_elementwise_callable<prev_t, Options, pedantic_option,  saturated_option, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return this->behavior(as<T>{}, eve::current_api, this->options(), v); }

    template<eve::value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(T v, N n) const noexcept
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
      return this->behavior(as<as_wide_as_t<T, N>>{}, eve::current_api, this->options(), v, n);
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
//!      // Regular overloads
//!      constexpr auto prev(value auto x)                                              noexcept; // 1
//!      constexpr auto prev(value auto x, integral_value auto n)                       noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto prev[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto prev[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto prev[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto prev[saturated ](/* any of the above overloads */)              noexcept; // 5
//!      constexpr auto prev[raw](value auto x)                                         noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating argument](@ref eve::floating_value).
//!     * `n`: [integral value argument](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. the greatest representable value less than `x` is returned.
//!       2. the nth representable value less than `x` is returned. If `n` is zero returns `x`.
//!       3. [The operation is performed conditionnaly](@ref conditional)
//!       4. if `x` is floating  zero and mzero are considered distinct.
//!       5. ensures that the input is never less than the result of the call.
//!       6. works only if inputs are normal numbers (this excludes floating zeroes, denormals or not finite).
//!          the option has no influence on the two parameters calls
//!
//!    If `n` is zero returns `x`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/prev.cpp}
//================================================================================================
  inline constexpr auto prev = functor<prev_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(raw))
        {
          auto s = ieee_constant<0x1.000002p-24f, 0x1.0000000000001p-53>(as(a));
          return fnma[pedantic](s, eve::abs(a), a);
        }
        if (eve::all( eve::is_normal(a))) return prev[raw](a);
        if constexpr(O::contains(pedantic))
        {
          auto pz   = bitinteger(a);
          auto z    = bitfloating(pz-one(as(pz)));
          auto test = is_negative(z) && is_positive(a);
          auto prv = if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
          prv =  if_else(is_nan(a), eve::allbits, prv);
          if  constexpr(O::contains(saturated))
          {
            prv = if_else(a == minf(as(a)), a, prv);
            if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, prv);
          }
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), prv);
        }
        else if  constexpr(O::contains(saturated))
        {
          auto prv = prev(a);
          auto z = if_else(a == minf(as(a)), a, prv);
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
        {
          auto bi = bitinteger(a);
          return bitfloating(bi - one(as(bi)));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated) || O::contains(pedantic))
        {
          return if_else(a == valmin(as(a)), a, T(a-one(as(a))));
        }
        else
        {
          return T(a-one(as(a)));
        }
      }
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic))
        {
          using i_t = as_integer_t<T>;
          auto vz   = bitinteger(a) - convert(n, as<element_type_t<i_t>>());
          auto pz   = vz + one(as(vz));
          auto z    = bitfloating(pz-one(as(pz)));
          auto test = is_negative(z) && is_positive(a);
          if constexpr( scalar_value<T> && scalar_value<N> )
          {
            if( is_nan(a) ) return a;
            return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
          }
          else { return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z); }
        }
        else if  constexpr(O::contains(saturated))
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
        if  constexpr(O::contains(saturated) || O::contains(pedantic))
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
