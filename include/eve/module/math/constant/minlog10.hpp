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
  //! @var minlog10
  //!
  //! @brief Callable object computing the least value for which eve::exp10
  //! returns a non zero result.
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
  //! the call `eve::minlog10(as<T>())` is semantically equivalent to:
  //!   - T(-37.9298f) if eve::element_type_t<T> is float
  //!   - T(-307.653) if eve::element_type_t<T> is double
  //!
  //! This is the greatest value for which `eve::exp10` is  zero
  //!
   //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/minlog10.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minlog10_, minlog10);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlog10_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)  return Constant<T, 0xc217b818U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc0733a7146f72a42ULL>();
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto minlog2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return minlog10(as<T>());
    }
  }
}
