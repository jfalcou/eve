//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/shr.hpp>
#include <eve/forward.hpp>
#include <type_traits>


// -------------------------------------------------------------------------------------------------
// Basic
namespace eve::detail
{
  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto bitwise_shr_(EVE_SUPPORTS(simd_)
                                   , wide<T, N, ABI> const &v0
                                   , wide<U, N, ABI> const &v1) noexcept
  {
    using t_t =  wide<T, N, ABI>; 
    using u_t =  wide<eve::detail::as_integer_t<T, unsigned>, N, ABI>; 
    return bitwise_cast<t_t>(eve::shr(bitwise_cast<u_t>(v0), v1));
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_shr_(EVE_SUPPORTS(simd_),
                                    wide<T, N, ABI> const &v0,
                                    U const &              v1) noexcept requires(wide<T, N, ABI>,
                                                                                 detail::Convertible<U, T>)
  {
    using t_t =  wide<T, N, ABI>; 
    using u_t =  wide<eve::detail::as_integer_t<T, unsigned>, N, ABI>; 
    return bitwise_cast<t_t>(eve::shr(bitwise_cast<u_t>(v0), v1));
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto bitwise_shr_(EVE_SUPPORTS(simd_)
                                   , U const &v0
                                   , wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                                  detail::Convertible<U, T>)
  {
    using t_t =  wide<T, N, ABI>; 
    using u_t =  wide<eve::detail::as_integer_t<T, unsigned>, N, ABI>; 
    return bitwise_cast<t_t>(eve::shr(u_t(v0), v1));
  }
}


#endif
