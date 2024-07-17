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
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_positive_t : elementwise_callable<is_positive_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_positive_t, is_positive_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_positive
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is signed and
//!   has its sign bit not set
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
//!      constexpr auto is_positive(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto is_positive[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_positive[logical_value auto m](value auto x)    noexcept; // 2
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
//!      1. this function coincides with `is_gtz` on [integral values](@ref eve::value),
//!         but The call `is_positive(x)` [elementwise](@ref glossary_elementwise) returns true
//!         if and only if the bit of sign (most significant bit) is not set.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note   this function coincides with `is_gez` on [integral real values](@ref eve::value),
//!     but for [floating values](@ref eve::floating_value) `T`, `is_positive(mzero<`T`>)` is false
//!     and if `x` is a `Nan` the result depends of the bit of sign of `x` which can be out of control
//!     although not undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_positive.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_positive = functor<is_positive_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_positive_(EVE_REQUIRES(cpu_), O const &, T const& v) noexcept
    {
      if constexpr( unsigned_value<T> ) return true_(eve::as(v));
      else
      {
        if constexpr( signed_integral_value<T> ) return is_gez(v);
        else if constexpr( simd_value<T> )
        {
          using elt_t = element_type_t<T>;
          using swi_t = as_wide_t<eve::as_integer_t<elt_t, signed>, cardinal_t<T>>;
          using lwi_t = as_logical_t<as_wide_t<elt_t, cardinal_t<T>>>;
          return bit_cast(is_gez(bit_cast(v, as<swi_t>())), as<lwi_t>());
        }
        else
        {
          using si_t = eve::as_integer_t<T, signed>;
          return bit_cast(is_gez(bit_cast(v, as<si_t> {})), as<as_logical_t<T>> {});
        }
      }
    }
  }
}
