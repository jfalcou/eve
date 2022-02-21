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
#include <eve/traits/as_integer.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var mantissamask
  //!
  //! @brief Callable object computing the mantissa bit mask.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the mantissamask constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::mantissamask(as<T>())` returns [elementwise](@ref glossary_elementwise), the
  //! integral mask to extract the exponent bits of an ieee floating value. The element values are:
  //!        - 0x807FFFFFU if the [element type](@ref eve::element_type) is float
  //!        - 0x800FFFFFFFFFFFFFULL if the [element type](@ref eve::element_type) is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/mantissamask.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mantissamask_, mantissamask);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto mantissamask_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t = element_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(0x807FFFFFU);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(0x800FFFFFFFFFFFFFULL);
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto mantissamask_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return mantissamask(as<T>());
    }
  }
}
