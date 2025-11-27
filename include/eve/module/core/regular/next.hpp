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
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqmz.hpp>
#include <eve/module/core/regular/is_minf.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/is_pinf.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/regular/is_normal.hpp>
#include <eve/module/core/regular/is_denormal.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/none.hpp>

namespace eve
{
  template<typename Options>
  struct next_t : strict_elementwise_callable<next_t, Options, pedantic_option,  saturated_option, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(T v, N n) const noexcept
    {
      EVE_ASSERT(eve::all(n >= 0), "[eve::next] : second parameter must be positive");
      return EVE_DISPATCH_CALL(v, n);
    }

    EVE_CALLABLE_OBJECT(next_t, next_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var next
//!   @brief `strict_elementwise_callable` computing the nth next representable element
//!
//!   @groupheader{Header file}
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
//!      constexpr auto next(value auto x)                                              noexcept; // 1
//!      constexpr auto next(value auto x, integral_value auto n)                       noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto next[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto next[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto next[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto next[saturated ](/* any of the above overloads */)              noexcept; // 5
//!      constexpr auto next[raw](value auto x)                                         noexcept; // 6
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
//!       1. the least representable value greater than `x` is returned.
//!       2. the nth representable value greater than `x` is returned. If `n` is zero returns `x`.
//!       3. [The operation is performed conditionnaly](@ref conditional)
//!       4. if `x` is floating the call with mzero returns zero
//!       5. ensures that the input is never greater than the result of the call.
//!       6. works only if inputs are normal numbers (this excludes floating zeroes, denormals or not finite)
//!          the option has no influence on the two parameters calls
//!
//!    If `n` is zero returns `x`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/next.cpp}
//================================================================================================
  inline constexpr auto next = functor<next_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T next_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    requires(!O::contains(pedantic) || !floating_value<T>)
    {
      if constexpr( floating_value<T>)
      {
        if constexpr(O::contains(raw))
        {
          auto s = ieee_constant<0x1.0000000000001p-53, 0x1.000002p-24f, 0x1.004p-11f>(as(a));
          return fma[pedantic](s, eve::abs(a), a);
        }
        if ((!std::same_as<element_type_t<T>,  eve::float16_t>) && (eve::all( eve::is_normal(a))))
        {
          return next[raw](a);
        }
        else
        {
          auto bi = bitinteger(a);
          if constexpr(scalar_value<T>)
          {
            using v_t = eve::as_integer_t<T, signed>;
            return bitfloating(  static_cast<v_t>(bi+ one(as(bi))));
          }
          else
            return bitfloating(  bi+ one(as(bi)));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated)||O::contains(pedantic))
        {
          return if_else(a == valmax(as(a)), a, T(a+one(as(a))));
        }
        else
        {
          return T(a+one(as(a)));
        }
      }
    }

    template<floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr T next_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    requires(O::contains(pedantic))
    {
      if ((!std::same_as<element_type_t<T>,  eve::float16_t>) && eve::all( eve::is_normal(a))) return next[raw](a);
      auto pz   = bitinteger(a);
      T z    = bitfloating(call_add(pz, one(as(pz))));
      auto testm0 = is_eqmz(a);
      if (eve::none(testm0)) return z;
      auto nxt = if_else(testm0, zero(as(a)), z);
      if (eve::none(is_not_finite(a))) return nxt;
      nxt = if_else(eve::is_minf(a), eve::valmin(eve::as(a)), nxt);
      if  constexpr(O::contains(saturated))
      {
        nxt = if_else(eve::is_pinf(a), a, nxt);
        if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, nxt);
        return nxt;
      }
      else
      {
        return nxt;
      }
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    next_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    requires(!O::contains(pedantic) || !floating_value<T>)
    {
      if constexpr( floating_value<T>)
      {
        auto bi = bitinteger(a);
        if constexpr(scalar_value<T>)
        {
          using v_t = eve::as_integer_t<T, signed>;
          return bitfloating(  static_cast<v_t>(bi+n));
        }
        else
          return bitfloating(bi+n);
      }
      else
      {
        if  constexpr(O::contains(saturated) || O::contains(pedantic))
        {
          auto tmp = next(a, n);
          return if_else(a > tmp, a, tmp);
        }
        else
        {
          return T(a+convert(n, as<element_type_t<T>>()));
        }
      }
    }

    template<floating_value T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    next_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    requires(O::contains(pedantic))
    {
      using i_t = as_integer_t<T>;
      i_t ban   = bitinteger(a) + convert(n, eve::as<element_type_t<i_t>>(n));
      auto nxt = bitfloating(ban);
      auto fbanm1 = bitfloating(call_sub(ban, one(as(ban))));
      nxt = if_else(is_negative(a) && is_positive(fbanm1), fbanm1, nxt);
      nxt = if_else(is_eqmz(fbanm1), zero, nxt);
      if constexpr( eve::platform::supports_nans ) nxt = if_else(is_nan(a), a, nxt);
      if constexpr(O::contains(saturated))         nxt = if_else(is_pinf(a), inf(as(a)), nxt);
      return nxt;
    }
  }
}
