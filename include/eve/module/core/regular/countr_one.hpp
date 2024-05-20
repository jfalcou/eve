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
#include <eve/module/core/regular/countr_zero.hpp>
#include <bit>

namespace eve
{
  template<typename Options>
  struct countr_one_t : elementwise_callable<countr_one_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countr_one_t, countr_one_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countr_one
//!   @brief Computes the number of consecutive 1 in a value starting from right.
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
//!      T countr_one(T x) noexcept;
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
//!      from the least significant bit ("right"), with same type as `x`,
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/countr_one.cpp}
//! @}
//================================================================================================
  inline constexpr auto countr_one = functor<countr_one_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T countr_one_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countr_one(v));
      else
        return countr_zero(~v);
    }
  }
}
