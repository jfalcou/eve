//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_or
//!   @brief Computes the logical NOT of its [argument](@ref eve::value).
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
//!      eve::as_logical_t<T> logical_or(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The call `logical_not(x)` is semantically equivalent to `is_eqz(x)`.
//!      Infix notation can be used with `!x`.
//!
//!    **Note**
//!
//!      Although the infix notation with `!` is supported, the `!` operator on
//!      standard scalar types is the original one and so will return bool instead of
//!      eve::logical_value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/logical_or.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct logical_not_;
}
template<> struct supports_conditional<tag::logical_not_> : std::false_type
{};

EVE_MAKE_CALLABLE(logical_not_, logical_not);
}

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE auto
logical_not_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return as_logical_t<T>(!a);
}

EVE_FORCEINLINE auto
logical_not_(EVE_SUPPORTS(cpu_), bool a) noexcept
{
  return !a;
}
}
