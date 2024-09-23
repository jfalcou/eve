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
#include <eve/module/core/constant/allbits.hpp>

namespace eve
{
  template<typename Options>
  struct nan_t : constant_callable<nan_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      return allbits(eve::as<T>());
   }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(nan_t, nan_);
  };


//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var nan
//!   @brief Computes the IEEE quiet NaN constant
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
//!      template<eve::floating_value T> constexpr T nan(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!    The call `eve::nan(as<T>())`  is semantically equivalent to  `T(0.0/0.0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/nan.cpp}
//! @}
//================================================================================================
  inline constexpr auto nan = functor<nan_t>;
}
