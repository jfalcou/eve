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
  //! @var sin_one
  //!
  //! @brief Callable object computing the sin_one constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sin_one constant                              |
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
  //! the sin_one constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/sin_one.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sin_one_, sin_one);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto sin_one_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.aed548p-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.aed548f090ceep-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto sin_one_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.aed54ap-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.aed548f090cefp-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.aed548p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.aed548f090ceep-1);
      }
    }
  }
}
