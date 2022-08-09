//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var invlog10_e
  //!
  //! @brief Callable object computing the constant \f$1/\log_{10}e\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                       |
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
  //! the invlog10_e constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/invlog10_e.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invlog10_e_, invlog10_e);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto invlog10_e_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.26bb1cp+1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.26bb1bbb55516p+1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto invlog10_e_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.26bb1cp+1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.26bb1bbb55516p+1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.26bb1ap+1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.26bb1bbb55515p+1);
      }
    }
  }
}
