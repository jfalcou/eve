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
  struct is_pinf_t : elementwise_callable<is_pinf_t, Options>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as<as_logical_t<T>>{}), t);
    }

    EVE_CALLABLE_OBJECT(is_pinf_t, is_pinf_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_pinf
//!   @brief `elementwise callable` returning a logical true  if and only if the element is a positive infinite value
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
//!      constexpr auto is_pinf(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_pinf[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_pinf[logical_value auto m](value auto x) noexcept;    // 2
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
//!     1. For floating entries returns true if x is equals to `eve::inf(as(x))`,
//!       and is always false for integral types.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_pinf.cpp}
//================================================================================================
  inline constexpr auto is_pinf = functor<is_pinf_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_pinf_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as(a));
      else
        return (a == inf(eve::as(a)));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_pinf.hpp>
#endif
