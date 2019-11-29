//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_ARM_NEON_LOOKUP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/detail/function/simd/lookup.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T,N,neon64_> lookup_ ( EVE_SUPPORTS(neon128_),
                                              wide<T,N,neon64_> a, wide<I,N,neon64_> idx
                                            ) noexcept
  {
    if constexpr( std::is_signed_v<I> )
    {
      using utype = wide<make_integer_t<sizeof(I),unsigned>,N>;
      return lookup(a, bitwise_cast(idx,as<utype>()));
    }
    else
    {
      using t8_t = typename wide<T,N,neon64_>::template rebind<std::uint8_t, fixed<8>>;

      if constexpr(sizeof(I) == 1)
      {
        return bitwise_cast( t8_t(vtbl1_u8(bitwise_cast(a, as<t8_t>()),idx)), as(a));
      }
      else
      {
        t8_t  i1 = lookup(bitwise_cast(idx<<shift<I>, as(i1)), t8_t{repeater<I>});
              i1 = bitwise_cast(bitwise_cast(i1,as<wide<I,N,neon64_>>())+offset<I>,as<t8_t>());
        return bitwise_cast( lookup(bitwise_cast(a, as<t8_t>()),i1), as(a));
      }
    }
  }

  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T,N,neon128_> lookup_( EVE_SUPPORTS(neon128_),
                                              wide<T,N,neon128_> a, wide<I,N,neon128_> idx
                                            ) noexcept
  {
    if constexpr( std::is_signed_v<I> )
    {
      using utype = wide<make_integer_t<sizeof(I),unsigned>,N>;
      return lookup(a, bitwise_cast(idx,as<utype>()));
    }
    else
    {
      using t8_t  = typename wide<T,N,neon128_>::template rebind<std::uint8_t, fixed<16>>;

      if constexpr(sizeof(I) == 1)
      {
        using t8h_t = typename wide<T,N,neon128_>::template rebind<std::uint8_t, fixed<8>>;

        auto pieces     = bitwise_cast(a,as<t8_t>());
        uint8x8x2_t tbl = {{ pieces.slice(lower_), pieces.slice(upper_) }};
        auto idxs       = idx.slice();

        return bitwise_cast ( t8_t( t8h_t(vtbl2_u8(tbl, idxs[0] ))
                                  , t8h_t(vtbl2_u8(tbl, idxs[1]))
                                  )
                            , as(a)
                            );
      }
      else
      {
        t8_t  i1 = lookup(bitwise_cast(idx<<shift<I>, as(i1)), t8_t{repeater<I>});
              i1 = bitwise_cast(bitwise_cast(i1,as<wide<I,N,neon128_>>())+offset<I>,as<t8_t>());
        return bitwise_cast( lookup(bitwise_cast(a, as<t8_t>()),i1), as(a));
      }
    }
  }
}

#endif
