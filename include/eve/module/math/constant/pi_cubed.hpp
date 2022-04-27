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
  //! @var pi_cubed
  //!
  //! @brief Callable object computing the pi_cubed constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pi_cubed constant                              |
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
  //! the pi_cubed constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/pi_cubed.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pi_cubed_, pi_cubed);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto pi_cubed_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.f019b6p+4);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f019b59389d7cp+4);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto pi_cubed_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.f019b6p+4);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f019b59389d7dp+4);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.f019b4p+4);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f019b59389d7cp+4);
      }
    }
  }
}
