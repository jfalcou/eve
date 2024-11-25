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
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_ltz_t : elementwise_callable<is_ltz_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_ltz_t, is_ltz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_ltz
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is less than 0.
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
//!      constexpr auto is_ltz(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_ltz[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_ltz[logical_value auto m](value auto x) noexcept;    // 2
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
//!     1. Returns [elementwise](@ref glossary_elementwise) `x < 0`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!     @godbolt{doc/core/is_ltz.cpp}
//================================================================================================
  inline constexpr auto is_ltz = functor<is_ltz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_ltz_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return false_(eve::as{a});
      else
        return a <  zero(eve::as{a});
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#include <eve/module/core/regular/impl/simd/x86/is_ltz.hpp>
#endif
