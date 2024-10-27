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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/module/core/regular/is_infinite.hpp>

namespace eve
{
  template<typename Options>
  struct fast_two_add_t : elementwise_callable<fast_two_add_t, Options>
  {
    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE zipped<common_value_t<T, U>, common_value_t<T, U>>
    operator()(T t, U u) const noexcept
    { return EVE_DISPATCH_CALL(t, u); }

    EVE_CALLABLE_OBJECT(fast_two_add_t, fast_two_add_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var fast_two_add
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  add and error,
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
//!      template< eve::floating_value T, eve::floating_value U  >
//!      kumi::tuple<T, T> quick_two_add(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x+y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`
//!
//! where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
//! @warning   the algoritm needs |x| >= |y|,  and will assert if the condition is not met
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fast_two_add.cpp}
//================================================================================================
  inline constexpr auto fast_two_add = functor<fast_two_add_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE auto fast_two_add_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
    {
      EVE_ASSERT(eve::all(is_not_less(eve::abs(a), eve::abs(b))), "|a| >=  |b| not satisfied for all elements");
      T s   = a + b;
      T err =  b - (s - a);
      if constexpr(eve::platform::supports_infinites ) err = if_else(is_finite(s), err, zero);
      return  eve::zip(s, err);
    }
  }
}
