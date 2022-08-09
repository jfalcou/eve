//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var half
//!   @brief Computes the constant \f$1/2\f$.
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
//!      T half(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::half(as<T>())`  is semantically equivalent to T(0.5).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/half.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(half_, half);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto half_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0x3F000000U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x3FE0000000000000ULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto half_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return half(as<T>());
  }
}
}
