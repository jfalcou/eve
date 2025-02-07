//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/invocable.hpp>
#include <eve/concept/generator.hpp>
#include <eve/detail/implementation.hpp>

#include <concepts>

namespace eve
{
  template<typename Options>
  struct as_value_t : callable<as_value_t, Options>
  {
    template<generator From, value T>
    EVE_FORCEINLINE constexpr T operator()(From from, as<T> t) const noexcept
    {
      return from(t);
    }

    template<arithmetic_value From, value T>
    EVE_FORCEINLINE constexpr T operator()(From from, as<T> t) const noexcept
    {
      return T{from};
    }

    template<relaxed_logical_value From, value T>
    EVE_FORCEINLINE constexpr T operator()(From from, as<T> t) const noexcept
    {
      return T{from};
    }
  };

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //!   @var as_value
  //!   @brief converts eve constant or just a value to a type.
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
  //!      template<eve::value From, eve::value T>
  //!      T as_value(From x, eve::as<T> t) noexcept;
  //!
  //!      template<eve::generator From, eve::value T>
  //!      T as_value(From from, eve::as<T> t) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!      * `x`: either something convertible to T or an of eve constant
  //!      * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::as_value(as<T>())` returns a value of type T which is
  //!      the conversion of `x` to type Target or the the eve constant of type Target.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/constant/as_value.cpp}
  //================================================================================================
  inline constexpr auto as_value = functor<as_value_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
