//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/forward.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>

namespace eve
{

template <typename Options>
struct iota_t : callable<iota_t, Options, conditional_option>
{
  template <eve::arithmetic_simd_value T>
  EVE_FORCEINLINE T operator()(as<T> tgt) const { return EVE_DISPATCH_CALL(tgt); }
  EVE_CALLABLE_OBJECT(iota_t, iota_);
};


//================================================================================================
//! @addtogroup core_constants
//! @{
//!    @var iota
//!    @brief all numbers from 0 to size() - 1. equivalent to `T{ [](int i, int) {return i; } }`
//!
//!    @see eve::views::iota if you want a view.
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
//!      template <eve::conditional_expr C,
//!                eve::arithmetic_simd_value T>
//!      T iota[C cond](as<T> tgt);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `tgt` :  [Type wrapper](@ref eve::as) - type of the resulting
//!   * `cond` : (optional) - a way to replace undesired elements If no `alternative`
//!              is provided - returns eve::zero(tgt) for disabled elements.
//!
//!  **Return value**
//!
//!    * T{0, 1, ...}
//!
//!  @groupheader{Example}
//!
//!  @godbolt{test/doc/core/constant/iota.cpp}
//! @}
inline constexpr auto iota = functor<iota_t>;
}

#include <eve/module/core/constant/simd/common/iota.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/constant/simd/arm/sve/iota.hpp>
#endif
