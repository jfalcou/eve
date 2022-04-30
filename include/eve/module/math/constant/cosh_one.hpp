//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var cosh_one
  //!
  //! @brief Callable object computing the cosh_one constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the cosh_one constant                              |
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
  //! the cosh_one constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/cosh_one.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cosh_one_, cosh_one);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto cosh_one_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.8b0756p+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f55p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto cosh_one_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.8b0756p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f551p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.8b0754p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f55p+0);
      }
    }
  }
}
