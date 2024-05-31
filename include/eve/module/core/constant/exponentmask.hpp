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
  struct exponentmask_t : constant_callable<exponentmask_t, Options, downward_option, upward_option>
  {
    template<floating_value T>
    static EVE_FORCEINLINE constexpr as_integer_t<T> value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::same_as<e_t, float>  ) return i_t(0x7f800000);
      else if constexpr(std::same_as<e_t, double> ) return i_t(0x7ff0000000000000LL);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
    EVE_FORCEINLINE constexpr auto operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

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
//!      template< eve::floating_value T >
//!      as_unsigned<T> exponentmask(as<T> t) noexcept;
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
//! @}
//================================================================================================
  inline constexpr auto exponentmask = functor<exponentmask_t>;
}
