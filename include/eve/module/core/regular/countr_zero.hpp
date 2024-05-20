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

namespace eve
{
  template<typename Options>
  struct countr_zero_t : elementwise_callable<countr_zero_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countr_zero_t, countr_zero_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countr_zero
//!   @brief Computes the number of consecutive 0 in a value starting from right
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
//!      T countr_zero(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
//!      from the least significant bit ("right"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/countr_zero.cpp}
//! @}
//================================================================================================
  inline constexpr auto countr_zero = functor<countr_zero_t>;
}

#include <eve/module/core/regular/impl/countr_zero.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/countr_zero.hpp>
#endif
