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
  //! @var khinchin
  //!
  //! @brief Callable object computing the khinchin constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the khinchin constant                              |
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
  //! the khinchin constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/khinchin.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(khinchin_, khinchin);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto khinchin_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.57bce4p+1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.57bce423c6d0dp+1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto khinchin_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.57bce6p+1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.57bce423c6d0ep+1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.57bce4p+1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.57bce423c6d0dp+1);
      }
    }
  }
}
