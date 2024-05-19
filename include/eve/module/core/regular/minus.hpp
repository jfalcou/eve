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
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/constant/signmask.hpp>

namespace eve
{
  template<typename Options>
  struct minus_t : elementwise_callable<minus_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(minus_t, minus_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minus
//!   @brief Computes the opposite of the parameter that must be signed.
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
//!      T minus(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     *  The result is  the opposite of `x` if this value is representable in the type of `x`.
//!
//!     *  More specifically, for signed integers the opposite value of [their lowest finite value](@ref eve::valmin)
//!        is not representable and the result is undefined behaviour.
//!
//!  @note
//!   * Although the operator notation with `-` is supported, the `-` operator on
//!     standard scalar type is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/minus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minus[mask](x)` provides a masked version of `eve::minus` which is
//!     equivalent to `if_else (mask, eve::minus(x), x)`.
//!
//!   * eve::saturated
//!
//!     The call `eve::saturated(eve::minus)(x)` computes a saturated version of eve::minus.
//!
//!     More specifically, for any signed integer value `x`, the expression
//!     `eve::saturated(eve::minus)(eve::valmin(as(x)))` evaluates to `eve::valmax(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto minus = functor<minus_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T minus_(EVE_REQUIRES(cpu_), O const &, T v) noexcept
    {
      if      constexpr( floating_value<T> ) return bit_xor(v, signmask(eve::as(v)));
      else if constexpr(O::contains(saturated2))
      {
        return if_else(v == valmin(as<T>()), valmax(as<T>()), minus(v));
      }
      else
      {
        if constexpr( simd_value<T> ) return -v;
        else                          return T{0} - v;
      }
    }
  }
}

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/minus.hpp>
#endif
