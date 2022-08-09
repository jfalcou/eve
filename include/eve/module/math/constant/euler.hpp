//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
  //! @var euler
  //!
  //! @brief Callable object computing the constant \f$\exp1\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                                |
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
  //! the call `eve::eeuler(as<T>())` is semantically equivalent to  `eve::exp``(T(1))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/euler.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(euler_, euler);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto euler_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X402DF854U, 0X4005BF0A8B145769ULL>(); // 2.7182818284590452353602874713526624977572470937;
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto euler_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, downward_type>)
        return eve::euler(as<T>());
      else
        return Ieee_constant<T, 0X402DF855U, 0X4005BF0A8B14576AULL>();
    }
  }
}
