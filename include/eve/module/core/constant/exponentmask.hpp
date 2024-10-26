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
  struct exponentmask_t : constant_callable<exponentmask_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto value(eve::as<T> const&, auto const&)
    {
      using i_t = as_integer_t<T>;
      if      constexpr(std::same_as<T, float>  ) return i_t(0x7f800000);
      else if constexpr(std::same_as<T, double> ) return i_t(0x7ff0000000000000LL);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr as_integer_t<T> operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(exponentmask_t, exponentmask_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var exponentmask
//!   @brief Computes the the exponent bit mask of IEEE float or double.
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
//!     template<eve::floating_value T> constexpr eve::as_integer_t<T> exponentmask(as<T> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     `t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!       the call `eve::exponentmask(as<T>())` returns [elementwise](@ref glossary_elementwise),
//!       the integral mask to extract the exponent bits of an ieee floating value. The element
//!       values are:
//!        - 0x7f800000 if the [element type](@ref eve::element_type) is float
//!        - 0x7ff0000000000000LL if the [element type](@ref eve::element_type) is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/exponentmask.cpp}
//!
//================================================================================================
  inline constexpr auto exponentmask = functor<exponentmask_t>;
//================================================================================================
//! @}
//================================================================================================
}
