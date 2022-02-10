//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

 #include <eve/module/core/regular/roundings.hpp>
#include <eve/module/core/regular/exponent.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var nbmantissabits
  //!
  //! @brief Callable object computing the number of mantissa bits.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the nbmantissabits constant                               |
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
  //! the call `eve::limitexponent(as<T>())` is semantically equivalent to
  //!   - as_integer_t<T>(23) if eve::element_type_t<T> is float
  //!   - as_integer_t<T>(52) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/nbmantissabits.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(nbmantissabits_, nbmantissabits);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto nbmantissabits_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t = element_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>)
      {
        return i_t(23);
      }
      else if constexpr(std::is_same_v<t_t, double >)
      {
        return i_t(52);
      }
    }
 
  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto nbmantissabits_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return nbmantissabits(as<T>());
  }
  }
}
