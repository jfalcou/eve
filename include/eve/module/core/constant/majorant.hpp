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
  struct majorant_t : constant_callable<majorant_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> tgt, Opts const&)
    {
      if constexpr (eve::floating_value<T>) return eve::inf(tgt);
      else                                  return eve::valmax(tgt);
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(majorant_t, majorant_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var majorant
//!   @brief Computes a value `x` such that for any value `y` of the same type, `is_not_greater(y, x)` is true.
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
//!     template<eve::plain_value T> constexpr T majorant(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::majorant(as<T>())` is semantically equivalent to [valmax](@ref eve::valmax) for integral types
//!      and [inf](@ref eve::inf) for floating-point types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/majorant.cpp}
//!
//================================================================================================
  inline constexpr auto majorant = functor<majorant_t>;
//================================================================================================
//! @}
//================================================================================================
}
