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
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fnma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqpz.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_pinf.hpp>
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
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
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
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
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
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    requires(!O::contains(pedantic) || !floating_value<T>)
    {
      if constexpr( floating_value<T>)
      {
        if constexpr(O::contains(raw))
        {
          auto s = ieee_constant<0x1.0000000000001p-53, 0x1.000002p-24f, 0x1.004p-11f>(as(a));
          return fnma[pedantic](s, eve::abs(a), a);
        }
        if (eve::all( eve::is_normal(a))) return prev[raw](a);
        else
        {
          auto bi = bitinteger(a);
          if constexpr(scalar_value<T>)
          {
            using v_t = eve::as_integer_t<T, signed>;
            return bitfloating(  v_t(bi- one(as(bi))));
          }
          else
            return bitfloating(  bi- one(as(bi)));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated))
        {
          return if_else(a == valmin(as(a)), a, T(a-one(as(a))));
        }
        else
        {
          return T(a-one(as(a)));
        }
      }
    }

    template<floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr T prev_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    requires(O::contains(pedantic))
    {
      if (eve::all( eve::is_normal(a))) return prev[raw](a);
      auto pz   = bitinteger(a);
      T z = bitfloating(call_sub(pz, one(as(pz))));
      auto testm0 = is_eqpz(a);
      auto prv = if_else(testm0, mzero(as(a)), z);
      if (eve::all(is_finite(a))) return prv;
      prv = if_else(eve::is_pinf(a), eve::valmax(eve::as(a)), prv);
      if constexpr( eve::platform::supports_nans ) prv = if_else(is_nan(a), eve::allbits, prv);
      if constexpr(O::contains(saturated))         prv = if_else(is_minf(as(a)), a, prv);
      return prv;
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    requires(!O::contains(pedantic) || !floating_value<T>)
    {
      if constexpr( floating_value<T>)
      {
        using v_t = eve::as_integer_t<T, signed>;
        v_t bi = bitinteger(a);
        if constexpr(scalar_value<T>) return bitfloating(v_t{ bi - n });
        else                          return bitfloating(bi - convert(n, as_element(bi)));
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
          return T(a-convert(n, as<element_type_t<T>>()));
        }
      }
    }

    template<floating_value T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    prev_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    requires(O::contains(pedantic))
    {
      using i_t = as_integer_t<T>;
      i_t bmn   = bitinteger(a) - convert(n, eve::as<element_type_t<i_t>>(n));
      auto prv = bitfloating(bmn);
      auto fbmnp1 = bitfloating(call_add(bmn, one(as(bmn))));
      prv = if_else(is_positive(a) && is_negative(fbmnp1), fbmnp1, prv);
      prv = if_else(is_eqpz(fbmnp1), mzero, prv);
      if constexpr( eve::platform::supports_nans ) prv = if_else(is_nan(a), a, prv);
      if constexpr(O::contains(saturated))         prv = if_else(is_minf(a), minf(as(a)), prv);
      return prv;
    }
  }
}
