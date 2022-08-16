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
//!   @var glaisher
//!   @brief Callable object computing the Glaisher-Kinkelin constant.
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
//!      T glaisher(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::glaisher(as<T>())` returns the Glaisher-Kinkelin constant.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/glaisher.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(glaisher_, glaisher);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto glaisher_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.484d24p+0);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.484d24f2fd873p+0);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto glaisher_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.484d26p+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.484d24f2fd874p+0);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.484d24p+0);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.484d24f2fd873p+0);
    }
  }
}
}
