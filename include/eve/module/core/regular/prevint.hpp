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
#include <eve/module/core/regular/if_else.hpp>

namespace eve
{
  template<typename Options>
  struct prevint_t : strict_elementwise_callable<prevint_t, Options, raw_option, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(prevint_t, prevint_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var prevint
//!   @brief Computes the previous representable integer if it exists.
//!
//!   This function is equivalent to [dec](@ref eve::dec) for integral types. For floating point types, it will skip
//!   over the non-representable values between the input and the previous representable integer.
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
//!      constexpr auto prevint(value auto x)                                              noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto prevint[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto prevint[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto prevint[raw](value auto x)                                         noexcept; // 3
//!      constexpr auto prevint[saturated](value auto x)                                   noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. The greatest representable integer value less than `x` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional)
//!       3. same as 1. but inf returns nan.
//!       4. ensures that the input is never less than the result of the call.
//!          (It can be equal for minimal representable value)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/prevint.cpp}
//================================================================================================
  inline constexpr auto prevint = functor<prevint_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {
    template<callable_options O, typename... Ts>
    EVE_FORCEINLINE constexpr auto prevint_(EVE_REQUIRES(emulated_), O const& o, Ts... ts) noexcept
      requires (_::fp16_should_apply<common_value_t<Ts...>>)
    {
      return prevint_(EVE_TARGETS(cpu_), o, ts...);
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T prevint_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    {
      if constexpr (eve::floating_value<T>)
      {
        auto ni = floor(prev[opts.drop(raw)](v));
        if (!O::contains(raw)) ni = if_else(is_nan(v), nan(as(v)), ni);
        return ni;
      }
      else
        return prev[opts](v);
    }
  }
}
