//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var nbmantissabits
//!   @brief Returns the number of mantissa bits of a floating point value.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T nbmantissabits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::nbmantissabits(as<T>())` is semantically equivalent to:
//!         * `as_integer_t<T>(23)` if `eve::element_type_t<T>` is float
//!         * `as_integer_t<T>(52)` if `eve::element_type_t<T>` is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/nbmantissabits.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(nbmantissabits_, nbmantissabits);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto nbmantissabits_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    using i_t = as_integer_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) { return i_t(23); }
    else if constexpr( std::is_same_v<t_t, double> ) { return i_t(52); }
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto
  nbmantissabits_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return nbmantissabits(as<T>());
  }
}
}
