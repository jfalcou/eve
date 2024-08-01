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
  struct bit_shr_t : strict_elementwise_callable<bit_shr_t, Options>
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
//!   @brief `strict_elementwise_callable` object computing a logical right shift.
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
//!      // Regular overload
//!      constexpr auto bit_shr(integral_value auto x, integral_value auto n)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_shr[conditional_expr auto c](integral_value auto x, integral_value auto n) noexcept; // 2
//!      constexpr auto bit_shr[logical_value auto m](integral_value auto x, integral_value auto n)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: argument(@ref eve::integral_value). to be shifted.
//!     * `n`: [shift](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!       1. The value of the logical right shift is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note
//!     * The call `bit_shr(x, n)` is equivalent to `x >> n` if `x`  is
//!       an [unsigned_value](@ref eve::simd_value).
//!
//!     * The types must share the same cardinal or be scalar and if \f$N\f$
//!       is the size in bits  of the element type of `T`,
//!       all elements of n must belong to the
//!       interval: \f$[0, N[\f$ or the result is undefined.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_shr.cpp}
//================================================================================================
  inline constexpr auto bit_shr = functor<bit_shr_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_shr.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_shr.hpp>
#endif

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_shr.hpp>
#endif
