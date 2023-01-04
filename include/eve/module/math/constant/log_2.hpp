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
//!   @var log_2
//!   @brief Callable object computing the constant \f$\log 2\f$.
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
//!      T log_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log_2(as<T>())` returns \f$\log 2\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(log_2_, log_2);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto log_2_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X3F317218U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0X3FE62E42FEFA39EFULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto log_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> )
    {
      if constexpr( std::is_same_v<D, upward_type> ) return eve::log_2(as<T>());
      else return Constant<T, 0X3F317217U>();
    }
    else
    {
      if constexpr( std::is_same_v<D, downward_type> ) return eve::log_2(as<T>());
      else return Constant<T, 0X3FE62E42FEFA39F0ULL>();
    }
  }
}
}
