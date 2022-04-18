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
  //! @var pi_minus_three
  //!
  //! @brief Callable object computing the pi_minus_three constant value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pi_minus_three constant                              |
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
  //! the pi_minus_three constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/pi_minus_three.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pi_minus_three_, pi_minus_three);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto pi_minus_three_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return 0x1.21fb54p-3;
      else if constexpr(std::is_same_v<t_t, double>) return 0x1.21fb54442d184p-3;
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto pi_minus_three_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.21fb56p-3;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.21fb54442d185p-3;
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.21fb54p-3;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.21fb54442d184p-3;
      }
    }
  }
}
