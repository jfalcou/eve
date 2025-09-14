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
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/valmin.hpp>

namespace eve
{
  template<typename Options>
  struct minorant_t : constant_callable<minorant_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> tgt, Opts const&)
    {
      if constexpr (eve::floating_value<T>) return eve::minf(tgt);
      else                                  return eve::valmin(tgt);
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(minorant_t, minorant_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var minorant
//!   @brief Computes a value `x` such that for any value `y` of the same type, `is_not_less(y, x)` is true.
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
//!     template<eve::plain_value T> constexpr T minorant(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minorant(as<T>())` is semantically equivalent to [valmin](@ref eve::valmin) for integral types
//!      and [minf](@ref eve::minf) for floating-point types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/minorant.cpp}
//!
//================================================================================================
  inline constexpr auto minorant = functor<minorant_t>;
//================================================================================================
//! @}
//================================================================================================
}
