//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var pi_pow_euler
  //!
  //! @brief Callable object computing the pi_pow_euler constant value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pi_pow_euler constant                              |
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
  //! the pi_pow_euler constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/pi_pow_euler.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pi_pow_euler_, pi_pow_euler);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto pi_pow_euler_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return 0x1.6758b6p+4;
      else if constexpr(std::is_same_v<t_t, double>) return 0x1.6758b5c381111p+4;
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto pi_pow_euler_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.6758b6p+4;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.6758b5c381112p+4;
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.6758b4p+4;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.6758b5c381111p+4;
      }
    }
  }
}
