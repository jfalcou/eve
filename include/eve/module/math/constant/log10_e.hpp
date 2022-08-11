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
//!   @var log10_e
//!   @brief Callable object computing the constant \f$\log_{10}e\f$.
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
//!      T log10_e(as<T> x) noexcept;
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
//!  @godbolt{doc/math/log10_e.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(log10_e_, log10_e);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto log10_e_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      return Ieee_constant<T, 0X3EDE5BD9, 0X3FDBCB7B1526E50ELL>(); // 0.43429448190325182765112891891660508229439700580367
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto log10_e_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      if constexpr(std::is_same_v<D, upward_type>)
        return Ieee_constant<T, 0X3EDE5BD9, 0X3FDBCB7B1526E50FLL>();
      else
        return Ieee_constant<T, 0X3EDE5BD8, 0X3FDBCB7B1526E50ELL>();

    }
  }
}
