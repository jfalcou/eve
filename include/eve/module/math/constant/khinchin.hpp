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
//!   @var khinchin
//!   @brief Callable object computing the Khinchin constant.
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
//!      T khinchin(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::khinchin(as<T>())` returns a value of type T with all bits set.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/khinchin.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(khinchin_, khinchin);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto khinchin_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.57bce4p+1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.57bce423c6d0dp+1);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto khinchin_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.57bce6p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.57bce423c6d0ep+1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.57bce4p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.57bce423c6d0dp+1);
    }
  }
}
}
