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
  //! @var minlog
  //!
  //! @brief Callable object computing the least value for which eve::exp
  //! returns a non denormal result
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the minlog constant                               |
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
  //! the call `eve::minlog(as<T>())` is semantically equivalent to:
  //!   - T(-87.3763f) if eve::element_type_t<T> is float
  //!   - T(-708.396) if eve::element_type_t<T> is double
  //!
  //! This is the greatest real value for which `eve::exp` evaluates to zero
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/minlog.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minlog_, minlog);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlog_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,0xc2aec0a5>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc086232bdd7abcd3ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto minlog_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return minlog(as<T>());
    }
  }
}
