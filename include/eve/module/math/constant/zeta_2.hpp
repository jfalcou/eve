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
//!   @var zeta_2
//!   @brief Callable object computing the constant \f$\zeta(2)\f$.
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
//!      T zeta_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::zeta_2(as<T>())` returns  \f$\zeta(2)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/zeta_2.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(zeta_2_, zeta_2);

namespace detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto zeta_2_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a51a66p+0);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a51a6625307d3p+0);
  }

  template<floating_ordered_value T, typename D>
  EVE_FORCEINLINE constexpr auto zeta_2_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a51a68p+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a51a6625307d4p+0);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.a51a66p+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.a51a6625307d3p+0);
    }
  }
}
}
