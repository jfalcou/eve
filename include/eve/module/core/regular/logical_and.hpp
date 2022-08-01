//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_logical
  //! @{
  //!   @var logical_and
  //!   @brief Computes the logical AND of its [arguments](@ref eve::value).
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
  //!      auto logical_and(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!     Returns the logical AND of the two parameters following the
  //!     [logical operations semantic](@ref glossary_logical).
  //!
  //!
  //!      The call `logical_and(x, y)` is semantically equivalent to `x && y`
  //!      if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
  //!
  //!    **Note**
  //!
  //!      Although the infix notation with `&&` is supported, the `&&` operator on
  //!      standard scalar types is the original one and so will return bool instead of eve::logical_value.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/logical_and.cpp}
  //! @}
  //================================================================================================
  namespace tag { struct logical_and_; }
  template<> struct supports_conditional<tag::logical_and_> : std::false_type {};

  EVE_MAKE_CALLABLE(logical_and_, logical_and);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a && b);
      else                                                return a && b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return b ? T{a} : false_(as<T>());
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return a ? U{b} : false_(as<U>());
    }

    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
    {
      return a && b;
    }
  }
}
