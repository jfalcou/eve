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
  //! @var zeta_two
  //!
  //! @brief Callable object computing the zeta_two constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the zeta_two constant                              |
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
  //! the zeta_two constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/zeta_two.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(zeta_two_, zeta_two);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto zeta_two_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.a51a66p+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.a51a6625307d3p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto zeta_two_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.a51a68p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.a51a6625307d4p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.a51a66p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.a51a6625307d3p+0);
      }
    }
  }
}
