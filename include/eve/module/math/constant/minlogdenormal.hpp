//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var minlogdenormal
  //!
  //! @brief Callable object computing the least value for which eve::exp
  //! returns a non zero result
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                               |
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
  //! the call `eve::minlog(as<T>())` is semantically equivalent to:
  //!   - T(-103.972f) if eve::element_type_t<T> is float
  //!   - T(-745.133) if eve::element_type_t<T> is double
  //!
  //! This is the greatest value for which `eve::pedantic(eve::exp)` is  zero
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/minlogdenormal.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minlogdenormal_, minlogdenormal);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlogdenormal_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0xc2cff1b5U>(); // -103.972084
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc0874910d52d3053ULL>();//-745.1332191019413358
    }
  }
}
