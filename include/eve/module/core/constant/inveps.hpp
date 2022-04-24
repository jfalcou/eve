//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var inveps
  //!
  //! @brief Callable object computing half the inverse of the machine epsilon.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the inveps constant                               |
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
  //! the call `eve::inveps(``eve::as<T>())` is semantically equivalent to
  //! `eve::rec(2*eve::eps(``eve::as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/inveps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(inveps_, inveps);

  namespace detail
  {
    template<real_value T>
    EVE_FORCEINLINE constexpr auto inveps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return T(4503599627370496);
      else if constexpr(std::is_same_v<t_t, double>) return T(8388608);
      else return T(1);
    }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto inveps_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return inveps(as<T>());
  }
  }
}
