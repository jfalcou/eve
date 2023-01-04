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
//!   @var log2_e
//!   @brief Callable object computing the constant \f$\log_2 e\f$.
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
//!      T log2_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log2_e(as<T>())` returns \f$\log_2 e\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log2_e.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(log2_e_, log2_e);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto log2_e_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return Ieee_constant<
        T,
        0X3FB8AA3BU,
        0X3FF71547652B82FEULL>(); // 1.442695040888963407359924681001892137426645954153
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto log2_e_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0X3FB8AA3CU, 0X3FF71547652B82FFULL>();
    else return Ieee_constant<T, 0X3FB8AA3BU, 0X3FF71547652B82FEULL>();
  }
}
}
