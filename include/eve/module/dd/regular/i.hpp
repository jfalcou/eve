//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include "eve/module/complex/regular/traits.hpp"
namespace eve
{
  //================================================================================================
  //! @addtogroup complex
  //! @{
  //! @var i
  //!
  //! @brief Callable object computing the pure imaginary (\f$\i\f$) value.
  //!
  //! **Required header:** `#include <eve/module/complex.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the i constant                                    |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::i(as<T>())` is semantically equivalent to  `eve::complex{0,T{1}`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/complex/i.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(i_, i);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto i_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return eve::as_complex_t<as_real_t<T>>{0,1};
    }
  }
}
