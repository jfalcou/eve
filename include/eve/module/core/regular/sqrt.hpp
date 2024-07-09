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
  struct sqrt_t : elementwise_callable<sqrt_t, Options, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sqrt_t, sqrt_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sqrt
//!   @brief Computes the square root of the parameter.
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
//!      template< eve::floating_value T >
//!      T sqrt(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::floating_value) argument.
//!
//!   **Return value**
//!
//!     * value containing the [elementwise](@ref glossary_elementwise)
//!       square root of `x` or Nan if `x` is less than zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/sqrt.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sqrt[mask](x)` provides a masked version of `eve::sqrt` which is
//!     equivalent to `if_else (mask, sqrt(x), x)`.
//!
//!   * eve::raw
//!
//!     The call `sqrt[raw](x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return. Otherwise it uses the non-decorated call.
//!
//! @}
//================================================================================================
  inline constexpr auto sqrt = functor<sqrt_t>;
}

#include <eve/module/core/regular/impl/sqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/sqrt.hpp>
#endif
