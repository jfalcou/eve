//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var invpi
  //!
  //! @brief Callable object computing \f$\pi^{-1}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the invpi constant                               |
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
  //! the call `eve::invpi(as<T>())` is semantically equivalent to  `eve::rec(eve::pi(eve::as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/invpi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invpi_, invpi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto invpi_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X3EA2F983U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3FD45F306DC9C883LL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto invpi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3EA2F984U, 0X3FD45F306DC9C883LL>();
      else
        return Ieee_constant<T, 0X3EA2F983U, 0X3FD45F306DC9C882LL>();
    }
  }
}
