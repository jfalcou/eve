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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct fast_two_sub_t : elementwise_callable<fast_two_sub_t, Options>
  {
    template<eve::floating_value T, eve::floating_value U>
    constexpr EVE_FORCEINLINE kumi::tuple<common_value_t<T, U>, common_value_t<T, U>>
    operator()(T t, U u) const noexcept
    { return EVE_DISPATCH_CALL(t, u); }

    EVE_CALLABLE_OBJECT(fast_two_sub_t, fast_two_sub_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var quick_two_add
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  sub and error,
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
//! @warning   raw version assube |x| >= |y|,  regular assert if the condition is not met
//!            and only pedantic version treat infinite values properly
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/quick_two_add.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto fast_two_sub = functor<fast_two_sub_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE auto
    fast_two_sub_(EVE_REQUIRES(cpu_), O const&
                 , T a
                 , U b) noexcept
    {
      EVE_ASSERT(eve::all(is_not_less(eve::abs(a), eve::abs(b))), "|a| >=  |b| not satisfied for all elements");
      T s   = a - b;
      T err =  (a-s) -b;
      if constexpr(eve::platform::supports_infinites ) err = if_else(is_finite(s), err, zero);
      return eve::zip(s, err);
    }
  }
}
