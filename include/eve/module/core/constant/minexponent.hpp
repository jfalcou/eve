//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var minexponent
//!   @brief Computes the  the greatest exponent of a floating point IEEE value
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
//!      template< eve::value T >
//!      eve::as_integer<T> minexponent(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::limitexponent(as<T>())` is semantically equivalent to
//!       * `as_integer_t<T>(-126)` if `eve::element_type_t<T>` is float
//!       * `as_integer_t<T>(-1022)` if `eve::element_type_t<T>` is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/minexponent.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minexponent_, minexponent);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto minexponent_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    using i_t = as_integer_t<t_t>;

    if constexpr( std::is_same_v<t_t, float> ) return i_t(-126);
    else if constexpr( std::is_same_v<t_t, double> ) return i_t(-1022);
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto minexponent_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return minexponent(as<T>());
  }
}
}
