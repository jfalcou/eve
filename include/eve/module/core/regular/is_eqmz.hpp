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
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_eqpz.hpp>

namespace eve
{
  template<typename Options>
  struct is_eqmz_t : elementwise_callable<is_eqmz_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_eqmz_t, is_eqmz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_eqmz
//!   @brief `elementwise callable` returning a logical true  if and only if the element
//!    value is a floating zero with sign bit set.
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
//!      constexpr auto is_eqmz(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_eqmz[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_eqmz[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. returns [elementwise](@ref glossary_elementwise) true if and only
//!        if the element value is a floating zero with sign bit set (`mzero`).
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @note This function is not defined for integral typed entries to avoid misuse.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_eqmz.cpp}
//================================================================================================
  inline constexpr auto is_eqmz = functor<is_eqmz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_eqmz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return logical_andnot(is_eqz(a), is_eqpz(a));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_eqmz.hpp>
#endif
