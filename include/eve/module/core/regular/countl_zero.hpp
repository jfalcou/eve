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
#include <eve/module/core/regular/countl_zero.hpp>
#include <bit>

namespace eve
{
  template<typename Options>
  struct countl_zero_t : elementwise_callable<countl_zero_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countl_zero_t, countl_zero_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countl_zero
//!   @brief Computes the number of consecutive 0 in a value starting from left
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
//!      T countl_zero(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
//!      from the most significant bit ("left"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/countl_zero.cpp}
//! @}
//================================================================================================
  inline constexpr auto countl_zero = functor<countl_zero_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T countl_zero_(EVE_REQUIRES(cpu_), O const&, T const& x) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countl_zero(x));
      else
        return map(countl_zero, x);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/countl_zero.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/countl_zero.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/countl_zero.hpp>
#endif
