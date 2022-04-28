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
  //! @var sinh_one
  //!
  //! @brief Callable object computing the sinh_one constant value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sinh_one constant                              |
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
  //! the sinh_one constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/sinh_one.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sinh_one_, sinh_one);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto sinh_one_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.2cd9fcp+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.2cd9fc44eb982p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto sinh_one_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.2cd9fep+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.2cd9fc44eb983p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.2cd9fcp+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.2cd9fc44eb982p+0);
      }
    }
  }
}
