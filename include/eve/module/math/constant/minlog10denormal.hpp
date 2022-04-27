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
  //! @var minlog10denormal
  //!
  //! @brief Callable object computing the least value for which eve::exp
  //! returns a non denormal result.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the minlog10denormal constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::minlog10denormal(as<T>())` is semantically equivalent to:
  //!   - T(-45.1545f) if eve::element_type_t<T> is float
  //!   - T(-323.607) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/minlog10denormal.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minlog10denormal_, minlog10denormal);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlog10denormal_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)  return Constant<T,  0xc2349e36U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc07439b7422d1bfbULL>();
    }
 
  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto minlog10denormal_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return minlog10denormal(as<T>());
  }
  }
}
