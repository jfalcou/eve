//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/module/core/decorator/roundings.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var nan
//!   @brief Computes the IEEE NaN constant
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
//!      template< eve::floating_value T >
//!      T nan(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::nan(as<T>())`  is semantically equivalent to  `T(0.0/0.0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/nan.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(nan_, nan);

namespace detail
{
  template<typename T>
  requires(plain_scalar_value<element_type_t<T>>)
  EVE_FORCEINLINE constexpr auto nan_(EVE_SUPPORTS(cpu_), as<T> const& tgt) noexcept
  {
    return allbits(tgt);
  }

  template<typename T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto nan_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  -> decltype(nan(as<T>()))
  {
    return nan(as<T>());
  }
}
}
