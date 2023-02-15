//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var shl
//!   @brief Computes the arithmetic left shift operation.
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
//!      template< eve::ordered_value T , integral_value N >
//!      T shl(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::ordered_value) to be shifted.
//!     * `n`:   [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) arithmetic left shift of the first
//!      parameter by the second one is returned.
//!
//!      The call `shl(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref
//!      eve::simd_value).
//!
//!      The types must share the same cardinal or be scalar and if `N` is the size in bits  of
//!      the element type of `T`, all  [elements](@ref glossary_elementwise) of n must belong to the
//!      interval: `[0, N[` or the result is undefined.
//!
//!    @note
//!     Although the infix notation with `<<` is supported, the `<<` operator on
//!     standard scalar types is the original one and so can not be overloaded on standard floating
//!     parameters due to **C++** limitations.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/shl.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::shl[mask](x, ...)` provides a masked
//!     version of `shl` which is
//!     equivalent to `if_else(mask, shl(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/shl.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct shl_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shl_), T const&,
                             [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::shl] Shifting by " << s << " is out of the range [0, "
                                         << sizeof(element_type_t<T>) * 8 << "[.");
  }
  template<conditional_expr C, typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shl_), C const& , T const&,
                             [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::shl] Shifting by " << s << " is out of the range [0, "
                                         << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(shl_, shl);
}

#include <eve/module/core/regular/impl/shl.hpp>
