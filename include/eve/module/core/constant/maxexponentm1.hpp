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
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxexponentm1
//!   @brief Computes the  the greatest exponent of a floating point IEEE value minus one.
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
//!      eve::as_integer<T> maxexponentm1(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//! the call `eve::limitexponent(as<T>())` is semantically equivalent to
//!   - as_integer_t<T>(126) if eve::element_type_t<T> is float
//!   - as_integer_t<T>(1022) if eve::element_type_t<T> is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxexponentm1.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(maxexponentm1_, maxexponentm1);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto maxexponentm1_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    using i_t = as_integer_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return i_t(126);
    else if constexpr( std::is_same_v<t_t, double> ) return i_t(1022);
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto maxexponentm1_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return maxexponentm1(as<T>());
  }
}
}
