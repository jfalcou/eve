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
struct rec_t : elementwise_callable<rec_t, Options, raw_option, pedantic_option>
{
  template<eve::value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(rec_t, rec_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rec
//!   @brief Computes the inverse of the parameter.
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
//!      T rec(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    inverse value of `x`.
//!
//!  @warning
//!     regular rec does not take care of denormals.
//!     If you need them use the pedantic option or the division operator
//!
//!
//!  @note
//!     For [real integral value](@ref eve::value) `x` is semantically equivalent to:
//!       * If x==1 or x==-1, x is returned.
//!       * If x==0,  [the greatest representable positive value](@ref eve::valmax) is returned.
//!       * Otherwise 0 is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rec.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::rec[mask](x)` provides a masked version of `eve::rec` which is
//!     equivalent to `if_else (mask, rec(x), x)`.
//!
//!   * eve::raw
//!
//!     The call `raw(rec)(x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return (circa 12 bits). Otherwise it uses the non decorated call.
//!
//!   * eve::pedantic
//!
//!     The call `rec[pedantic](x)` is equivalent to one(as(x)/x.
//! @}
//================================================================================================
  inline constexpr auto rec = functor<rec_t>;
}


#include <eve/module/core/regular/impl/rec.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rec.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rec.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rec.hpp>
#endif
