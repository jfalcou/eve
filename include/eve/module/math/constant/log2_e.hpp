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
  //! @var log2_e
  //!
  //! @brief Callable object computing the constant \f$\log_2 e\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                               |
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
  //! the call `eve::log2_e(as<T>())` is semantically equivalent to  `eve::log(T(2.0)`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/log2_e.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log2_e_, log2_e);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto log2_e_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X3FB8AA3BU, 0X3FF71547652B82FEULL >(); // 1.442695040888963407359924681001892137426645954153
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto log2_e_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3FB8AA3CU, 0X3FF71547652B82FFULL >();
      else
        return Ieee_constant<T, 0X3FB8AA3BU, 0X3FF71547652B82FEULL >();

    }
  }
}
