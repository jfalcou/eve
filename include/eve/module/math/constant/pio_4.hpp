//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var pio_4
  //!
  //! @brief Callable object computing the \f$\pi/4\f$ value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pio_4 constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()( as <T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::pio_4(as<T>())` is semantically equivalent to  `eve::atan``(T(1))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/pio_4.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pio_4_, pio_4);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto pio_4_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,   0X3F490FDB>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T,  0X3FE921FB54442D18LL>();
    }
  }
}
