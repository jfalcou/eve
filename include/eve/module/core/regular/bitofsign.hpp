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
#include <eve/forward.hpp>
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_and.hpp>

namespace eve
{

  template<typename Options>
  struct bitofsign_t : elementwise_callable<bitofsign_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL_PT(as<T>{}, v);
    }

    EVE_CALLABLE_OBJECT(bitofsign_t, bitofsign_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var bitofsign
//!   @brief `elementwise_callable` object computing the bit of sign.
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
//!      constexpr auto bitofsign(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bitofsign[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto bitofsign[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the bit of sign is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!    @note
//!      * `bitofsign` does NOT return a [logical value](@ref eve::value)
//!
//!      * In particular,  take care that for  [floating real values](@ref eve::value) bitofsign
//!        does NOT return a [logical value](@ref eve::value) that can be tested, but
//!        `mzero(as(x))` if `x` is
//!        negative and  `zero(as(x))` if `x` is positive, which both satisfy the eve::is_eqz
//!        predicate.
//!
//!      * If you want to test if the bit of sign is set `is_negative` is the right function to
//!        call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bitofsign.cpp}
//================================================================================================
  inline constexpr auto bitofsign = functor<bitofsign_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    constexpr T  bitofsign_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      return bit_and(a, signmask(eve::as(a)));
    }
  }
}
