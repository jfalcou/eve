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
  struct maxexponent_t : constant_callable<maxexponent_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using i_t = as_integer_t<T>;

      if      constexpr(std::same_as<T, eve::float16>) return i_t(15);
      else if constexpr(std::same_as<T, float>  ) return i_t(127);
      else if constexpr(std::same_as<T, double> ) return i_t(1023);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr as_integer_t<T> operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(maxexponent_t, maxexponent_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxexponent
//!   @brief Computes the greatest exponent of a floating point IEEE value
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
//!     template<eve::floating_value T> constexpr eve::as_integer<T> maxexponent(as<T> x);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//! the call `eve::maxexponent(as<T>())` is semantically equivalent to
//!   - as_integer_t<T>(127) if eve::element_type_t<T> is float
//!   - as_integer_t<T>(1023) if eve::element_type_t<T> is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxexponent.cpp}
//!
//================================================================================================
 inline constexpr auto maxexponent = functor<maxexponent_t>;
//================================================================================================
//! @}
//================================================================================================
}
