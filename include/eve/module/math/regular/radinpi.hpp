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
#include <eve/module/core.hpp>

namespace eve
{

  template<typename Options>
  struct radinpi_t : elementwise_callable<radinpi_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(radinpi_t, radinpi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var radinpi
//!
//! @brief `elementwise_callable` object multiplying the input by \f$1/\pi\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto radinpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto radinpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto radinpi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref floating_value).
//!    * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the radian input converted in \f$\pi\f$ multiples.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/radinpi.cpp}
//!  @}
//================================================================================================
  inline constexpr auto radinpi = functor<radinpi_t>;

  namespace detail
  {
    template<floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    radinpi_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
        return inv_pi(eve::as(a)) * a;
      else
        return apply_over(radinpi, a);
    }
  }
}
