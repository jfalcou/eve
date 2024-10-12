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
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct popcount_t : elementwise_callable<popcount_t, Options>
  {
    template<unsigned_value T>
    EVE_FORCEINLINE constexpr T operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(popcount_t, popcount_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var popcount
//!   @brief `elementwise_callable` object computing elementwise the number of bits set in the parameter.
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
//!      constexpr auto popcount(unsigned_value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [unsigned argument](@ref eve::unsigned_value).
//!
//!    **Return value**
//!
//!    The value of  number of bits set in the value `x` is returned.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/popcount.cpp}
//================================================================================================
  inline constexpr auto popcount = functor<popcount_t>;
//================================================================================================
//! @}
//================================================================================================

}

#include <eve/module/core/regular/impl/popcount.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/popcount.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/popcount.hpp>
#endif
