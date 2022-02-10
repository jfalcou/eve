//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var Ieee_constant
  //!
  //! @brief Callable object computing a floating constant from its scalar hexadecimal integral representations |
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | generates a floating constant from its scalar hexadecimal integral representations |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template <floating_real_value T BitsPatternfloat, BitsPatterndouble > T operator()() const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **template Parameters**
  //!
  //!`BitsPatternfloat': hexadecimal integral representation of the float scalar constant
  //!
  //!`BitsPatterndouble': hexadecimal integral representation of the double scalar constant
  //!
  //! **Return value**
  //!
  //! the call `eve::ieee_constant(as<T>()) < T, BitsPatternfloat, BitsPatterndouble>`
  //! is semantically equivalent to :
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  using t_t = element_type_t<T>;
  //!  if constexpr(std::same_as<t_t, float>) return eve::constant<T, BitsPatternfloat>();
  //!  else                                   return eve::constant<T, BitsPatterndouble>();
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! ---
  //!
  //! #### Example
  //!
  //! godbolt{doc/core/ieee_constant.cpp}
  //!
  //! @}
  //================================================================================================
  template<floating_value T, auto BitsPatternfloat, auto BitsPatterndouble>
  EVE_FORCEINLINE auto Ieee_constant(eve::as<T> const & = {}) noexcept
  {
    using t_t = element_type_t<T>;

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
