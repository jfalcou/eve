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
//!   @var cosh_1
//!   @brief Callable object computing the constant \f$\cosh1\f$.
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
//!      T cosh_1(as<T> x) noexcept;
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
//!  @godbolt{doc/math/cosh_1.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(cosh_1_, cosh_1);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto cosh_1_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.8b0756p+0);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f55p+0);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto cosh_1_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.8b0756p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f551p+0);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.8b0754p+0);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.8b07551d9f55p+0);
      }
    }
  }
}
