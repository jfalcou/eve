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
  struct maxexponentm1_t : constant_callable<maxexponentm1_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using i_t = as_integer_t<T>;

      if      constexpr(std::same_as<T, eve::float16>) return i_t(14);
      else if constexpr(std::same_as<T, float>  ) return i_t(126);
      else if constexpr(std::same_as<T, double> ) return i_t(1022);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr as_integer_t<T> operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(maxexponentm1_t, maxexponentm1_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxexponentm1
//!   @brief Computes the  the greatest exponent of a floating point IEEE value minus one.
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
//!     template<eve::plafloating_valuein_value T> constexpr eve::as_integer_t<T> maxexponentm1m1(as<T> x);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//! the call `eve::maxexponentm1(as<T>())` is semantically equivalent to
//!   - as_integer_t<T>(126) if eve::element_type_t<T> is float
//!   - as_integer_t<T>(1022) if eve::element_type_t<T> is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxexponentm1.cpp}
//!
//================================================================================================
inline constexpr auto maxexponentm1 = functor<maxexponentm1_t>;
//================================================================================================
//! @}
//================================================================================================
}
