//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_NOT_EQUAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/forward.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                 wide<T, N, ABI> const &v0,
                                 wide<T, N, ABI> const &v1) noexcept
  {
    return logical_not(is_equal(v0, v1));
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                      wide<T, N, ABI> const &v0,
                                      U const & v1) noexcept requires(wide<T, N, ABI>,
                                                                      detail::Convertible<U, T>)
  {
    return eve::is_not_equal(v0, wide<T, N, ABI>(static_cast<T>(v1)));
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                      U const & v0,
                                      wide<T, N, ABI> const &v1) noexcept requires(wide<T, N, ABI>,
                                                                                   detail::Convertible<U, T>)
  {
    return eve::is_not_equal(wide<T, N, ABI>(static_cast<T>(v0)), v1);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                 wide<T, N, aggregated_> const &v0,
                                 wide<T, N, aggregated_> const &v1) noexcept
  {
    return aggregate(eve::is_not_equal, v0, v1);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Emulation 
  template<typename T, typename N>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                 wide<T, N, emulated_> const &v0,
                                 wide<T, N, emulated_> const &v1) noexcept
  {
    return map(eve::is_not_equal, v0, v1);
  }
  
  // -----------------------------------------------------------------------------------------------
  // logical 
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(simd_),
                                 wide<logical<T>, N, ABI> const &v0,
                                 wide<logical<T>, N, ABI> const &v1) noexcept
  {
      using t_t = wide<logical<T>, N, ABI>;
      using c_t = wide<T, N>;
      return bitwise_cast<t_t>((bitwise_xor(bitwise_cast<c_t>(v0),bitwise_cast<c_t>(v1))));
  }
}

namespace eve
{
  // -----------------------------------------------------------------------------------------------
  // operator !=  
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto eve::operator!=(  wide<T, N, ABI> const &v0,
                                         wide<T, N, ABI> const &v1) noexcept
  {
    return eve::is_not_equal(v0, v1); 
  }
}

#endif
