//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var invlog_10
//!   @brief Callable object computing 1/log(10).
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T invlog_10(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns a value of type T with all bits set.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/invlog_10.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invlog_10_, invlog_10);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto invlog_10_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0x3ede5bd9U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x3fdbcb7b1526e50EULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto invlog_10_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0x3ede5bd9U, 0x3fdbcb7b1526e50fULL>();
    else return Ieee_constant<T, 0x3ede5bd8U, 0x3fdbcb7b1526e50eULL>();
  }
}
}
