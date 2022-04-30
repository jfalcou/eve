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
  //! @var pi
  //!
  //! @brief Callable object computing \f$\pi\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pi constant                                   |
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
  //! the call `eve::pi(as<T>())` is semantically equivalent to  `4*eve::atan``(T(1))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pi_, pi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto pi_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;


      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x40490FDBU>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x400921FB54442D18ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t           = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        if constexpr(std::is_same_v<D, upward_type>)
          return eve::pi(as<T>());
        else
          return Constant<T,  0x40490FDAU>();
      }
      else
      {
        if constexpr(std::is_same_v<D, downward_type>)
          return eve::pi(as<T>());
        else
          return Constant<T, 0x400921FB54442D19ULL>();
      }
    }
  }
}
