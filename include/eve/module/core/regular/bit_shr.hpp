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
#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct bit_shr_t : elementwise_callable<bit_shr_t, Options>
  {
    template<eve::value T, integral_value I >
    constexpr EVE_FORCEINLINE  as_wide_as_t<T, I> operator()(T v, I i) const
    {
      EVE_ASSERT(detail::assert_good_shift<T>(i),
                 "[eve::bit_shr] Shifting by " << i << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(v, i);
    }

    template<eve::integral_value T, auto I >
    //    requires(unsigned_scalar_value<element_type_t<T>>)
    constexpr EVE_FORCEINLINE T operator()(T v, index_t<I> i) const
    {
      EVE_ASSERT(detail::assert_good_shift<T>(i),
                 "[eve::bit_shr] Shifting by " << i << " is out of the range [0, "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(v, i);
    }

    EVE_CALLABLE_OBJECT(bit_shr_t, bit_shr_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_shr
//!   @brief Computes a logical right shift.
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
//!      template< eve::value T , integral_value N >
//!      T bit_shr(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  argument(@ref eve::value). to be shifted.
//!
//!     * `n`:    [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!    The value of the logical right shift
//!    is returned.
//!
//!   @note
//!     * The call `bit_shr(x, n)` is equivalent to `x >> n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!     * The types must share the same cardinal or be scalar and if \f$N\f$
//!       is the size in bits  of the element type of `T`,
//!       all elements of n must belong to the
//!       interval: \f$[0, N[\f$ or the result is undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_shr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_shr[mask](x, ...)` provides a masked
//!     version of `bit_shr` which is
//!     equivalent to `if_else(mask, bit_shr(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_shr.cpp}
//! @}
//================================================================================================
  inline constexpr auto bit_shr = functor<bit_shr_t>;
}

#include <eve/module/core/regular/impl/bit_shr.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_shr.hpp>
#endif
