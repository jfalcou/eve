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
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_even_t : elementwise_callable<is_even_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_even_t, is_even_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_even
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is even.
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
//!      // Regular overload
//!      constexpr auto is_even(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_even[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_even[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. returns [elementwise](@ref glossary_elementwise) true if and only
//!        if the element value is even.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_even.cpp}
//================================================================================================
  inline constexpr auto is_even = functor<is_even_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_even_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        auto aisflt = is_flint(a * half(eve::as(a)));
        auto aa     = eve::abs(a);
        if constexpr( eve::platform::supports_denormals )
          return aisflt && (aa != mindenormal(eve::as<T>()));
        else
          return aisflt && (aa != smallestposval(eve::as<T>()));
      }
      else if constexpr( scalar_value<T> )
        return (!(a & one(eve::as(a))));
      else
        return is_eqz((a & one(eve::as(a))));
    }
  }
}
