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
  //! @var euler_pow_pi
  //!
  //! @brief Callable object computing the euler_pow_pi constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the euler_pow_pi constant                              |
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
  //! the euler_pow_pi constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/euler_pow_pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(euler_pow_pi_, euler_pow_pi);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto euler_pow_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.724046p+4);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.724046eb0933ap+4);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto euler_pow_pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.724048p+4);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.724046eb0933ap+4);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.724046p+4);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.724046eb09339p+4);
      }
    }
  }
}
