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
  //! @var sqrt_pi
  //!
  //! @brief Callable object computing constant \f$\sqrt{\pi}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrt_pi constant                              |
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
  //! the sqrt_pi constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/sqrt_pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrt_pi_, sqrt_pi);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto sqrt_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.c5bf8ap+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.c5bf891b4ef6bp+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto sqrt_pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.c5bf8ap+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.c5bf891b4ef6bp+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.c5bf88p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.c5bf891b4ef6ap+0);
      }
    }
  }
}
