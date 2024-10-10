//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct expx2_t : elementwise_callable<expx2_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(expx2_t, expx2_);
  };

  //================================================================================================
  //! @addtogroup math_exp
  //! @{
  //! @var expx2
  //! @brief Callable object computing \f$e^{x^2}\f$.
  //!
  //!   @groupheader{Header file}
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
  //!      // Regular overload
  //!      constexpr auto expx2(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto expx2[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto expx2[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!  **Parameters**
  //!
  //!     * `x`: [floating value](@ref floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!  **Return value**
  //!
  //!     1. Returns the [elementwise](@ref glossary_elementwise) exponential of the square of `x`
  //!        trying to avoid overflow as possible.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/expx2.cpp}
  //================================================================================================
  inline constexpr auto expx2 = functor<expx2_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    expx2_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        if constexpr( eve::platform::supports_invalids && scalar_value<T> )
        {
          if( is_nan(a0) ) return a0;
        }
        if constexpr( scalar_value<T> && eve::platform::supports_infinites )
          if( is_infinite(a0) ) return inf(as<T>{});
        T       x       = eve::abs(a0);
        using u_t = underlying_type_t<T>;
        const u_t Expx2c1 = ieee_constant<0x1.0p+5f, 0x1.0000000000000p+7>(as<u_t>{});
        const u_t Expx2c2 = ieee_constant<0x1.0p-5f, 0x1.0000000000000p-7>(as<u_t>{});
        /* Represent x as an exact multiple of 1/32 plus a residual.  */
        T m = Expx2c1 * eve::floor(fma(Expx2c2, x, half(as<T>{})));
        x -= m;
        /* x**2 = m**2 + 2mf + f**2 */
        T u  = sqr(m);
        T u1 = fma(T(2) * m, x, sqr(x));
        /* u is exact, u1 is small.  */
        auto gtmxlg = is_not_less_equal(u + u1, maxlog(as<T>{}));
        if constexpr( scalar_value<T> )
        {
          if( gtmxlg ) return inf(as<T>{});
          return eve::exp(u) * eve::exp(u1);
        }
        else if constexpr( simd_value<T> )
        {
          T r = eve::if_else(gtmxlg, eve::inf(as<T>{}), eve::exp(u) * eve::exp(u1));
          if constexpr( eve::platform::supports_infinites ) r = eve::if_else((x == inf(as<T>{})), x, r);
          if constexpr( eve::platform::supports_invalids )
            r = eve::if_else(is_nan(a0), eve::allbits, r);
          return r;
        }
        return u + u1;
      }
      else return apply_over(expx2, a0);
    }
  }
}
