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
#include <eve/module/special/regular/factorial.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/module/special/regular/log_gamma.hpp>

namespace eve
{
 template<typename Options>
  struct lfactorial_t : elementwise_callable<lfactorial_t, Options, raw_option, pedantic_option>
  {
    template<eve::integral_value T>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(lfactorial_t, lfactorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lfactorial
//!   @brief `elementwise_callable` object computing the natural logarithm of the factorial of unsigned integer values
//!   \f$\displaystyle \log n! = \sum_{i=1}^n \log i\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      template <value T> constexpr as_wide_as_t<double,T> lfactorial(T x) noexcept; // 1
//!
//!      // Semantic options
//!      template <value T> constexpr as_wide_as_t<double,T> lfactorial[raw](T x) noexcept; // 2
//!      template <value T> constexpr as_wide_as_t<double,T> lfactorial[pedantic](T x) noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto factorial[conditional_expr auto c](value auto n)     noexcept; // 4
//!      constexpr auto factorial[logical_value auto m](value auto n)        noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral or flint argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     1. The value of \f$ \log n!\f$ is returned with the following considerations:
//!        * If the entry is an integral value, the result
//!          element type is always double to try to avoid overflow as possible.
//!        * If the entry is a floating point value which must be a flint,
//!          the result is of the same type as the entry.
//!        * If `n` elements are nor integer nor flint the result is undefined.
//!     2  With the raw option the call never assert even for non flint or negative entries. The result is garbage for
//!        such values, but not undefined behaviour.
//!     3. With the pedantic option \f$\log(\Gamma(x+1))\f$ is returned. (more expansive using [log_gamma](@ref eve::log_gamma))
//!     4. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Erf](https://mathworld.wolfram.com/Factorial.html)
//!   *  [Wikipedia: Error Function](https://en.wikipedia.org/wiki/Factorial)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/lfactorial.cpp}
//================================================================================================
  inline constexpr auto lfactorial = functor<lfactorial_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE decltype(eve::factorial(T()))
      lfactorial_(EVE_REQUIRES(cpu_), O const&, T n) noexcept
    {
      if constexpr(!O::contains(raw) && !O::contains(pedantic))
      {
        EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
        EVE_ASSERT(eve::all(is_gez(n)), "lfactorial : some entry elements are not positive");
      }
      if constexpr(O::contains(pedantic))
      {
        using elt_t = element_type_t<T>;
        auto r = eve::log_gamma(eve::convert(n, as<double>()));
        if constexpr( std::same_as<elt_t, double> ) return r;
        else return convert(r, as<float>());
      }
      else
      {
        constexpr auto max = std::same_as<element_type_t<T>, double> ? 171 : 35;
        auto           r   = eve::log(factorial(n));

        if( eve::all(n < max) ) return r;
        else
        {
          auto np = [](auto x)
            {
              if constexpr(integral_value<T>) return convert(inc(x), as<double>());
              else                            return inc(x);
            }(n);

          return if_else(n < max, r, log_abs_gamma(np));
        }
      }
    }
  }
}
