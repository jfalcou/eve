//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template< typename T, typename N, typename X1
          , typename U, typename M, typename X2
          >
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_),
                                 wide<T, N, X1> const &     v0,
                                 as_<wide<U, M, X2>> const &tgt) noexcept
  requires (!native<X1> || !native<X2>) && (sizeof(wide<T, N, X1>) == sizeof(wide<U, M, X2>))
//   Requires( wide<U, M, X2>
//           , either<!is_native<X1>::value,!is_native<X2>::value>
//           , if_<sizeof(wide<T, N, X1>) == sizeof(wide<U, M, X2>)>
//           )
  {
    wide<U, M, X2> that;

    constexpr auto sz = std::min(sizeof(v0), sizeof(that));

    void const *src = reinterpret_cast<detail::alias_t<void const> *>(&v0);
    void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
    std::memcpy(dst, src, sz);

    return that;
  }

  template< typename T, typename N, typename X1
          , typename U, typename M, typename X2
          >
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_),
                                     logical<wide<T, N, X1>> const &v0,
                                     as_<wide<U, M, X2>> const &    tgt) noexcept
  requires (!native<X1> || !native<X2>) && (sizeof(logical<wide<T, N, X1>>) == sizeof(wide<U, M, X2>))
//   Requires( wide<U, M, X2>
//           , either<!is_native<X1>::value,!is_native<X2>::value>
//           , if_<sizeof(logical<wide<T, N, X1>>) == sizeof(wide<U, M, X2>)>
//           )
  {
    wide<U, M, X2> that;

    constexpr auto sz = std::min(sizeof(v0), sizeof(that));

    void const *src = reinterpret_cast<detail::alias_t<void const> *>(&v0);
    void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
    std::memcpy(dst, src, sz);

    return that;
  }

  template< typename T, typename N, typename X1
          , typename U, typename M, typename X2
          >
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_),
                                     wide<T, N, X1> const &              v0,
                                     as_<logical<wide<U, M, X2>>> const &tgt) noexcept
  requires (!native<X1> || !native<X2>) && (sizeof(wide<T, N, X1>) == sizeof(logical<wide<U, M, X2>>))
  //   Requires( logical<wide<U, M, X2>>
  //           , either<!is_native<X1>::value,!is_native<X2>::value>
  //           , if_<sizeof(wide<T, N, X1>) == sizeof(logical<wide<U, M, X2>>)>
  //           )
  {
    logical<wide<U, M, X2>> that;
    
    constexpr auto sz = std::min(sizeof(v0), sizeof(that));
    
    void const *src = reinterpret_cast<detail::alias_t<void const> *>(&v0);
    void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
    std::memcpy(dst, src, sz);
    
    return that;
  }

  template< typename T, typename N, typename X1
            , typename U, typename M, typename X2
            >
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_),
                                 logical<wide<T, N, X1>> const &     v0,
                                 as_<logical<wide<U, M, X2>>> const &tgt) noexcept
  requires (!native<X1> || !native<X2>) && (sizeof(logical<wide<T, N, X1>>) == sizeof(logical<wide<U, M, X2>>))
//   Requires( logical<wide<U, M, X2>>
//           , either<!is_native<X1>::value,!is_native<X2>::value>
//           , if_<sizeof(logical<wide<T, N, X1>>) == sizeof(logical<wide<U, M, X2>>)>
//           )
  {
    logical<wide<U, M, X2>> that;

    constexpr auto sz = std::min(sizeof(v0), sizeof(that));

    void const *src = reinterpret_cast<detail::alias_t<void const> *>(&v0);
    void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
    std::memcpy(dst, src, sz);

    return that;
  }
}

#endif
