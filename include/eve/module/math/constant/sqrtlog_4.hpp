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
//!   @var sqrtlog_4
//!   @brief Callable object computing the constant \f$\sqrt{\log4}\f$.
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
//!      T sqrtlog_4(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrtlog_4(as<T>())` returns the square root of \f$\log4\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sqrtlog_4.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrtlog_4_, sqrtlog_4);

namespace detail
{
  template<flating_ordered_value T>
  EVE_FORCEINLINE auto sqrtlog_4_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2d6abep+0);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2d6abe44afc43p+0);
  }

  template<flating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto sqrtlog_4_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2d6acp+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2d6abe44afc44p+0);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.2d6abep+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.2d6abe44afc43p+0);
    }
  }
}
}
