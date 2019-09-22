//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
// #include <eve/module/core/detail/generic/sin_kernel.hpp>
// #include <eve/module/core/detail/generic/cos_kernel.hpp>   
#include <eve/module/core/detail/scalar/cos_finalize.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/rem_pio2_medium.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, Vectorizable<T>)
  {
    return regular_(eve::cos)(a0); 
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T const &a0) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
      auto x2 = sqr(a0); 
      if (is_not_less_equal(x2, pi2_16)) return Nan<T>(); 
      return detail::cos_eval(x2);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                      , small_type const &       
                                      , T const &a0) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t =  detail::as_integer_t<T, signed>; 
      T x = eve::abs(a0);
      if (is_not_less_equal(x, Pio_2<T>())) return Nan<T>(); //Nan or Inf input
      i_t n = x > Pio_4<T>(); 
      if (n)
      {
        auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
        auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
        auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
        T xr = x-pio2_1;
        xr -= pio2_2;
        xr -= pio2_3;
        return bitwise_xor(detail::sin_eval(sqr(xr), xr), n << (sizeof(T)*8-1));
      }
      else
      {
        return detail::cos_eval(sqr(x));
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  
  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                      , cephes_type const &       
                                      , T const &a0) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
//      using i_t =  detail::as_integer_t<T, signed>; 
      if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
      const T x =  abs(a0);
      auto [fn, xr] = rem_pio2_cephes(x); 
      return detail::cos_finalize(fn, xr); 
//       i_t n = i_t(fn);
//       i_t swap_bit = n&i_t(1);
//       i_t sign_bit = shl(bitwise_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
//       T z = sqr(xr);
//       if (swap_bit)
//         z = sin_eval(z, xr);
//       else
//         z = cos_eval(z);
//       return bitwise_xor(z,sign_bit);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                     , medium_type const &       
                                     , T const &a0) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
//      using i_t =  detail::as_integer_t<T, signed>; 
      if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
      const T x =  abs(a0);
      auto [fn, xr] = rem_pio2_medium(x); 
      return detail::cos_finalize(fn, xr); 
//       i_t n = i_t(fn); //&i_t(3);
//       i_t swap_bit = n&i_t(1);
//       i_t sign_bit = shl(bitwise_xor(swap_bit, (n&i_t(2))>>1), sizeof(i_t)*8-1);
// //          std::cout << "n         " <<  n << std::endl;
// //          std::cout << "swap_bit  " <<  swap_bit << std::endl;
// //          std::cout << "sign_bit  " <<  sign_bit << std::endl;
// //          std::cout << "xr        " <<  xr       << std::endl;
//       T z = sqr(xr);
//       if (swap_bit)
//         z = sin_eval(z, xr);
//       else
//         z = cos_eval(z);
//       return bitwise_xor(z,sign_bit);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }  
  
//   template<typename T>
//   EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
//                                      , big_type const &       
//                                      , T const &a0) noexcept
//   requires(T, Vectorizable<T>)
//   {
//     if constexpr(std::is_floating_point_v<T>)
//     {
//       if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
//       const T x =  abs(a0);
//       auto [fn, xr] = rem_pio2(x); 
//       return detail::cos_finalize(fn, xr); 
//     }
//     else
//     {
//       static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
//     }   
//   }
}

#endif
