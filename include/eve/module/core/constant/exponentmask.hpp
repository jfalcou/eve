//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var exponentmask
  //!
  //! @brief Callable object computing the exponent bit mask.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the exponentmask constant                         |
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
  //! the call `eve::exponentmask(as<T>())` returns [elementwise](@ref glossary_elementwise), the
  //! integral mask to extract the exponent bits of an ieee floating value. The element values are:
  //!        - 0x7f800000 if the [element type](@ref eve::element_type) is float
  //!        - 0x7ff0000000000000LL if the [element type](@ref eve::element_type) is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/exponentmask.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exponentmask_, exponentmask);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto exponentmask_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t = element_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(0x7f800000);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(0x7ff0000000000000LL);
    }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto exponentmask_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return exponentmask(as<T>());
  }
  }
}
