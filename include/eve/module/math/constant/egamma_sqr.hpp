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
//!   @var egamma_sqr
//!   @brief Callable object computing the square of the [Euler-Mascheroni constant](@ref
//!   eve::egamma).
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
//!      T egamma_sqr(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::egamma_sqr(as<T>())` returns the square of the [Euler-Mascheroni constant](@ref
//!      eve::egamma).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/egamma_sqr.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(egamma_sqr_, egamma_sqr);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto egamma_sqr_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.552c98p-2);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.552c97fa03695p-2);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto egamma_sqr_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.552c98p-2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.552c97fa03696p-2);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.552c96p-2);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.552c97fa03695p-2);
    }
  }
}
}
