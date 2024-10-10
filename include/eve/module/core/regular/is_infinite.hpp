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
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_infinite_t : elementwise_callable<is_infinite_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_infinite_t, is_infinite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_infinite
//!   @brief `elementwise callable` returning a logical true  if and only if the element is an infinite value
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
//!      constexpr auto is_infinite(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_infinite[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_infinite[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. For floating entries returns true if x is equals to `eve::inf(as{x})` or `eve::minf(as{x})`,
//!       and is always false for integral types.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_infinite.cpp}
//================================================================================================
  inline constexpr auto is_infinite = functor<is_infinite_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_infinite_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as{a});
      else
        return (eve::abs(a) == inf(eve::as{a}));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_infinite.hpp>
#endif
