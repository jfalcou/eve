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
//!   @var extreme_value_skewness
//!   @brief Callable object computing the extreme value distribution skewness : \f$12\sqrt6\zeta(3)/\pi^3\f$.
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
//!      T extreme_value_skewness(as<T> x) noexcept;
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
//!  @godbolt{doc/math/extreme_value_skewness.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(extreme_value_skewness_, extreme_value_skewness);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto extreme_value_skewness_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.23b95cp+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d31p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto extreme_value_skewness_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.23b95cp+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d32p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.23b95ap+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.23b95bd431d31p+0);
      }
    }
  }
}
