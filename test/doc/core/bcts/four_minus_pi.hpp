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
  //! @var four_minus_pi
  //!
  //! @brief Callable object computing the four_minus_pi constant value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the four_minus_pi constant                              |
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
  //! the four_minus_pi constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/four_minus_pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(four_minus_pi_, four_minus_pi);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto four_minus_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return 0x1.b7812ap-1;
      else if constexpr(std::is_same_v<t_t, double>) return 0x1.b7812aeef4b9fp-1;
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto four_minus_pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.b7812cp-1;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.b7812aeef4b9fp-1;
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return 0x1.b7812ap-1;
        else if constexpr(std::is_same_v<t_t, double>) return 0x1.b7812aeef4b9ep-1;
      }
    }
  }
}
