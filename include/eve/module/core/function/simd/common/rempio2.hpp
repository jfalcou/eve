//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REMPIO2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REMPIO2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/combine.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/module/core/detail/simd/rempio2_kernel.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template <typename D, typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto  rempio2_(EVE_SUPPORTS(cpu_)
                                , D const & 
                                , wide < T, N, ABI> const &xx) noexcept
  {
    /* Reduce range of x to within PI/2 with abs (x) <  255*pi/4. */
//    using t_t = wide < float, N, ABI>; 
    if constexpr(is_emulated_v<ABI>)
    {
      return map(D()(rempio2), xx);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      auto  [lo, hi] = xx.slice();
      auto  [nhi, xhi, dxhi]   = D()(rempio2)(hi);
      auto  [nlo, xlo, dxlo]   = D()(rempio2)(lo);
      return std::make_tuple(eve::combine( nlo, nhi)
                            , eve::combine( xlo, xhi)
                            , eve::combine( dxlo, dxhi));
    }
    else if constexpr(std::is_same_v<D, small_type>)
    {
      return rempio2_small(xx); 
    }
    else if constexpr(std::is_same_v<D, medium_type>)
    {
      return rempio2_medium(xx); 
    }
    else if constexpr(std::is_same_v<D, big_type>)
    {
      return rempio2_big(xx); 
    }
    else if constexpr(std::is_same_v<D, regular_type>)
    {
      return rempio2(xx); 
    }
  }
  
  template < typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto  rempio2_(EVE_SUPPORTS(cpu_)
                                , wide<T, N, ABI> const &x) noexcept
  requires(std::tuple<wide<T, N, ABI>, wide<T, N, ABI>, wide<T, N, ABI>>, vectorizable<T>)
  {
//    EVE_ASSERT(all(is_nltz(x)), "attempted rempio2 with negative argument"); 
    using t_t = wide < T, N, ABI>; 
    if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::rempio2, x);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      auto  [lo, hi] = x.slice();
      auto  [nhi, xhi, dxhi] = rempio2(hi);
      auto  [nlo, xlo, dxlo] = rempio2(lo);
      return std::make_tuple( eve::combine( nlo, nhi)
                                      , eve::combine( xlo, xhi)
                                      , eve::combine( dxlo, dxhi));
    }
    else
    {    
      if (all(x <= Rempio2_limits(restricted_type(), T())))  return  std::make_tuple(t_t(0), x, t_t(0)); 
      else if (all(x <= Rempio2_limits(small_type(), T())))  return small_(rempio2)(x); 
      else if (all(x <= Rempio2_limits(medium_type(), T()))) return medium_(rempio2)(x); 
      else return big_(rempio2)(x); 
    }
  }
}


#endif
 
