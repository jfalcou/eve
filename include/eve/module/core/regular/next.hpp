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
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_negative.hpp>
#include <eve/module/core/regular/is_positive.hpp>
#include <eve/module/core/regular/is_normal.hpp>

namespace eve
{
  template<typename Options>
  struct next_t : strict_elementwise_callable<next_t, Options, pedantic_option,  saturated_option, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL_PT(T, v); }

    template<eve::value T, integral_value N>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(T v, N n) const noexcept
      requires (eve::same_lanes_or_scalar<T, N>)
    {
      EVE_ASSERT(eve::all(n >= 0), "[eve::next] : second parameter must be positive");
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<T, N>), v, n);
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
//!      constexpr auto next[pedantic](/* any of the above overloads */)                noexcept; // 5.1
//!      constexpr auto next[saturated ](/* any of the above overloads */)              noexcept; // 5.2
//!      constexpr auto next[raw](value auto x)                                         noexcept; // 6
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
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(raw))
        {
          auto s = ieee_constant<0x1.000002p-24f, 0x1.0000000000001p-53>(as(a));
          return fma(s, eve::abs(a), a);
        }
        if (eve::all( eve::is_normal(a))) return next[raw](a);
        if constexpr(O::contains(pedantic))
        {
          auto pz   = bitinteger(a);
          auto z    = bitfloating(pz+one(as(pz)));
          auto test = is_negative(a) && is_positive(z);
          auto nxt = if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
          if  constexpr(O::contains(saturated))
          {
            nxt = if_else(a == inf(as(a)), a, nxt);
            if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          }
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), nxt);
        }
        else if  constexpr(O::contains(saturated))
        {
          auto z = if_else(a == inf(as(a)), a, next(a));
          if constexpr( eve::platform::supports_nans ) return if_else(is_nan(a), eve::allbits, z);
          else return z;
        }
        else
        {
          auto bi = bitinteger(a);
          return bitfloating(bi+one(as(bi)));
        }
      }
      else
      {
        if  constexpr(O::contains(saturated) || O::contains(pedantic))
        {
          return if_else(a == valmax(as(a)), a, T(a+one(as(a))));
        }
        else
        {
          return T(a+one(as(a)));
        }
      }
    }

    template<typename T, typename N, callable_options O>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N>
    next_(EVE_REQUIRES(cpu_), O const &, T const &a,  N const &n) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(pedantic))
        {
          using i_t = as_integer_t<T>;
          i_t vz   = bitinteger(a) + convert(n, as<element_type_t<i_t>>(n));
          auto pz   = vz - one(as(vz));
          auto z    = bitfloating(pz+one(as(pz)));
          auto test = is_negative(a) && is_positive(z);
          if constexpr( scalar_value<T> && scalar_value<N> )
          {
            if( is_nan(a) ) return a;
            return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
          }
          else { return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z); }
        }
        else if  constexpr(O::contains(saturated))
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
  }
}
