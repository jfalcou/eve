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
{
  template<typename Options>
  struct logspace_add_t : elementwise_callable<logspace_add_t, Options>
  {
    template<eve::floating_ordered_value T, floating_ordered_value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept { return EVE_DISPATCH_CALL(t, u); }

    template<eve::floating_ordered_value T0, floating_ordered_value T1, floating_ordered_value... Ts>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr auto operator()(Tup t) const noexcept { return EVE_DISPATCH_CALL(t); }


    EVE_CALLABLE_OBJECT(logspace_add_t, logspace_add_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var logspace_add
//!
//! @brief Callable object computing the logspace_add operation: \f$\log\left(\sum_{i = 0}^n
//! e^{x_i}\right)\f$
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
//!      auto logspace_add(T arg0, U arg1, Ts ... args) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`arg0`, `arg1`, `args`, ...:   [floating values](@ref eve::floating_value).
//!
//! **Return value**
//!
//! The call `logspace_add(arg0, arg1, args...)` is semantically equivalent to
//!`log(exp(arg0) + exp(arg1) + exp(args)...)`.
//!
//! The result type is the [common value type](@ref common_value_t) of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/logspace_add.cpp}
//!  @}
//================================================================================================
inline constexpr auto logspace_add = functor<logspace_add_t>;
}


#include <eve/module/math/regular/impl/logspace_add.hpp>
