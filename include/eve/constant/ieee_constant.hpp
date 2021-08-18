//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var ieee_constant
  //!
  //! @brief Callable object computing the greatest positive value.
  //!
  //! **Required header:** `#include <eve/function/ieee_constant.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the values of an a flooating ieee_constant        |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < BitsPatternfloat, BitsPatterndouble, value T > T operator()( as < Target > const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::ieee_constant(as<T>())` is semantically equivalent to  `TO DO`
  //!
  //! ---
  //!
  //! #### Example
  //!  //! @godbolt{doc/core/ieee_constant.cpp}
  //!
  //! @}
  //================================================================================================
  template<floating_value T, auto BitsPatternfloat, auto BitsPatterndouble>
  EVE_FORCEINLINE auto Ieee_constant(eve::as<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>)
    {
      if constexpr(sizeof(t_t) != sizeof(BitsPatternfloat))
      {
        static_assert(sizeof(t_t) == sizeof(BitsPatternfloat),
                      "[eve::ieeeconstant] floating_point case - BitsPatternfloat has not the correct size");
        return T{};
      }
      else return static_cast<T>(bit_cast(BitsPatternfloat, as<t_t>()));
    }
    else // if constexpr(std::is_same_v<t_t, double>)
    {
      if constexpr(sizeof(t_t) != sizeof(BitsPatterndouble))
      {
        static_assert(sizeof(t_t) == sizeof(BitsPatterndouble),
                      "[eve::ieeeconstant] floating_point case - BitsPatterndouble has not the correct size");
        return T{};
      }
      else return static_cast<T>(bit_cast(BitsPatterndouble, as<t_t>()));
    }
  }
}
