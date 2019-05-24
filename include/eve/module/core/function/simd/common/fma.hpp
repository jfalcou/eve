//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/add.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto fma_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const & c) noexcept
                  requires( std::conditional_t< !is_vectorized_v<T>
                                              , std::conditional_t<is_vectorized_v<U>,U,V>
                                              , T
                                              >,
                            detail::Either< is_vectorized_v<T>,
                                            is_vectorized_v<U>,
                                            is_vectorized_v<V>
                                          >
                          )
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;

    if      constexpr(  vT && !vU && !vV ) return fma(  a , T{b}, T{c});
    else if constexpr(  vT &&  vU && !vV ) return fma(  a ,   b , T{c});
    else if constexpr(  vT && !vU &&  vV ) return fma(  a , T{b},   c );
    else if constexpr( !vT &&  vU && !vV ) return fma(U{a},   b , U{c});
    else if constexpr( !vT &&  vU &&  vV ) return fma(U{a},   b ,   c );
    else if constexpr( !vT && !vU &&  vV ) return fma(V{a}, V{b},   c );
    else
    {
      if constexpr(std::is_same_v<T,U> && std::is_same_v<T,V>)
      {
        using abi_t = typename T::abi_type;
        if      constexpr( is_aggregated_v<abi_t> ) return aggregate( eve::fma, a, b, c);
        else if constexpr( is_emulated_v<abi_t>   ) return map( eve::fma, a, b, c);
        else                                        return a * b + c;
      }
      else
      {
        static_assert ( std::is_same_v<T,U> && std::is_same_v<T,V>,
                        "[eve::fma] - Incompatible types."
                      );
        return {};
      }
    }
  }
}

#endif
