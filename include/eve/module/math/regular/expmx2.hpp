//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/expx2.hpp>

namespace eve
{
  template<typename Options>
  struct expmx2_t : elementwise_callable<expmx2_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(expmx2_t, expmx2_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var expmx2
//! @brief `elementwise_callable` object computing \f$e^{-x^2}\f$.
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
//!      constexpr auto expmx2(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto expmx2[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto expmx2[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!  **Parameters**
//!
//!    * `x`: [floating value](@ref eve::value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!  **Return value**
//!
//!     1. Returns the [elementwise](@ref glossary_elementwise) exponential of minus the square of `x`: \f$e^{-x^2}\f$.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/expmx2.cpp}
//================================================================================================
  inline constexpr auto expmx2 = functor<expmx2_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    expmx2_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      if constexpr( has_native_abi_v<T> )
        return rec[pedantic](eve::expx2(a0));
      else
        return apply_over(expmx2, a0);
    }
  }
}
