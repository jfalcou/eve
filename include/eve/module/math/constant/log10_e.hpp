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
  //! @var log10_e
  //!
  //! @brief Callable object computing \f$\log_10 e\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the log10_e constant                               |
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
  //! the call `eve::log10_e(as<T>())` is semantically equivalent to  `eve::log(T(2.0)`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/log10_e.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log10_e_, log10_e);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto log10_e_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X3EDE5BD9, 0X3FDBCB7B1526E50ELL>(); // 0.43429448190325182765112891891660508229439700580367
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto log10_e_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3EDE5BD9, 0X3FDBCB7B1526E50FLL>();
      else
        return Ieee_constant<T, 0X3EDE5BD8, 0X3FDBCB7B1526E50ELL>();

    }
  }
}
