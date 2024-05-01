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
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bitofsign.hpp>

namespace eve
{
  template<typename Options>
  struct copysign_t : elementwise_callable<copysign_t, Options>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(copysign_t, copysign_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var copysign
//!   @brief Computes the [elementwise](@ref glossary_elementwise) composition of a value
//!   with the magnitude of the first parameter  and the bit of sign of the second one.
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
//!      template< eve::ordered_value T, eve::ordered_value T >
//!      T copysign(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [real](@ref eve::ordered_value) arguments.
//!
//!    **Return value**
//!
//!      The value of the [elementwise](@ref glossary_elementwise) composition of a
//!      value with the magnitude of `x` and the bit of sign of `y`
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/copysign.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::copysign[mask](x, ...)` provides a masked
//!     version of `copysign` which is
//!     equivalent to `if_else(mask, copysign(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto copysign = functor<copysign_t>;

  namespace detail
  {
    template<floating_value T, floating_value U, callable_options O>
    EVE_FORCEINLINE constexpr auto copysign_(EVE_REQUIRES(cpu_), O const &, T aa, U bb) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t a = r_t(aa);
      r_t b = r_t(bb);
      return bit_or(bitofsign(b), bit_notand(signmask(eve::as(a)), a));
    }
  }
}
