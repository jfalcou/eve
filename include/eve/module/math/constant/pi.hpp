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
//!   @var pi
//!   @brief Callable object computing the constant \f$\pi\f$.
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
//!      T pi(as<T> x) noexcept;
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
//!  @godbolt{doc/math/pi.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(pi_, pi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto pi_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;


      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x40490FDBU>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x400921FB54442D18ULL>();
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t           = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        if constexpr(std::is_same_v<D, upward_type>)
          return eve::pi(as<T>());
        else
          return Constant<T,  0x40490FDAU>();
      }
      else
      {
        if constexpr(std::is_same_v<D, downward_type>)
          return eve::pi(as<T>());
        else
          return Constant<T, 0x400921FB54442D19ULL>();
      }
    }
  }
}
