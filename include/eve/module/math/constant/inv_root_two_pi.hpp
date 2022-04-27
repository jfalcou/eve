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
  //! @addtogroup core
  //! @{
  //! @var inv_root_two_pi
  //!
  //! @brief Callable object computing the inv_root_two_pi constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the inv_root_two_pi constant                              |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the inv_root_two_pi constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/inv_root_two_pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(inv_root_two_pi_, inv_root_two_pi);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto inv_root_two_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.988454p-2);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d43651p-2);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto inv_root_two_pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.988454p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d43651p-2);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.988452p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d4365p-2);
      }
    }
  }
}
