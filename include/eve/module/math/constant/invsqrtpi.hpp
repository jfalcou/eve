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
  //! @var invsqrtpi
  //!
  //! @brief Callable object computing \f$\pi^{-1}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the invsqrtpi constant                               |
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
  //! the call `eve::invsqrtpi(as<T>())` is semantically equivalent to  `eve::rec(eve::pi(eve::as<T>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/invsqrtpi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(invsqrtpi_, invsqrtpi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto invsqrtpi_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X3F106EBBU, 0X3FE20DD750429B6DULL>(); //0.564189583547756286948079451560772585844050629329
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto invsqrtpi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
       if constexpr(std::is_same_v<D, downward_type>)
      {
        return Ieee_constant<T, 0X3F106EBAU, 0X3FE20DD750429B6DULL>();
      }
      else
      {
        return Ieee_constant<T, 0X3F106EBBU, 0X3FE20DD750429B6EULL>();
      }
    }
  }
}
