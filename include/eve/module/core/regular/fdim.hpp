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
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve
{
  template<typename Options>
  struct fdim_t : elementwise_callable<fdim_t, Options>
  {
    template<eve::value T,  value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(fdim_t, fdim_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fdim
//!   @brief Computes the positive difference between the two parameters.
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
//!      template< eve::ordered_value T, eve::ordered_value U >
//!      T fdim(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [real](@ref eve::ordered_value)  arguments.
//!
//!   **Return value**
//!
//!     Returns the  [elementwise](@ref glossary_elementwise) positive difference
//!     between `x` and `y`:
//!       * if `x>y`,   `x-y` is returned,
//!       * if `x<=y`,  `+0` is returned,
//!       * otherwise a `Nan` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fdim.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fdim[mask](x)` provides a masked version of `eve::fdim` which is
//!     equivalent to `if_else (mask, fdim(x), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto fdim = functor<fdim_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    fdim_(EVE_REQUIRES(cpu_), O const &, T a, T b) noexcept
    {
      return if_else(a >= b, sub(a, b), eve::zero);
    }
  }
}
