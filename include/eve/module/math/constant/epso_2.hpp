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
  //! @var epso_2
  //!
  //! @brief Callable object computing the the half of the machine epsilon.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the epso_2 constant                              |
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
  //! the call `eve::epso_2(as<T>())` is semantically equivalent to [eve::eps(as<T>())](@ref eve::eps)/2.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/epso_2.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(epso_2_, epso_2);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto epso_2_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X33800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3CA0000000000000ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto epso_2_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return epso_2(as<T>());
    }
  }
}
