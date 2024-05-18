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
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>


namespace eve
{
template<typename Options>
struct fibonacci_t : strict_elementwise_callable<fibonacci_t, Options>
{
  template<eve::unsigned_value N, floating_value T0,  floating_value T1>
  requires (same_lanes_or_scalar<N, T0, T1>)
  constexpr EVE_FORCEINLINE as_wide_as_t<common_value_t<T0, T1>, N>
  operator()(N n, T0 t0, T1 t1) const noexcept
  { return EVE_DISPATCH_CALL(n, t0, t1); }

  EVE_CALLABLE_OBJECT(fibonacci_t, fibonacci_);
};

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var fibonacci
//!   @brief Computes the nth element of the Fibonacci sequence \f$(f_i)_{i\in \mathbb{N}}\f$.
//!
//!   The sequence is defined by the recurrence relations :
//!
//!     * \f$f_0 = x\f$
//!     * \f$f_1 = y\f$
//!     * \f$f_{n+2} = f_{n+1} + f_{n},  n > 0\f$
//!
//!   but is computed using the
//!   [Binet formula](https://mathworld.wolfram.com/BinetsFibonacciNumberFormula.html).
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value N, eve::floating_value T, eve::floating_value U>
//!      constexpr eve::common_value_t<T, U> fibonacci(N n, T x, U y) noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `n`: [index](@ref eve::unsigned_value) of the value to be returned
//!
//!   `x`, `y`: [floating point arguments](@ref eve::floating_value) : \f$f_0\f$ and \f$f_1\f$.
//!
//!    **Return value**
//!
//!    The value of the  nth element of the Fibonacci sequence beginning by `x` and `y` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/combinatorial/regular/fibonacci.cpp}
//! @}
//================================================================================================
inline constexpr auto fibonacci = functor<fibonacci_t>;

  namespace detail
  {
    template<typename N, typename T, typename U, callable_options O>
    constexpr EVE_FORCEINLINE as_wide_as_t<common_value_t<T, U>, N>
    fibonacci_(EVE_REQUIRES(cpu_), O const&, N n, T a, U b)
    {
      using c_t    = as_wide_as_t<common_value_t<T, U>, N>;
      using elt_t  = element_type_t<c_t>;
      using eli_t  = as_integer_t<elt_t, unsigned>;
      auto gold    = c_t(1.61803398874989484820458683436563811772030917980575);
      auto goldbar = c_t(-0.61803398874989484820458683436563811772030917980575);
      constexpr elt_t oneosqrt5 = 0.4472135954999579392818347337462552470881236719223;

      if constexpr(std::same_as<T, U>)
      {
        auto nm1 = convert(n, uint_from<eli_t>());
        auto c2  = fms(gold, a, b) * oneosqrt5;
        auto c1  = a - c2;
        auto f   = fma(c1, eve::pow(gold, nm1), c2 * eve::pow(goldbar, nm1));
        return  nearest[is_flint(a) && is_flint(b)](f);
      }
      else return fibonacci(n,c_t(a), c_t(b));
    }
  }
}
