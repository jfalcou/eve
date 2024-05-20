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
  struct countl_one_t : elementwise_callable<countl_one_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countl_one_t, countl_one_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countl_one
//!   @brief Computes the number of consecutive 1 in a value starting from left.
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
//!      T countl_one(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 1 ("one") bits in the value of `x`, starting
//!      from the most significant bit ("left"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/countl_one.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto countl_one = functor<countl_one_t>;

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T countl_one_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countl_one(v));
      else
        return countl_zero(~v);
    }
  }
}
