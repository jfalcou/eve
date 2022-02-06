//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/detail/erf_kernel.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T>
  EVE_FORCEINLINE T erf_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr(eve::platform::supports_invalids)
      if(is_nan(a0)) return a0;
    if constexpr(eve::platform::supports_infinites)
      if (eve::is_infinite(a0)) return signnz(a0);
    if constexpr(std::is_same_v<T, double>)
    {
      T y =  eve::abs(a0);
      if (y <= 0.46875) // 15/32
      {
        T ysq = if_else(y > halfeps(as<T>()), sqr(y), eve::zero);
        return kernel1_erf1(a0, ysq);
      }
      else
      {
        if (a0 > 26.543) return sign(a0);
        else if (y <= 4)
        {
          T res = kernel1_erf2(a0, y);
          res =   kernel1_finalize2(res, y);
          res = (half(as<T>()) - res) + half(as<T>());
          if (is_ltz(a0)) res = -res;
          return res;
        }
        else //if  (y <= 26.543)
        {
          T res = kernel1_erf3(a0, y);
          res =   kernel1_finalize2(res, y);
          res = (half(as<T>()) - res) + half(as<T>());
          if (is_ltz(a0)) res = -res;
          return res;
        }
      }
    }
    else  if constexpr(std::is_same_v<T, float>)
    {
      T x =  eve::abs(a0);
      if (x < 6.6666667e-01f)//2/3
      {
        return a0*kernel_erf1(sqr(x));
      }
      else
      {
        T z = x/inc(x)-0.4f; //Ratio<T, 2, 5>();
        T r2 =   oneminus(exp(-sqr(x))*kernel_erfc2(z));
        if (is_ltz(a0)) r2 = -r2;
        return r2;
      }
    }
  }

  template<floating_real_simd_value T>
  EVE_FORCEINLINE T erf_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::is_same_v<elt_t, double>)
      {
        T y =  eve::abs(a0);
        y =  if_else(y > T(26.543), T(26.543), y);
        T sqry =  eve::sqr(y);
        auto test1 = eve::is_less(y, T( 0.46875)); // 15/32;
        T r1 = eve::zero(as<T>());
      auto nb = eve::count_true(test1);
        if(nb > 0)  //here y < 0.46875
        {
          T ysq = if_else(y > halfeps(as<T>()), sqry, eve::zero);
          r1 = kernel1_erf1(a0, ysq);
          if (nb == T::size()) return r1;
        }
        auto test2 = (y <= T(4));
        auto test3 = logical_andnot(test2, test1);

        auto nb1 =  eve::count_true(test3);
        if(nb1 > 0) //here we treat 0.46875 <= y and y <= 4
        {
          T res = kernel1_erf2(a0, y);
          res =   kernel1_finalize2(res, y);
          res = (half(as<T>()) - res) + half(as<T>());
          res = minus[is_ltz(a0)](res);
          r1 = if_else(test3, res, r1);
          if (nb+nb1 == T::size()) return r1;
        }
        //here we treat y > 4
        T res = kernel1_erf3(a0, y);
        res =   kernel1_finalize2(res, y);
        res = (half(as<T>()) - res) + half(as<T>());
        res = minus[is_ltz(a0)](res);
        r1 = if_else(test2, r1, res);
        return r1;
      }
      else  if constexpr(std::is_same_v<elt_t, float>)
      {
        T x =  eve::abs(a0);
        T r1 = eve::zero(as<T>());
        auto test1 = eve::is_less(x, 6.6666667e-01f); //Ratio<T, 2, 3>());
        auto nb = eve::count_true(test1);
        if(nb > 0)
        {
          r1 =  a0*kernel_erf1(sqr(x));
          if(nb >= T::size())
            return r1;
        }
        T z = x/inc(x);
        z-= T(0.4);
        T r2 =   oneminus(exp(-sqr(x))*kernel_erfc2(z));
        r2 = minus[is_ltz(a0)](r2);
        r1 = if_else(test1, r1, r2);
        if constexpr(eve::platform::supports_infinites)
          r1 = eve::if_else(eve::is_infinite(a0), eve::sign(a0), r1);
        return r1;
      }
    }
    else
      return apply_over(erf, a0);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto erf_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::erf, t);
  }
}
