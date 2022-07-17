//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/spy.hpp>
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/as.hpp>

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace eve::detail
{
  //================================================================================================
  // enumerated make - 128bits
  //================================================================================================
  template<real_scalar_value T, typename S, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T,S>> const &, Vs... vs) noexcept
    requires std::same_as<abi_t<T, S>, x86_128_>
  {
    static_assert ( sizeof...(Vs) <= S::value
                  , "[eve::make] - Invalid number of arguments"
                  );

    constexpr auto c = categorize<wide<T,S>>();

          if constexpr( c == category::float64x2) return _mm_setr_pd(static_cast<T>(vs)...);
    else  if constexpr( c == category::float32x4)
    {
      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        return _mm_setr_ps(vs..., (N ? 0:0)...);
      }(std::make_index_sequence<4 - sizeof...(vs)>());
    }
    else  if constexpr( match(c,category::int8x16, category::uint8x16) )
    {
      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        return _mm_setr_epi8(vs..., (N ? 0:0)...);
      }(std::make_index_sequence<16 - sizeof...(vs)>());
    }
    else  if constexpr( match(c,category::int16x8, category::uint16x8) )
    {
      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        return _mm_setr_epi16(vs..., (N ? 0:0)...);
      }(std::make_index_sequence<8 - sizeof...(vs)>());
    }
    else  if constexpr( match(c,category::int32x4, category::uint32x4) )
    {
      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        return _mm_setr_epi32(vs..., (N ? 0:0)...);
      }(std::make_index_sequence<4 - sizeof...(vs)>());
    }
    else  if constexpr( match(c,category::int64x2, category::uint64x2) )
    {
      [[maybe_unused]] __m128i that;

      T *ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
      T d[] = {static_cast<T>(vs)...};

      ptr[0] = d[0];
      ptr[1] = d[1];

      return that;
    }
  }

  //================================================================================================
  // enumerated make - 256bits
  //================================================================================================
  template<real_scalar_value T, typename S, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T, S>> const &, Vs... vs) noexcept
    requires std::same_as<abi_t<T, S>, x86_256_>
  {
    static_assert ( sizeof...(Vs) <= S::value
                  , "[eve::make] - Invalid number of arguments"
                  );

    constexpr auto c = categorize<wide<T, S>>();

          if constexpr( c == category::float64x4) return _mm256_setr_pd(vs...);
    else  if constexpr( c == category::float32x8) return _mm256_setr_ps(vs...);
    else  if constexpr( sizeof(T) == 1) return _mm256_setr_epi8(vs...);
    else  if constexpr( sizeof(T) == 2) return _mm256_setr_epi16(vs...);
    else  if constexpr( sizeof(T) == 4) return _mm256_setr_epi32(vs...);
    else  if constexpr( sizeof(T) == 8) return _mm256_setr_epi64x(vs...);
  }

  //================================================================================================
  // enumerated make - 512bits
  //================================================================================================
  template<real_scalar_value T, typename S, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as<wide<T,S>> const &, Vs... vs) noexcept
    requires std::same_as<abi_t<T, S>, x86_512_>
  {
    static_assert ( sizeof...(Vs) <= S::value
                  , "[eve::make] - Invalid number of arguments"
                  );

    constexpr auto c = categorize<wide<T,S>>();

    /*
      Please take a minute to acknowledge the effect of deciding _mm512_setr should be
      a macro on g++. Thanks, I hate it

      Press F for respect.
    */
    if constexpr( c == category::float64x8)
      return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7)
              { return _mm512_setr_pd(a0,a1,a2,a3,a4,a5,a6,a7); }(vs...);
    else  if constexpr( c == category::float32x16)
      return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7
                , auto b0,auto b1,auto b2,auto b3, auto b4,auto b5,auto b6,auto b7
                )
              { return _mm512_setr_ps(a0,a1,a2,a3,a4,a5,a6,a7,b0,b1,b2,b3,b4,b5,b6,b7); }(vs...);
    else  if constexpr( sizeof(T) == 8)
      return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7)
          { return _mm512_setr_epi64(a0,a1,a2,a3,a4,a5,a6,a7); }(vs...);
    else  if constexpr( sizeof(T) == 4)
      return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7
                , auto b0,auto b1,auto b2,auto b3, auto b4,auto b5,auto b6,auto b7
                )
          { return _mm512_setr_epi32(a0,a1,a2,a3,a4,a5,a6,a7,b0,b1,b2,b3,b4,b5,b6,b7); }(vs...);
    else  if constexpr( sizeof(T) == 2)
      return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7
                , auto b0,auto b1,auto b2,auto b3, auto b4,auto b5,auto b6,auto b7
                , auto c0,auto c1,auto c2,auto c3, auto c4,auto c5,auto c6,auto c7
                , auto d0,auto d1,auto d2,auto d3, auto d4,auto d5,auto d6,auto d7
                )
          { return _mm512_set_epi16 ( d7,d6,d5,d4,d3,d2,d1,d0,c7,c6,c5,c4,c3,c2,c1,c0,b7,
                                      b6,b5,b4,b3,b2,b1,b0,a7,a6,a5,a4,a3,a2,a1,a0
                                    ); }(vs...);
    else  if constexpr( sizeof(T) == 1)
          return  []( auto a0,auto a1,auto a2,auto a3, auto a4,auto a5,auto a6,auto a7
                    , auto b0,auto b1,auto b2,auto b3, auto b4,auto b5,auto b6,auto b7
                    , auto c0,auto c1,auto c2,auto c3, auto c4,auto c5,auto c6,auto c7
                    , auto d0,auto d1,auto d2,auto d3, auto d4,auto d5,auto d6,auto d7
                    , auto e0,auto e1,auto e2,auto e3, auto e4,auto e5,auto e6,auto e7
                    , auto f0,auto f1,auto f2,auto f3, auto f4,auto f5,auto f6,auto f7
                    , auto g0,auto g1,auto g2,auto g3, auto g4,auto g5,auto g6,auto g7
                    , auto h0,auto h1,auto h2,auto h3, auto h4,auto h5,auto h6,auto h7
                    )
              { return _mm512_set_epi8( h7,h6,h5,h4,h3,h2,h1,h0,g7,g6,g5,g4,g3,g2,g1,g0,
                                        f7,f6,f5,f4,f3,f2,f1,f0,e7,e6,e5,e4,e3,e2,e1,e0,
                                        d7,d6,d5,d4,d3,d2,d1,d0,c7,c6,c5,c4,c3,c2,c1,c0,b7,
                                        b6,b5,b4,b3,b2,b1,b0,a7,a6,a5,a4,a3,a2,a1,a0
                                      ); }(vs...);
  }

  //================================================================================================
  // splat make
  //================================================================================================
  template<real_scalar_value T, typename S, typename V>
  EVE_FORCEINLINE auto make(eve::as<wide<T,S>> const&, V v) noexcept
      requires x86_abi<abi_t<T, S>>
  {
    if constexpr(wide<T,S>::size() < eve::fundamental_cardinal_v<T>)
    {
      return [&]<std::size_t... N>(std::index_sequence<N...> const&)
      {
        return make(as<wide<T,fundamental_cardinal_t<T>>>{}, (N<S::value ? v : 0)...);
      }(std::make_index_sequence<fundamental_cardinal_v<T>>());
    }
    else
    {
      constexpr auto c = categorize<wide<T,S>>();

           if constexpr( c == category::float64x8                        ) return _mm512_set1_pd(v);
      else if constexpr( c == category::float64x4                        ) return _mm256_set1_pd(v);
      else if constexpr( c == category::float64x2                        ) return _mm_set1_pd(v);
      else if constexpr( c == category::float32x16                       ) return _mm512_set1_ps(v);
      else if constexpr( c == category::float32x8                        ) return _mm256_set1_ps(v);
      else if constexpr( c == category::float32x4                        ) return _mm_set1_ps(v);
      else if constexpr( match(c,category::int8x64 , category::uint8x64) ) return _mm512_set1_epi8(v);
      else if constexpr( match(c,category::int8x32 , category::uint8x32) ) return _mm256_set1_epi8(v);
      else if constexpr( match(c,category::int8x16 , category::uint8x16) ) return _mm_set1_epi8(v);
      else if constexpr( match(c,category::int16x32, category::uint16x32)) return _mm512_set1_epi16(v);
      else if constexpr( match(c,category::int16x16, category::uint16x16)) return _mm256_set1_epi16(v);
      else if constexpr( match(c,category::int16x8 , category::uint16x8) ) return _mm_set1_epi16(v);
      else if constexpr( match(c,category::int32x16, category::uint32x16)) return _mm512_set1_epi32(v);
      else if constexpr( match(c,category::int32x8 , category::uint32x8) ) return _mm256_set1_epi32(v);
      else if constexpr( match(c,category::int32x4 , category::uint32x4) ) return _mm_set1_epi32(v);
      else if constexpr( match(c,category::int64x8 , category::uint64x8) ) return _mm512_set1_epi64(v);
      else if constexpr( match(c,category::int64x4 , category::uint64x4) ) return _mm256_set1_epi64x(v);
      else if constexpr( match(c,category::int64x2 , category::uint64x2) )
      {
        [[maybe_unused]] __m128i that;
        T *ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
        ptr[0] = ptr[1] = static_cast<T>(v);
        return that;
      }
    }
  }

  //================================================================================================
  // logical cases
  //================================================================================================
  template<real_scalar_value T, typename S, typename... Vs>
  EVE_FORCEINLINE auto make(as<logical<wide<T,S>>> const &, Vs... vs) noexcept
      requires x86_abi<abi_t<T, S>>
  {
    if constexpr( !abi_t<T, S>::is_wide_logical )
    {
      typename logical<wide<T,S>>::storage_type that{};
      [&]<std::size_t... N>(auto& v, std::index_sequence<N...>){ (( v |= vs?(1ULL<<N):0),...); }
      (that.value, std::make_index_sequence<sizeof...(vs)>{});

      return that;
    }
    else
    {
      return make(as<wide<T,S>> {}, logical<T>(vs).mask()...);
    }
  }

  template<real_scalar_value T, typename S,typename V>
  EVE_FORCEINLINE auto make(as<logical<wide<T,S>>> const &, V v) noexcept
      requires x86_abi<abi_t<T, S>>
  {
    if constexpr( !abi_t<T, S>::is_wide_logical )
    {
      using s_t = typename logical<wide<T,S>>::storage_type;
      using i_t = typename s_t::type;

      constexpr i_t false_bits =  i_t{0};
      constexpr i_t true_bits  = []{
        if constexpr ( S() < s_t::bits ) return i_t{ (1ULL << S::value) -1 };
        else                             return ~i_t{0};
      }();

      return s_t{ !!v ? true_bits : false_bits };
    }
    else
    {
      return make(as<wide<T,S>> {}, logical<T>(v).mask());
    }
  }
}

#if defined(SPY_COMPILER_IS_GCC)
#pragma GCC diagnostic pop
#endif
