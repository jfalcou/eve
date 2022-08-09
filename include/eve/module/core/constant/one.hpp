//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/roundings.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var one
//!   @brief Computes the constant \f$1\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T one(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::one(as<T>())` is semantically equivalent to `T(1)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/one.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(one_, one);
namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto one_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return T(1);
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto one_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return one(as<T>());
  }
}
}
