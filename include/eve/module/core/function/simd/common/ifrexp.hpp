//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Jean-Thierry LAPRESTE
   Copyright 2019 Joel FALCOU
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IFREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IFREXP_HPP_INCLUDED


#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/tags.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shr.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_andnot.hpp>   
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/logical_notand.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/maxexponent.hpp> 
#include <eve/constant/maxexponentm1.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/twotonmb.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/raw.hpp>
#include <eve/detail/meta.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Raw case
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , wide<T, N, ABI> const & a0) noexcept
  requires( std::tuple<wide<T, N, ABI>, as_integer_t<wide<T, N, ABI>, signed>>, floating_point<T>) 
  {
    using t_t = wide<T, N, ABI>; 
    using i_t = as_integer_t<t_t, signed>; 
    auto r1   = bitwise_and(Expobits_mask<t_t>(), a0);
    auto x    = bitwise_notand(Expobits_mask<t_t>(), a0);
    return  std::tuple<t_t, i_t>{ bitwise_or(Half<t_t>(), x), bitwise_shr(r1,Nbmantissabits<t_t>()) - Maxexponentm1<t_t>()};
  }
  
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , wide<T, N, ABI>  a0) noexcept
  requires( std::tuple<wide<T, N, ABI>, as_integer_t<wide<T, N, ABI>, signed>>, floating_point<T>) 
  {
    using t_t = wide<T, N, ABI>; 
    using i_t = as_integer_t<t_t, signed>; 
    auto [m, e] =  raw_(ifrexp)(a0);
    auto test = is_nez(a0);
    return std::tuple<t_t, i_t>{if_else(test, m, eve::zero_), if_else(test, e, eve::zero_)}; 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic case
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                    , pedantic_type const & 
                                    , wide<T, N, ABI> const & a0) noexcept
  requires( std::tuple<wide<T, N, ABI>, as_integer_t<wide<T, N, ABI>, signed>>, floating_point<T>) 
  {
     using t_t = wide<T, N, ABI>; 
     using i_t = as_integer_t<t_t, signed>;
     t_t aa0 = a0;
     i_t t(0); 
     if constexpr(eve::platform::supports_denormals)
     {
       auto test = is_denormal(a0);
       t = if_else(test,Nbmantissabits<t_t>(), eve::zero_);
       aa0 = if_else(test, Twotonmb<T>()*a0, a0);
     }
     auto r1 = bitwise_and(Expobits_mask<t_t>(), aa0); //extract exp.
     auto x  = bitwise_notand(Expobits_mask<t_t>(), aa0);
     r1 = bitwise_shr(r1,Nbmantissabits<T>()) - Maxexponentm1<T>();
     auto r0 = bitwise_or(Half<t_t>(), x);
     auto test0 = is_nez(aa0);
     auto test1 = is_greater(r1,Limitexponent<t_t>());
     r1 = if_else(logical_notand(test1, test0), r1, eve::zero_);

     if constexpr(eve::platform::supports_denormals)
     {
       r1 -= t ;
     }
     return std::tuple<t_t, i_t>{ if_else(test0, add[test1](r0,aa0), eve::zero_), r1};
  }
}

#endif
