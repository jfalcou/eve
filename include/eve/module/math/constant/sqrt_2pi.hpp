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
//!   @var sqrt_2pi
//!   @brief Callable object computing the constant \f$\sqrt{2\pi}\f$.
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
//!      T sqrt_2pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_2pi(as<T>())` returns athe square root of \f$2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sqrt_2pi.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sqrt_2pi_, sqrt_2pi);

namespace detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto sqrt_2pi_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<t_t, float> ) return T(0x1.40d932p+1);
    else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.40d931ff62706p+1);
  }

  template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto sqrt_2pi_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    using t_t = element_type_t<T>;
    if constexpr( std::is_same_v<D, upward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.40d932p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.40d931ff62706p+1);
    }
    else if constexpr( std::is_same_v<D, downward_type> )
    {
      if constexpr( std::is_same_v<t_t, float> ) return T(0x1.40d93p+1);
      else if constexpr( std::is_same_v<t_t, double> ) return T(0x1.40d931ff62705p+1);
    }
  }
}
}
