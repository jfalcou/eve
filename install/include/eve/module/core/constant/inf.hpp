//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var inf
  //!
  //! @brief Callable object computing the infinity ieee value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the inf constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_real_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::inf(as<T>())` is semantically equivalent to  `T(std::numeric_limits<eve::element_type_t<T>>::``infinity())`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/inf.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(inf_, inf);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto inf_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      return T(std::numeric_limits<t_t>::infinity());
    }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto inf_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return inf(as<T>());
  }
  }
}
