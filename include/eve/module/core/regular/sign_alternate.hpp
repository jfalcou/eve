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
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct sign_alternate_t : elementwise_callable<sign_alternate_t, Options>
  {
    template<signed_value T>
    constexpr EVE_FORCEINLINE T operator()(T n) const noexcept
    {
      EVE_ASSERT(all(is_flint(n)), "sign_alternate : some entries are not flint");
      return EVE_DISPATCH_CALL_PT(T, n);
    }

    EVE_CALLABLE_OBJECT(sign_alternate_t, sign_alternate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sign_alternate
//!   @brief Computes \f$(-1)^n\f$.
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
//!      constexpr auto sign_alternate(signed_value auto n)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sign_alternate[conditional_expr auto c](signed_value auto n) noexcept; // 2
//!      constexpr auto sign_alternate[logical_value auto m](signed_value auto n)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [argument](@ref eve::value). Must be signed integral or flint.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1.  [elementwise](@ref glossary_elementwise) \f$(-1)^n\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sign_alternate.cpp}
//================================================================================================
  inline constexpr auto sign_alternate = functor<sign_alternate_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sign_alternate_(EVE_REQUIRES(cpu_), O const &, T const& n) noexcept
    {
      return if_else(is_odd(n), mone, one(as(n)));
    }
  }
}
