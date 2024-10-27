//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{

  template<typename Options>
  struct cbrt_t : elementwise_callable<cbrt_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cbrt_t, cbrt_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//!   @var cbrt
//!   @brief `elementwise_callable` object computing the cubic root.
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
//!      constexpr auto cbrt(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cbrt[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cbrt[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`:  [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!   1. Returns an [elementwise](@ref glossary_elementwise) cubic root value of the input.
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/cbrt)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Cube_root)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/CubeRoot.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cbrt.cpp}
//================================================================================================
  inline constexpr auto cbrt = functor<cbrt_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<eve::floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cbrt_(EVE_REQUIRES(cpu_), O const & , T x) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        using vt_t = element_type_t<T>;
        auto test0 = is_eqz(x) || is_not_finite(x);
        if constexpr( eve::scalar_value<T> )
          if( test0 ) return x;
        constexpr vt_t factor[5] = {0.6299605249474365823836,
                                    0.793700525984099737376,
                                    1.0,
                                    1.2599210498948731647672,
                                    1.587401051968199474751};
        auto           ax        = eve::abs(x);
        auto           test      = is_less(eve::abs(x), T(100) * smallestposval(eve::as<T>()));
        ax                       = ldexp[test](ax, 54);
        /* Reduce x.  xm now is an range  [0.5, 1.0].  */
        auto [xm, xe] = ifrexp[raw](ax);
        T u;
        if constexpr( std::is_same_v<vt_t, double> )
          u = eve::reverse_horner(xm, T(0x1.6b69cba168ff2p-2), T(0x1.8218dde9028b4p+0), T(-0x1.0eb8277cd8d5dp+1)
                                 , T(0x1.39350adad51ecp+1), T(-0x1.d5ae6cfa20f0cp+0)
                                 , T(0x1.91e2a6fe7e984p-1), T(-0x1.29801e893366dp-3));
        else if constexpr( std::is_same_v<vt_t, float> )
          u = eve::reverse_horner(xm, T(0x1.f87bc4p-2f), T(0x1.6527f4p-1f), T(-0x1.88324ap-3f));
        auto t2 = sqr(u) * u;
        u *= fma(xm, T(2), t2) / fma(T(2), t2, xm);

        if constexpr( eve::scalar_value<T> ) u *= factor[2 + xe % 3];
        else                            u *= gather(&factor[0], 2 + xe - (xe / 3) * 3);
        u = minus[is_ltz(x)](u);
        if constexpr( eve::scalar_value<T> ) xe = add[test](int(xe) / 3, -18);
        else                            xe = add[test](xe / 3, -18);
        auto z = ldexp(u, xe);
        if constexpr( eve::scalar_value<T> ) return z;
        else                            return if_else(test0, x, z);
      }
      else return apply_over(cbrt, x);
    }
  }
}
