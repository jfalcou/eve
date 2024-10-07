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
  struct eps_t : constant_callable<eps_t, Options, lower_option, upper_option>
  {
    template<plain_value T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if      constexpr (std::integral<T>       ) return T{1};
      else if constexpr (std::same_as<T, float> ) return T{0x1p-23};
      else if constexpr (std::same_as<T, double>) return T{0x1p-52};
    }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(eps_t, eps_);
  };

  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var eps
  //!   @brief Computes a constant to the machine epsilon.
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
  //!     template<eve::plain_value T> constexpr T eps(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!   **Return value**
  //!
  //!   The call `eve::eps(as<T>())` returns [elementwise](@ref glossary_elementwise), the smallest
  //!   positive value `x` of the type such that `1+x !=  x`.
  //!
  //!   * If T is an [integral value](@ref eve::integral_value) the elements returned are equal to one.
  //!   * If T is a  [floating value](@ref eve::floating_value) the elements returned are equal to:
  //!     * 2.220446049250313e-16 if the [elements type](@ref eve::element_type) is `float`.
  //!     * 1.1920929e-07f        if the [elements type](@ref eve::element_type) is `double`.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/core/constant/eps.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto eps = functor<eps_t>;
}
