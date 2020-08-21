//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/popcount.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_value T, typename N>
  EVE_FORCEINLINE size_t  nbtrue_(EVE_SUPPORTS(sse2_)
                            , logical<wide<T, N, sse_>> const &v) noexcept
  {
    static constexpr int Bytes = eve::sse_::bytes;

    if constexpr(std::is_same_v<T, float>)
    {
      using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;
      static constexpr int Card = Bytes/sizeof(T);
      static constexpr int SH = (Card-N::value);

      if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
      {
        using t_t  = wide<float, fixed<Card>, sse_>;
        static constexpr int sv = SH*sizeof(T);
        i8_t z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t>()), sv);

        return popcount(_mm_movemask_ps(bit_cast(z,as_<t_t>())));
      }
      else
      {
        return popcount(_mm_movemask_ps(v.mask()));
      }
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;
      static constexpr int Card = Bytes/sizeof(T);
      static constexpr int SH = (Card-N::value);

      if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
      {
        using t_t  = wide<double, fixed <Card>, sse_>;
        static constexpr int sv = SH*sizeof(T);
        i8_t z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t>()), sv);

        return popcount(_mm_movemask_pd(bit_cast(z,as_<t_t>())));
      }
      else
      {
        return popcount(_mm_movemask_pd(v.mask()));
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      [[maybe_unused]]  static constexpr int SH   = (Bytes-sizeof(T)*N::value);
      if constexpr(sizeof(T) == 1)
      {
        if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
        {
          static constexpr int sv = SH;
          auto z = _mm_bslli_si128(v.mask(), sv);

          return popcount(_mm_movemask_epi8(z));
        }
        else
        {
          return popcount(_mm_movemask_epi8(v.mask()));
        }
      }
      else
      {
        using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;
        if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
        {
          static constexpr int sv = SH;
          auto z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t >()), sv);
          return popcount(_mm_movemask_epi8(z))/sizeof(T);
        }
        else
        {
          return popcount(_mm_movemask_epi8(bit_cast(v.mask(), as_<i8_t >())))/sizeof(T);
        }
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_value T, typename N>
  EVE_FORCEINLINE size_t nbtrue_(EVE_SUPPORTS(avx_)
                           , logical<wide<T, N, avx_>> const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
      {
        return popcount(_mm256_movemask_ps(v.mask()));
      }
      else
      {
        return popcount(_mm256_movemask_pd(v.mask()));
      }
    }
    else
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)
        {
          return popcount(_mm256_movemask_epi8(v.mask()));
        }
        else
        {
          using i8_t = wide<int8_t, fixed<32> , avx_>;
          return popcount(_mm256_movemask_epi8(bit_cast(v.mask(), as_<i8_t >())))/sizeof(T);
        }
      }
      else
      {
        auto [sl, sh] = v.slice();
        return nbtrue(sl) + nbtrue(sh);
      }
    }
  }
}

