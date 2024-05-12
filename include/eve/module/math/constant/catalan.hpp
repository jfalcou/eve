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
  //! @var catalan
  //!
  //! @brief Callable object computing the catalan constant \f$\beta(2) = \sum_0^\infty \frac{(-1)^n}{(2n+1)^2}.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                              |
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
  //! the catalan constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/catalan.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(catalan_, catalan);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE T catalan_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.d4f972p-1);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.d4f9713e8135dp-1);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr T catalan_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.d4f972p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.d4f9713e8135ep-1);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.d4f97p-1);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.d4f9713e8135dp-1);
      }
    }
  }
}
