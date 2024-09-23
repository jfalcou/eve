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
  struct nbmantissabits_t : constant_callable<nbmantissabits_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr as_integer_t<T> value(eve::as<T> const&, auto const&)
    {
      using i_t = as_integer_t<T>;

      if      constexpr(std::same_as<T, float>  ) return  i_t(23);
      else if constexpr(std::same_as<T, double> ) return  i_t(52);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr as_integer_t<T> operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(nbmantissabits_t, nbmantissabits_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var nbmantissabits
//!   @brief Returns the number of mantissa bits of a floating point value.
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
//!     template<eve::floating_value T> constexpr T nbmantissabits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::nbmantissabits(as<T>())` is semantically equivalent to:
//!         * `as_integer_t<T>(23)` if `eve::element_type_t<T>` is float
//!         * `as_integer_t<T>(52)` if `eve::element_type_t<T>` is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/nbmantissabits.cpp}
//! @}
//================================================================================================
 inline constexpr auto nbmantissabits = functor<nbmantissabits_t>;
}
