//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/regular/sqrt.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/floor.hpp>
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
  //! @var sqrtsmallestposval
  //!
  //! @brief Callable object computing the greatest value less
  //! than the square root of the greatest value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrtsmallestposval constant                           |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::sqrtsmallestposval(as<T>())` is the square root of`eve::smallestposval(as<T>())`.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqrtsmallestposval.cpp}
  //!
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(sqrtsmallestposval_, sqrtsmallestposval);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr  auto sqrtsmallestposval_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
        return Constant<T,  0x20000000U>();
      else if constexpr(std::is_same_v<t_t, double>)
        return Constant<T, 0x2000000000000000ULL>();
      else
        return T(1);
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto sqrtsmallestposval_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type>{}))
    {
        return sqrtsmallestposval(as<T>());
    }
  }
}
