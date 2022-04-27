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
  //! @var exp_minus_one
  //!
  //! @brief Callable object computing the exp_minus_one constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the exp_minus_one constant                              |
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
  //! the exp_minus_one constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/exp_minus_one.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exp_minus_one_, exp_minus_one);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto exp_minus_one_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.78b564p-2);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.78b56362cef38p-2);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto exp_minus_one_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.78b564p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.78b56362cef38p-2);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.78b562p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.78b56362cef37p-2);
      }
    }
  }
}
