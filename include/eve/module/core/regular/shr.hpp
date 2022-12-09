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
//!   @var shr
//!   @brief Computes the arithmetic right shift operation.
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
//!      T shr(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value) to be shifted.
//!
//!     * `n`:   [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) arithmetic right shift of the first
//!         parameter by the second one is returned.
//!
//!      The call `shr(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref
//!          eve::simd_value).
//!
//!      The types must share the same cardinal or be scalar and if `N` is the size in bits  of
//!      the element type of `T`, all  [elements](@ref glossary_elementwise) of n must belong to the
//!      interval: `[0, N[` or the result is undefined.
//!
//!    @note
//!      Although the infix notation with `<<` is supported, the `<<` operator on
//!      standard scalar types is the original one and so can not be overloaded on standard floating
//!      parameters due to **C++** limitations.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/shr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::shr[mask](x, ...)` provides a masked
//!     version of `shr` which is
//!     equivalent to `if_else(mask, shr(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/shr.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct shr_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shr_), T const&,
                             [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::shr] Shifting by " << s << " is out of the range [0, "
                                         << sizeof(element_type_t<T>) * 8 << "[.");
  }
  template<conditional_expr C, typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shr_), C const& , T const&,
                             [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::shr] Shifting by " << s << " is out of the range [0, "
                                         << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(shr_, shr);
}

#include <eve/module/core/regular/impl/shr.hpp>
