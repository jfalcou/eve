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
//!   @var invlog10_e
//!   @brief Callable object computing the constant \f$1/\log_{10}e\f$.
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
//!      T invlog10_e(as<T> x) noexcept;
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
//!  @godbolt{doc/math/invlog10_e.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(invlog10_e_, invlog10_e);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto invlog10_e_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.26bb1cp+1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.26bb1bbb55516p+1);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto invlog10_e_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.26bb1cp+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.26bb1bbb55516p+1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.26bb1ap+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.26bb1bbb55515p+1);
    }
  }
}
}
