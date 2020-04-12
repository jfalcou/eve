//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/arch/limits.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE bool  all_(EVE_SUPPORTS(sse2_)
                            , logical<wide<T, N, sse_>> const &v) noexcept
  {
    static constexpr int Bytes = limits<eve::sse2_>::bytes;

    if constexpr(std::is_same_v<T, float>)
    {
      using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;

      static constexpr int Card = Bytes/sizeof(T);
      static constexpr int SH = (Card-N::value);
      static constexpr int mask = 0xF >> SH;

      if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
      {
        using t_t  = wide<float, fixed<Card>, sse_>;
        static constexpr int sv = SH*sizeof(T);
        static constexpr int smask = mask << SH;
        i8_t z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t>()), sv);

        return _mm_movemask_ps(bit_cast(z,as_<t_t>())) == smask;
      }
      else
      {
        return _mm_movemask_ps(v.mask()) == mask;
      }
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;

      static constexpr int Card = Bytes/sizeof(T);
      static constexpr int SH = (Card-N::value);
      static constexpr int mask = 0x3 >> SH;

      if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
      {
        using t_t  = wide<double, fixed <Card>, sse_>;
        static constexpr int sv = SH*sizeof(T);
        static constexpr int smask = mask << SH;
        i8_t z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t>()), sv);

        return _mm_movemask_pd(bit_cast(z,as_<t_t>())) == smask;
      }
      else
      {
        return _mm_movemask_pd(v.mask()) == mask;
      }
    }
    else if constexpr(integral_value<T>)
    {
      static constexpr int SH   = (Bytes-sizeof(T)*N::value);
      static constexpr int mask = 0xFFFF >> SH;

      if constexpr(sizeof(T) == 1)
      {
        if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
        {
          static constexpr int smask = mask <<  SH;
          static constexpr int sv = SH;
          auto z = _mm_bslli_si128(v.mask(), sv);

          return _mm_movemask_epi8(z) == smask;
        }
        else
        {
          return _mm_movemask_epi8(v.mask()) == mask;
        }
      }
      else
      {
        using i8_t = typename wide<T, N, sse_>::template rebind<int8_t, fixed<Bytes>>;

        if constexpr(N::value*sizeof(T) != Bytes) // "small" wide types
        {
          static constexpr int smask = mask <<  SH;
          static constexpr int sv = SH;
          auto z = _mm_bslli_si128(bit_cast(v.mask(), as_<i8_t >()), sv);
          return _mm_movemask_epi8(z) == smask;
        }
        else
        {
          return _mm_movemask_epi8(bit_cast(v.mask(), as_<i8_t >())) == mask;
        }
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(avx_)
                           , logical<wide<T, N, avx_>> const &v) noexcept
  {
    if constexpr(floating_value<T>)
    {
      if constexpr(std::is_same_v<T, float>)
      {
        return _mm256_movemask_ps(v.mask()) == int(0xFF);
      }
      else
      {
        return _mm256_movemask_pd(v.mask()) ==int( 0xF);
      }
    }
    else
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)
        {
          return _mm256_movemask_epi8(v.mask()) == int(0xFFFFFFFF);
        }
        else
        {
          using i8_t = typename wide<T, N, avx_>::template rebind<int8_t, fixed<32>>;

          return _mm256_movemask_epi8(bit_cast(v.mask(), as_<i8_t >())) == int(0xFFFFFFFF);
        }
      }
      else
      {
        auto [sl, sh] = v.slice();
        return all(sl) && all(sh);
      }
    }
  }
}

#endif
