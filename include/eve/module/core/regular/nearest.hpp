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
  struct nearest_t : elementwise_callable<nearest_t, Options>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {  return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const  noexcept
    { return EVE_DISPATCH_CALL(v, target); }

    EVE_CALLABLE_OBJECT(nearest_t, nearest_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var nearest
//!   @brief Computes the nearest integer to the input.
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
//!      T nearest(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!      Computes  [elementwise](@ref glossary_elementwise) the integer nearest to `x`.
//!
//!      If `x` is an exact half-integer the rounding is made to the nearest even integer.
//!
//!      The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!      `FE_TOWARDZERO`. This function object implements the `FE_TONEAREST` version.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/nearest.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::nearest[mask](x)` provides a masked version of `eve::nearest` which is
//!     equivalent to `if_else (mask, nearest(x), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto nearest = functor<nearest_t>;
}


#include <eve/module/core/impl/nearest.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/impl/simd/x86/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/impl/simd/ppc/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/impl/simd/arm/neon/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/impl/simd/arm/sve/nearest.hpp>
#endif
