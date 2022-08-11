//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_or
//!   @brief Computes the logical OR of its arguments.
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
//!      template< eve::value T, eve::value U >
//!      auto logical_or(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical OR of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_or(x, y)` is semantically equivalent to `x || y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
//!
//!    @note
//!      Although the infix notation with `||` is supported, the `||` operator on
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
  struct logical_or_;
}
template<> struct supports_conditional<tag::logical_or_> : std::false_type
{};

EVE_MAKE_CALLABLE(logical_or_, logical_or);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a || b);
      else                                                return a || b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return b ? true_(as<T>()) : T{a};
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return a ? true_(as<U>()) : U{b};
    }

    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
    {
      return a || b;
    }
  }
}
