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
  //! @var log_log_2
  //!
  //! @brief Callable object computing the log_log_2 constant value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the log_log_2 constant                              |
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
  //! the log_log_2 constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/log_log_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log_log_2_, log_log_2);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto log_log_2_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return -0x1.774f2ap-2;
      else if constexpr(std::is_same_v<t_t, double>) return -0x1.774f29bdd6b9fp-2;
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto log_log_2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return -0x1.774f28p-2;
        else if constexpr(std::is_same_v<t_t, double>) return -0x1.774f29bdd6b9ep-2;
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return -0x1.774f2ap-2;
        else if constexpr(std::is_same_v<t_t, double>) return -0x1.774f29bdd6b9fp-2;
      }
    }
  }
}
