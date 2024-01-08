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
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core
//! @{
//! @var Ieee_constant
//!
//! @brief Callable object computing a floating constant from its scalar hexadecimal integral
//! representations |
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | generates a floating constant from its scalar hexadecimal integral
//! representations |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template <floating_ordered_value T BitsPatternfloat, BitsPatterndouble > T operator()() const
//!  noexcept;
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
//! godbolt{doc/core/constant/ieee_constant.cpp}
//!
//! @}
//================================================================================================
  template<floating_value T>
  EVE_FORCEINLINE auto ieee_constant(float vf,  double vd, eve::as<T> const& = {}) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr( std::same_as<elt_t, float> )
    {
      return T(vf);
    }
    else if constexpr(std::same_as<elt_t, double>)
    {
       return T(vd);
    }
  }
}
