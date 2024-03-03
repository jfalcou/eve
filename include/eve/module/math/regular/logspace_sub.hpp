//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{ template<typename Options>
  struct logspace_sub_t : elementwise_callable<logspace_sub_t, Options>
  {
    template<eve::floating_ordered_value T, floating_ordered_value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept { return EVE_DISPATCH_CALL(t, u); }

    template<eve::floating_ordered_value T0, floating_ordered_value T1, floating_ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tuple>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tuple>
    operator()(Tuple const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(logspace_sub_t, logspace_sub_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var logspace_sub
//!
//! @brief Callable object computing the logspace_sub operation:
//!        \f$\log\left(e^{x_0}-\sum_{i = 1}^n e^{x_i}\right)\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U, eve::floating_value ... Ts >
//!      auto logspace_sub(T arg0, U arg1, Ts ... args) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`arg0`, `arg1`, `args`, ...:   [values](@ref eve::value).
//!
//! **Return value**
//!
//! The call `logspace_sub(arg0, arg1, args...)` is semantically equivalent to
//!`log(exp(arg0) - exp(arg1) - exp(args)...)`.
//!
//! The result type is the [common value type](@ref common_value_t) of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/logspace_sub.cpp}
//!  @}
//================================================================================================
inline constexpr auto logspace_sub = functor<logspace_sub_t>;
}

#include <eve/module/math/regular/impl/logspace_sub.hpp>
