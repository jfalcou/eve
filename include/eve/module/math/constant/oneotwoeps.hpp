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
  struct oneotwoeps_t : constant_callable<oneotwoeps_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

      if constexpr(std::same_as<e_t, float>  ) return T(0x1p22);
      else if constexpr(std::same_as<e_t, double> ) return T(0x1p51);
    }

    template<typename T>
    requires(floating_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(oneotwoeps_t, oneotwoeps_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var oneotwoeps
//!   @brief Computes a constant to the machine oneotwoepsilon.
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
//!     template<eve::value T> constexpr T oneotwoeps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!   **Return value**
//!
//!   The call `eve::oneotwoeps(as<T>())` returns [elementwise](@ref glossary_elementwise), the smallest
//!   positive value `x` of the type such that `1+x !=  x`.
//!
//!   * If T is an [integral value](@ref eve::integral_value) the elements returned are equal to one.
//!   * If T is a  [floating value](@ref eve::floating_value) the elements returned are equal to:
//!     * 4194304            if the [elements type](@ref eve::element_type) is `float`.
//!     * 2.2518e+15f        if the [elements type](@ref eve::element_type) is `double`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/core/constant/oneotwoeps.cpp}
//! @}
//================================================================================================
  inline constexpr auto oneotwoeps = functor<oneotwoeps_t>;
}
