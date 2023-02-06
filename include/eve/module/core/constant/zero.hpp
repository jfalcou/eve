//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
//!   @var zero
//!   @brief Computes the constant 0
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
//!      T zero(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::zero(as<T>())` is semantically equivalent to  `T(0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/zero.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(zero_, zero);

namespace detail
{
  template<typename T>
  requires(plain_scalar_value<element_type_t<T>>)
  EVE_FORCEINLINE T zero_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    return T{0};
  }

  template<typename T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto zero_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  -> decltype(zero(as<T>()))
  {
    return zero(as<T>());
  }
}
}
