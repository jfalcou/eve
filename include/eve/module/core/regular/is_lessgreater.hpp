//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/is_ordered.hpp>

namespace eve
{
  template<typename Options>
  struct is_lessgreater_t : strict_elementwise_callable<is_lessgreater_t, Options, definitely_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_lessgreater] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_lessgreater_t, is_lessgreater_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_lessgreater
//!   @brief Returns a logical true  if and only if the elements pair are not equal or unordered.
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
//!      eve::as_logical<T> is_lessgreater(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_lessgreater(x, y)`  is semantically  equivalent to `x < y || x > y`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_lessgreater.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_lessgreater[mask](x, y)` provides a masked version of
//!     `eve::is_lessgreater` which is equivalent to `if_else (mask, is_lessgreater(x, y),
//!     eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_lessgreater = functor<is_lessgreater_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_lessgreater_(EVE_REQUIRES(cpu_),
                    O const & ,
                    logical<T> const& a, logical<U> const& b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a != b);
      else                                              return a != b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr  common_logical_t<T,U>
    is_lessgreater_(EVE_REQUIRES(cpu_),
                    O const & o,
                    T const& a, U const& b)  noexcept
    {
      return  is_not_equal[o](a, b) && is_ordered(a, b);
    }
  }
}


#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_lessgreater.hpp>
#endif
