//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <eve/as_arithmetic.hpp>
#include <type_traits>

// #include <eve/function/bitwise_and.hpp>
// #include <eve/function/bitwise_or.hpp>
// #include <eve/function/bitwise_andnot.hpp>
// #include <eve/function/bitwise_ornot.hpp>
// #include <eve/constant/zero.hpp>
// #include <eve/constant/allbits.hpp>
// #include <eve/constant/nan.hpp>

namespace eve::detail
{
  
  //-----------------------------------------------------------------------------------------------
  // Basic
  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                , wide<logical<U>, N, ABI> const& v0
                                , wide<T, N, ABI> const& v1
                                , wide<T, N, ABI> const& v2
                                ) noexcept
  {
    return bitwise_select( bitwise_mask(v0), v1, v2); 
  }
  
  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                , wide<logical<U>, N, ABI> const& v0
                                , wide<logical<T>, N, ABI> const& v1
                                , wide<logical<T>, N, ABI> const& v2
                                ) noexcept
  {
    using t_t =  wide<logical<T>, N, ABI>; 
    return bitwise_cast<t_t>(bitwise_select( bitwise_mask(v0), bitwise_mask(v1), bitwise_mask(v2))); 
  }

  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                , wide<U, N, ABI> const& v0
                                , wide<T, N, ABI> const& v1
                                , wide<T, N, ABI> const& v2
                                ) noexcept
  {
    return if_else(is_nez(v0), v1, v2); 
  }

  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                , wide<U, N, ABI> const& v0
                                , wide<logical<T>, N, ABI> const& v1
                                , wide<logical<T>, N, ABI> const& v2
                                ) noexcept
  {
    return if_else(is_nez(v0), v1, v2); 
  }

  //-----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                                        , wide<U,N,aggregated_> const& v0
                                                        , wide<T,N,aggregated_> const& v1
                                                        , wide<T,N,aggregated_> const& v2
                                                 ) noexcept requires(wide<T,N>, Arithmetic<U>, Arithmetic<T>)
  {
    return aggregate( eve::if_else, v0, v1, v2);
  }

  template<typename U, typename T, typename N>
  EVE_FORCEINLINE auto if_else_ ( EVE_SUPPORTS(simd_)
                                                        , wide<logical<U>,N,aggregated_> const& v0
                                                        , wide<T,N,aggregated_> const& v1
                                                        , wide<T,N,aggregated_> const& v2
                                                        ) noexcept requires(wide<T,N>, Arithmetic<U>, Arithmetic<T>)
  {
    return aggregate( eve::if_else, v0, v1, v2);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE  wide<T,N,emulated_> if_else_ ( EVE_SUPPORTS(simd_)
                                                       , wide<U,N,emulated_> const& v0
                                                       , wide<T,N,emulated_> const& v1
                                                       , wide<T,N,emulated_> const& v2
                                                       ) noexcept
  {
    return map( eve::if_else, v0, v1, v2);
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , T const &v1
          , T const &v2) noexcept
  {
    return eve::if_else(v0, wide<T, N>(v1), wide<T, N>(v2));
  }

  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , wide<U, N, ABI> const &v1
          , U const &v2) noexcept
  {
    return eve::if_else(v0, v1, wide<U, N>(v2));
  }

  template<typename T, typename U, typename N, typename ABI>
  EVE_FORCEINLINE auto
  if_else_(EVE_SUPPORTS(simd_)
          , wide<T, N, ABI> const &v0
          , U const &v1
          , wide<U, N, ABI> const &v2) noexcept
  {
    return eve::if_else(v0, wide<U, N>(v1), v2);
  }
  
//   // -----------------------------------------------------------------------------------------------
//   // Support for specialization with zero and allbits

//   // if zero else
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , callable_object<eve::tag::zero_>
//           , wide<U, N, ABI> const &v2) noexcept
//   {
//     return bitwise_andnot(v2, bitwise_mask(v0));
//   }

//   // if else zero 
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , wide<U, N, ABI> const &v1
//           , callable_object<eve::tag::zero_>) noexcept
//   {
//     return bitwise_and(v1, bitwise_mask(v0));
//   }

//   // if allbits else
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , callable_object<eve::tag::allbits_>
//           , wide<U, N, ABI> const &v2) noexcept
//   {
//     return bitwise_ornot(v2, bitwise_mask(v0));
//   }

//   // if else allbits 
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , wide<U, N, ABI> const &v1
//           , callable_object<eve::tag::allbits_>) noexcept
//   {
//     return bitwise_or(v1, bitwise_mask(v0));
//   }

//    // if nan else
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , callable_object<eve::tag::nan_>
//           , wide<U, N, ABI> const &v2) noexcept requires(wide<U, N, ABI>, Floating<U>)
//   {
//     return bitwise_ornot(v2, bitwise_mask(v0));
//   }

//   // if else nan 
//   template<typename T, typename U, typename N, typename ABI>
//   EVE_FORCEINLINE auto
//   if_else_(EVE_SUPPORTS(simd_)
//           , wide<T, N, ABI> const &v0
//           , wide<U, N, ABI> const &v1
//           , callable_object<eve::tag::nan_>) noexcept requires(wide<U, N, ABI>, Floating<U>)
//   {
//     return bitwise_or(v1, bitwise_mask(v0));
//   }
 
}

#endif
