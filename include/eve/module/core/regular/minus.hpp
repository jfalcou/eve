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
#include <eve/module/core/regular/bit_not.hpp>
#include <eve/module/core/constant/signmask.hpp>

namespace eve
{
  template<typename Options>
  struct minus_t : elementwise_callable<minus_t, Options, saturated_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), a);
    }

    EVE_CALLABLE_OBJECT(minus_t, minus_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minus
//!   @brief Computes the opposite of the parameter that must be signed.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto minus(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto minus[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto minus[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto minus[saturated](value auto x)               noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The result is  the opposite of `x` if this value is representable in the type of `x`.
//!          More specifically, for signed integers the opposite value of [their lowest finite value](@ref valmin)
//!          is not representable and the result is incorrect (in this case eve::minus(valmin) is valmin).
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The saturated version of eve::minus. More specifically, for any signed integer value `x`, the expression
//!         `minus[saturated](valmin(as{x}))` evaluates to `valmax(as{x})`.
//!
//!  @note  Although the operator notation with `-` is supported, the `-` operator on
//!     standard scalar type is the original one and so can lead to automatic promotion.
//!     Also contrarily to `-` on signed scalar integral values,  `eve::minus is never undefined behaviour.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/minus.cpp}
//================================================================================================
  inline constexpr auto minus = functor<minus_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T minus_(EVE_REQUIRES(cpu_), O const&, T v) noexcept
    {
      if      constexpr (floating_value<T>)
      {
        return bit_xor(v, signmask(eve::as{v}));
      }
      else if constexpr (O::contains(saturated))
      {
        return if_else(v == valmin(as<T>{}), valmax(as<T>{}), minus(v));
      }
      else
      {
        using u_t = as_integer_t<T, unsigned>;
        if (unsigned_value<T>)
        {
          if constexpr (simd_value<T>) return bit_not(v)+1;
          else                         return -v;
        }
        else
        {
          if constexpr (simd_value<T>) return bit_cast(-bit_cast(v, as<u_t>{}), as<T>{});
          else                         return T(-(u_t(v)));
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/minus.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/minus.hpp>
#endif
