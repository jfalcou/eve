//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
//!   @var mantissamask
//!   @brief Computes the mask to extract the mantissa bits of an ieee floating value.
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
//!      eve::as_unsigned<T> mantissamask(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mantissamask(as<T>())` returns [elementwise](@ref glossary_elementwise), the
//!      integral mask to extract the mantissa bits of an ieee floating value. The element values
//!      are:
//!        - 0x807FFFFFU if the [element type](@ref eve::element_type) is float
//!        - 0x800FFFFFFFFFFFFFULL if the [element type](@ref eve::element_type) is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mantissamask.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(mantissamask_, mantissamask);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto mantissamask_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    using i_t = as_integer_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return i_t(0x807FFFFFU);
    else if constexpr( std::is_same_v<t_t, double> ) return i_t(0x800FFFFFFFFFFFFFULL);
  }

  template<floating_value T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto mantissamask_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  {
    return mantissamask(as<T>());
  }
}
}
