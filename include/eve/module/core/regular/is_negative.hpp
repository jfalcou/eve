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
#include <eve/module/core/is_ltz.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_negative_t : elementwise_callable<is_negative_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_negative_t, is_negative_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_negative
//!   @brief Returns a logical true  if and only if the element  value is signed and
//!   has its sign bit set
//!
//!   **Defined in Header**
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
//!      template< eve::value T >
//!      eve::as_logical<T> is_negative(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!      For signed types The call `is_negative(x)`
//!      [elementwise](@ref glossary_elementwise) returns true
//!      if and only if the bit of sign (most significant bit) is set.
//!
//!   @note
//!     this function coincides with `is_ltz` on [integral real values](@ref eve::value),
//!     but for [floating values](@ref eve::floating_value) `T`, `is_negative(mzero<`T`>)` is true
//!     and if `n` is a Nan the result depends of the bit of sign of `n` which can be out of control
//!     although not undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_negative.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_negative[mask](x)` provides a masked version of `eve::is_negative` which
//!     is equivalent to `if_else (mask, is_negative(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
 inline constexpr auto is_negative = functor<is_negative_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_negative_(EVE_REQUIRES(cpu_), O const &, T const& v) noexcept
    {
      if constexpr( unsigned_value<T> )
        return false_(eve::as(v));
      else
      {
        if constexpr( signed_integral_value<T> )
          return is_ltz(v);
        else if constexpr( simd_value<T> )
        {
          using elt_t = element_type_t<T>;
          using swi_t = as_wide_t<eve::as_integer_t<elt_t, signed>, cardinal_t<T>>;
          using lwi_t = as_logical_t<as_wide_t<elt_t, cardinal_t<T>>>;
          return bit_cast(is_ltz(bit_cast(v, as<swi_t>())), as<lwi_t>());
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
