//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var four_pio_3
  //!
  //! @brief Callable object computing the constant \f$4\pi/3\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                              |
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
  //! the four_pio_3 constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/four_pio_3.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(four_pio_3_, four_pio_3);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto four_pio_3_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.0c1524p+2);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.0c152382d7366p+2);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto four_pio_3_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.0c1524p+2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.0c152382d7366p+2);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.0c1522p+2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.0c152382d7365p+2);
      }
    }
  }
}
