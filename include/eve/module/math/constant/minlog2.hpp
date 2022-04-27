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
  //! @var minlog2
  //!
  //! @brief Callable object computing the least value for which eve::exp2
  //! returns a non denormal result
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the minlog2 constant                               |
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
  //! the call `eve::minlog2(as<T>())` is semantically equivalent to:
  //!   - T(-127.0f) if eve::element_type_t<T> is float
  //!   - T(-1022.0) if eve::element_type_t<T> is double
  //!
  //! This is the greatest real value for which `eve::exp2` evaluates to zero
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/minlog2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minlog2_, minlog2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlog2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)  return Constant<T,  0xc2fe0000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc08ff00000000000ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto minlog2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return minlog2(as<T>());
    }
  }
}
