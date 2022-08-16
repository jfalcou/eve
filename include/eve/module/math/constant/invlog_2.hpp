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
//!   @var invlog_2
//!   @brief Callable object computing the constant \f$1/\log2\f$.
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
//!      T invlog_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invlog_2(as<T>())` returns the inverse of \f$\log2\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/invlog_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invlog_2_, invlog_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto invlog_2_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X3FB8AA3BU>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0X3FF71547652B82FEULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto invlog_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, downward_type> )
      return Ieee_constant<T, 0X3FB8AA3BU, 0X3FF71547652B82FEULL>();
    else return Ieee_constant<T, 0X3FB8AA3CU, 0X3FF71547652B82FFULL>();
  }
}
}
