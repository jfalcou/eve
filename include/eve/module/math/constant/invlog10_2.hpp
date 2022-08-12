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
//!   @var invlog10_2
//!   @brief Callable object computing the constant \f$1/\log_{10}2\f$.
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
//!      T invlog10_2(as<T> x) noexcept;
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
//!  @godbolt{doc/math/invlog10_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invlog10_2_, invlog10_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto invlog10_2_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0x40549a78U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x400a934f0979a371ULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto invlog10_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, upward_type> )
      return Ieee_constant<T, 0x40549a79U, 0x400a934f0979a372ULL>();
    else return Ieee_constant<T, 0x40549a78U, 0x400a934f0979a371ULL>();
  }
}
}
