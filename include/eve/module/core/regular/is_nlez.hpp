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
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_nlez_t : elementwise_callable<is_nlez_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_nlez_t, is_nlez_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nlez
//!   @brief Returns a logical true  if and only if the element value is not less or equal to 0.
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
//!      eve::as_logical<T> is_nlez(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `!(x <= 0)`.
//!
//!   @note
//!    This is not equivalent to `(x >=   0)` for floating values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_nlez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_nlez[mask](x)` provides a masked version of `eve::is_nlez` which is
//!     equivalent to `if_else (mask, is_nlez(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_nlez.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_nlez = functor<is_nlez_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nlez_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return is_nez(a);
      else
      {
        if constexpr( scalar_value<T> )
        {
          if constexpr( integral_value<T> ) return is_gtz(a);
          else if constexpr( floating_value<T> ) return is_gtz(a) || is_nan(a);
        }
        else return is_not_less_equal(a, zero(eve::as(a)));
      }
    }
  }
}
