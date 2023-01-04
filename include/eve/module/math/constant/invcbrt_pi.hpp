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
//!   @var invcbrt_pi
//!   @brief Callable object computing the constant \f$\pi^{-1/3}\f$.
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
//!      T invcbrt_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invcbrt_pi(as<T>())` returns  the inverse of the cubic root of \f$\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/invcbrt_pi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invcbrt_pi_, invcbrt_pi);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto invcbrt_pi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.5d95ep-1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5d95df6bd2aeep-1);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto invcbrt_pi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.5d95ep-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5d95df6bd2aeep-1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.5d95dep-1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.5d95df6bd2aedp-1);
    }
  }
}
}
