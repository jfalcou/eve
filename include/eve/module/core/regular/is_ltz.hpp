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
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_ltz_t : elementwise_callable<is_ltz_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_ltz_t, is_ltz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_ltz
//!   @brief Returns a logical true  if and only if the element value is less than 0.
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
//!      eve::as_logical<T> is_ltz(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x < 0`.
//!
//!  @groupheader{Example}
//!
//!     @godbolt{doc/core/is_ltz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_ltz[mask](x)` provides a masked version of `eve::is_ltz` which is
//!     equivalent to `if_else (mask, is_ltz(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_ltz = functor<is_ltz_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_ltz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return false_(eve::as(a));
      else
        return a <  zero(eve::as(a));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#include <eve/module/core/regular/impl/simd/x86/is_ltz.hpp>
#endif
