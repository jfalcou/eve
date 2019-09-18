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
#include <eve/module/core/detail/scalar/sin_kernel.hpp>
#include <eve/module/core/detail/scalar/cos_kernel.hpp>   
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_4.hpp>
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
      auto pi2_16 = static_cast<T>(0.61685027506808491367715568749226); 
      auto x2 = sqr(a0); 
//      EVE_ASSERT(!test, "Restricted cos called with arg magnitude greater than Pi/4"); 
      if (is_not_less_equal(x2, pi2_16)) return Nan<T>(); 
      return detail::cos_eval(x2);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto cos_(EVE_SUPPORTS(cpu_)
                                      , TAG const &       
                                      , T const &a0) noexcept
  {
    static_assert(std::is_floating_point_v<T>, "still not implemented");
    return T{}; 
    
// //        using redu_t = trig_reduction<A0,unit_tag,tag::not_simd_type, mode>;
// //        using eval_t = trig_evaluation<A0,tag::not_simd_type>;
// //        using i_t    = bd::as_integer_t<A0, signed>;           // signed integer type associated to A0
// //        using style_t = typename mode::type;
//     if constexpr(std::is_floating_point_v<T>)
//     {
//       using i_t = detail::as_integer_t<A0, signed>;
//       if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
//       const T x = eve::abs(a0);
//       T xr = Nan<T>();
//       i_t n = static_cast<i_t>(detail::reduce(radian_type{}, TAG{}, x, xr));
//       i_t swap_bit = n&One<i_t>();
//       i_t sign_bit = shl(bitwise_xor(swap_bit, (n&Two<i_t>())>>1), sizeof(i_t)*8-1);
//       T z = sqr(xr);
//       if (swap_bit)
//         z = sin_eval(z, xr);
//       else
//         z = cos_eval(z);
//       return bitwise_xor(z,sign_bit); 
//     }
//     else
//     {
//    static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
//     }   
  }
}

#endif
