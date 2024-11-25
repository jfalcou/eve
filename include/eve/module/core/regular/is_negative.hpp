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
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_not_nan.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_negative_t : elementwise_callable<is_negative_t, Options, pedantic_option>
  {
    template<value T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(is_negative_t, is_negative_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_negative
//!   @brief `elementwise callable` returning a logical true if and only if the element
//!    value is signed and has its sign bit set
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
//!      constexpr auto is_negative(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_negative[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_negative[logical_value auto m](value auto x) noexcept;    // 2
//!
//!      // Semantic options
//!      constexpr auto is_negative[pedantic](value auto x)noexcept;                 // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. For signed types The call `is_negative(x)` returns true
//!        if and only if the bit of sign (most significant bit) is set. Of course the result on a NaN input
//!        is generally out of control.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. with this option a NaN input always return false.
//!
//!   @note
//!     this function coincides with `is_ltz` on [integral real values](@ref eve::value),
//!     but for [floating values](@ref eve::floating_value) `T`, `is_negative(mzero<`T`>)` is true
//!     and if `n` is a Nan the result depends of the bit of sign of `n` which can be out of control
//!     although not undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_negative.cpp}
//================================================================================================
  inline constexpr auto is_negative = functor<is_negative_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> is_negative_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr (unsigned_value<T>)
        return false_(as{v});
      else if constexpr (O::contains(pedantic))
      {
        return is_negative(v) && is_not_nan(v);
      }
      else
      {
        if constexpr (signed_integral_value<T>)
          return is_ltz(v);
        else if constexpr (simd_value<T>)
        {
          using elt_t = element_type_t<T>;
          using swi_t = as_wide_t<eve::as_integer_t<elt_t, signed>, cardinal_t<T>>;
          using lwi_t = as_logical_t<as_wide_t<elt_t, cardinal_t<T>>>;
          return bit_cast(is_ltz(bit_cast(v, as<swi_t>{})), as<lwi_t>{});
        }
        else
        {
          using si_t = eve::as_integer_t<T, signed>;
          return bit_cast(is_ltz(bit_cast(v, as<si_t> {})), as<as_logical_t<T>> {});
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_negative.hpp>
#endif
