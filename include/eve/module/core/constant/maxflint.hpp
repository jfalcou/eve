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
  struct maxflint_t : constant_callable<maxflint_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      if      constexpr(std::same_as<T, float>  ) return T(0x1p+24);
      else if constexpr(std::same_as<T, double> ) return T(0x1p+53);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(maxflint_t, maxflint_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxflint
//!   @brief Computes the the greatest floating point representing an integer and
//!   such that n != n+1.
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
//!     template<eve::floating_value T> constexpr T maxflint(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::maxflint(as<T>())` is semantically equivalent to:
//!        * `T(16777216.0f)` if `eve::element_type_t<T>` is float.
//!        * `T(9007199254740992.0)` if `eve::element_type_t<T>` is double.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxflint.cpp}
//! @}
//================================================================================================
  inline constexpr auto maxflint = functor<maxflint_t>;
}
