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
  //! @var pi2o_16
  //!
  //! @brief Callable object computing constant \f$\pi^2/16\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the pi2o_16 constant                              |
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
  //! the pi2o_16 constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/pi2o_16.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(pi2o_16_, pi2o_16);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto pi2o_16_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.3bd3ccp-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.3bd3cc9be45dep-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto pi2o_16_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.3bd3cep-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.3bd3cc9be45dfp-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.3bd3ccp-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.3bd3cc9be45dep-1);
      }
    }
  }
}
