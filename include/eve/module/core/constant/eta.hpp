//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var eta
  //!
  //! @brief Callable object computing the least denormal positive value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the eta constant; the exponent of mindenormal     |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > auto operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::eta(as<T>())` is semantically equivalent to:
  //!   - -1074 if eve::element_type_t<T> is float
  //!   - -149 if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/eta.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(eta_, eta);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto eta_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      using i_t = as_integer_t<t_t>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(-149u);
      else if constexpr(std::is_same_v<t_t, double>) return i_t(-1074);
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto eta_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return eta(as<T>());
    }
  }
}
