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
#include <eve/traits/as_logical.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var false_
//!   @brief Computes  the false logical value.
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
//!      eve::as_logical<T> false_(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      the call `eve::false_(as<T>())` returns [elementwise](@ref glossary_elementwise), the false
//!      logical value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/false_.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(false__, false_);

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto false__(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return as_logical_t<T>(false);
  }
}
}
