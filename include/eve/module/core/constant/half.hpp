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
  struct half_t : constant_callable<half_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      if      constexpr(std::same_as<T, float> ) return T(0x1p-1);
      else if constexpr(std::same_as<T, double>) return T(0x1p-1f);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(half_t, half_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var half
//!   @brief Computes the constant \f$1/2\f$.
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
//!     template<eve::floating_value T> constexpr T half(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!    The call `eve::half(as<T>())` is semantically equivalent to T(0.5).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/half.cpp}
//!
//================================================================================================
  inline constexpr auto half = functor<half_t>;
//================================================================================================
//! @}
//================================================================================================
}
