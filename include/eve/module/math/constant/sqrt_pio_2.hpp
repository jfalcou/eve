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
  //! @var sqrt_pio_2
  //!
  //! @brief Callable object computing constant \f$\sqrt{\pi/2}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrt_pio_2 constant                              |
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
  //! the sqrt_pio_2 constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/sqrt_pio_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqrt_pio_2_, sqrt_pio_2);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto sqrt_pio_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.40d932p+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.40d931ff62706p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto sqrt_pio_2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.40d932p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.40d931ff62706p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.40d93p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.40d931ff62705p+0);
      }
    }
  }
}
