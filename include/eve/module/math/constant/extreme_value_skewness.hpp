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
  //! @var extreme_value_skewness
  //!
  //! @brief Callable object computing the extreme value distribution skewness : \f$12\sqrt6\zeta(3)/\pi^3\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the extreme_value_skewness constant                              |
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
  //! the extreme_value_skewness constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/extreme_value_skewness.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(extreme_value_skewness_, extreme_value_skewness);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto extreme_value_skewness_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.23b95cp+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d31p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto extreme_value_skewness_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.23b95cp+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d32p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.23b95ap+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d31p+0);
      }
    }
  }
}
