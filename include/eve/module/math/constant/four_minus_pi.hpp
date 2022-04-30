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
  //! @var four_minus_pi
  //!
  //! @brief Callable object computing constant \f$4-\pi\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
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
  //! @godbolt{doc/math/four_minus_pi.cpp}
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
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.b7812ap-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.b7812aeef4b9fp-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto four_minus_pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.b7812cp-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.b7812aeef4b9fp-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.b7812ap-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.b7812aeef4b9ep-1);
      }
    }
  }
}
