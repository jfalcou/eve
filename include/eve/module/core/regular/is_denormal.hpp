/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/bit_value.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_denormal_t : elementwise_callable<is_denormal_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_denormal_t, is_denormal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_denormal
//!   @brief Returns a logical true if and only if the element value is denormal.
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
//!      eve::as_logical<T> is_denormal(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_denormal(x)` is semantically  equivalent to:
//!
//!     @code
//!       if constexpr(floating_value<T>)
//!         return (eve::abs(x) < eve::smallestposval(as(x))) && is_nez(x);
//!       else constexpr(integral_value<T>)
//!         return eve::false_(as(x));
//!    @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_denormal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_denormal[mask](x)` provides a masked version
//!     of `eve::is_denormal` which is
//!     equivalent to `if_else (mask, is_denormal(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_denormal.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_denormal = functor<is_denormal_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_denormal_(EVE_REQUIRES(cpu_), T const& a) noexcept
    {
      if constexpr( !floating_value<T> || !eve::platform::supports_denormals )
        return false_(eve::as<T>());
      else
        return is_nez(a) && (eve::abs(a) < smallestposval(eve::as<T>()));
    }
  }
}
// // -----------------------------------------------------------------------------------------------
// // logical masked case
//     template<conditional_expr C, ordered_value U>
//     EVE_FORCEINLINE auto
//     is_denormal_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
//     {
//       return logical_mask_op(cond, is_denormal, u);
//     }
//   }

// namespace detail
// {
//   // -----------------------------------------------------------------------------------------------
//   // logical masked case
//   template<conditional_expr C, value U, value V>
//   EVE_FORCEINLINE auto is_denormal_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
//   {
//     return logical_mask_op(cond, is_denormal, u);
//   }
// }
// }
