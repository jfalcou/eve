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
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/constant/valmax.hpp>

namespace eve
{
  template<typename Options>
  struct maxrepint_t : constant_callable<maxrepint_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T> tgt, Opts const&)
    {
      if constexpr (eve::integral_value<T>) return valmax(tgt);
      else                                  return maxflint(tgt);
    }

    template<arithmetic_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(maxrepint_t, maxrepint_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxrepint
//!   @brief Computes the maximum representable integer value. Same as `maxflint` for floating types and
//!          `valmax` for integral types.
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
//!     template<eve::floating_value T> constexpr T maxrepint(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::maxrepint(as<T>{})` is semantically equivalent to:
//!        * `eve::maxflint(as<T>{})` if `eve::element_type_t<T>` is a floating point type.
//!        * `eve::valmax(as<T>{})` if `eve::element_type_t<T>` is an integral type.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxrepint.cpp}
//!
//================================================================================================
  inline constexpr auto maxrepint = functor<maxrepint_t>;
//================================================================================================
//! @}
//================================================================================================
}
