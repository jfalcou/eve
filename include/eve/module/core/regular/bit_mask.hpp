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
#include <eve/module/core/regular/is_nez.hpp>

namespace eve
{
  template<typename Options>
  struct bit_mask_t : elementwise_callable<bit_mask_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE auto operator()(T v) const
    {
      return EVE_DISPATCH_CALL_PT((as<T>{}), v);
    }

    EVE_CALLABLE_OBJECT(bit_mask_t, bit_mask_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_mask
//!   @brief `elementwise_callable` object computing a bit mask full of zeroes or ones
//!
//!   @groupheader{Callable Signatures}
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
//!      constexpr auto bit_mask(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_mask[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto bit_mask[logical_value auto m](value auto x)    noexcept; // 2
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
//!      1. For each [elementwise](@ref glossary_elementwise) of `x`:
//!        *  if the [element](@ref glossary_elementwise) is zero, an element
//!           with all bits unset is returned.
//!        *  else an element of the type with all bits set is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_mask.cpp}
//================================================================================================
  inline constexpr auto bit_mask = functor<bit_mask_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    bit_mask_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      return is_nez(v).mask();
    }
  }
}
