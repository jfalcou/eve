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
  //! @var half_root_two
  //!
  //! @brief Callable object computing the half_root_two constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the half_root_two constant                              |
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
  //! the half_root_two constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/half_root_two.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(half_root_two_, half_root_two);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto half_root_two_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.6a09e6p-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.6a09e667f3bcdp-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto half_root_two_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.6a09e8p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.6a09e667f3bcdp-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.6a09e6p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.6a09e667f3bccp-1);
      }
    }
  }
}
