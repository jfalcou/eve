//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/traits/common_value.hpp>


namespace eve
{
  template<typename Options>
  struct logspace_add_t : tuple_callable<logspace_add_t, Options>
  {
    template<eve::floating_ordered_value T, floating_ordered_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T t, U u) const noexcept { return EVE_DISPATCH_CALL(t, u); }

    template<eve::floating_ordered_value T0, floating_ordered_value T1, floating_ordered_value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tuple>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<eve::common_value,Tuple>
    operator()(Tuple const& t) const noexcept { return EVE_DISPATCH_CALL(t); }


    EVE_CALLABLE_OBJECT(logspace_add_t, logspace_add_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var logspace_add
//!
//! @brief Callable object computing the logspace_add operation: \f$\log\left(\sum_{i = 0}^n
//! e^{\log x_i}\right)\f$
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
//!`log(exp(log(arg0)) + exp(log(arg1)) + exp(log(args))...)`.
//!
//! The result type is the [common value type](@ref common_value_t) of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/logspace_add.cpp}
//!  @}
//================================================================================================
  inline constexpr auto logspace_add = functor<logspace_add_t>;

  namespace detail
  {
    template<typename T0, typename T1, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
    logspace_add_(EVE_REQUIRES(cpu_), O const &, T0 a0, T1 a1, Ts... args) noexcept
    {
      using r_t = common_value_t<T0, T1, Ts...>;
      if constexpr(sizeof...(Ts) == 0)
      {
        if constexpr( has_native_abi_v<T0> )
        {
          auto r0 = r_t(a0);
          auto r1 = r_t(a1);
          auto tmp = -eve::abs(r0 - r1);
          auto r   = eve::max(r0, r1) + eve::log1p(eve::exp(tmp));
          if constexpr( eve::platform::supports_invalids ) r = if_else(is_nan(tmp), r0 + r1, r);
          return r;
        }
        else return arithmetic_call(logspace_add, r_t(a0), r_t(a1));
      }
      else
      {
        r_t  that(logspace_add(a0, a1));
        auto ladd = [](auto that, auto next) -> r_t
          {
            that = logspace_add(that, next);
            return that;
          };
        ((that = ladd(that, args)), ...);
        return that;
      }
    }
  }
}
