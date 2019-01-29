//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SELECT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_andnot.hpp>
#include <eve/function/bitwise_or.hpp>   
#include <eve/function/complement.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Native
  template<typename U, typename M, typename T, typename N, typename API>
  EVE_FORCEINLINE wide<T,N,API> bitwise_select_( EVE_SUPPORTS(simd_)
                                               , wide<U,M,API> const& v0
                                               , wide<T,N,API> const& v1
                                               , wide<T,N,API> const& v2
                                               ) noexcept
  {
    static_assert ( sizeof(wide<U,M,API>) == sizeof(wide<T,N,API>)
                  , "eve::bitwise_select - Arguments have incompatible size"
                  );
    return eve::bitwise_or(eve::bitwise_and(v1, v0), eve::bitwise_andnot(v2,v0));
  }
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE wide<T,N,aggregated_> bitwise_select_( EVE_SUPPORTS(simd_)
                                                    , wide<U,N,aggregated_> const& v0
                                                    , wide<T,N,aggregated_> const& v1
                                                    , wide<T,N,aggregated_> const& v1
                                                    ) noexcept
  {
    static_assert ( sizeof(U>) == sizeof(T)
                  , "eve::bitwise_select - Arguments have incompatible size"
                  );
    return aggregate( eve::bitwise_select, v0, v1, v2);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename U, typename T, typename N>
  EVE_FORCEINLINE  wide<T,N,emulated_> bitwise_select_ ( EVE_SUPPORTS(simd_)
                                                       , wide<U,N,emulated_> const& v0
                                                       , wide<T,N,emulated_> const& v1
                                                       , wide<T,N,emulated_> const& v2
                                                       ) noexcept
  {
    static_assert ( sizeof(U>) == sizeof(T)
                  , "eve::bitwise_select - Arguments have incompatible size"
                  );
    return map( eve::bitwise_select, v0, v1, v2);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N,emulated_> bitwise_select_ ( EVE_SUPPORTS(simd_)
                                                      , wide<T,N,emulated_> const& v0
                                                      , T const& v1
                                                        T const& v2
                                                      ) noexcept
                            requires(wide<T,N,emulated_>, Convertible<U,T>)
  {
    return map( eve::bitwise_select, v0, T(v1), T(v2));
  }

  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto bitwise_select_ ( EVE_SUPPORTS(simd_)
                                       , wide<T,N,ABI> const& v0
                                       , T const& v1
                                       , T const& v2  
                                    ) noexcept
                  requires(wide<T,N,ABI>, Convertible<U,T>)
  {
    return eve::bitwise_select( v0, wide<T,N,ABI>(v1), wide<T,N,ABI>(v2) );
  }


}


#endif
