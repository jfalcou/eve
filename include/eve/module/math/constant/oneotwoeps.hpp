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
  struct oneotwoeps_t : constant_callable<oneotwoeps_t, Options, lower_option, upper_option>
  {
    template<floating_value T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if constexpr (std::same_as<T, float>) return T{0x1p22};
      else                                  return T{0x1p51};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

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
  //!     template<eve::floating_value T> constexpr T oneotwoeps(as<T> x) noexcept;
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
