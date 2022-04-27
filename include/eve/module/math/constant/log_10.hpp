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
  //! @var log_10
  //!
  //! @brief Callable object computing \f$\\log 2\f$.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the log_10 constant                                |
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
  //! the call `eve::log_10(as<T>())` is semantically equivalent to  `eve::log(T(2.0)`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/log_10.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log_10_, log_10);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto log_10_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X40135D8EU, 0X40026BB1BBB55516ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto log_10_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
    if constexpr(std::is_same_v<D, upward_type>)
      return eve::log_10(as<T>());
    else
      return Ieee_constant<T, 0X40135D8DU, 0X40026BB1BBB55515ULL>();
    }
  }
}
