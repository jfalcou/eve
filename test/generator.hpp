//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include "test_distribution.hpp"
#include "types.hpp"
#include <tuple>

namespace eve::test
{
  //================================================================================================
  // Turn a list of sampels into the correct type
  //================================================================================================
  template<typename S, typename T, std::size_t... N>
  auto make_args(S const& t, std::index_sequence<N...>, eve::as_<T>)
  {
    auto constexpr get = [](auto const& p)
    {
      if constexpr( eve::simd_value<T> )
      {
        using type = as_wide_t< std::remove_cvref_t<decltype(*p.data())>, eve::cardinal_t<T>>;
        return type(p.data());
      }
      else
      {
        return *p.data();
      }
    };

    return std::make_tuple( get(std::get<N>(t))... );
  }

  //================================================================================================
  // no-data generator - used to propagate types only
  //================================================================================================
  template<typename V, typename T> auto as_value(V v, as_<T>)
  {
    if constexpr(std::is_invocable_v<V,as_<T>>)  return v(eve::as_<T>{});
    else                                         return static_cast<T>(v);
  }

  //================================================================================================
  // no-data generator - used to propagate types only
  //================================================================================================
  inline auto const no_data = []<typename T>(eve::as_<T>, auto&)
  {
    using d_t = std::array<eve::element_type_t<T>,eve::cardinal_v<T>>;
    return d_t{};
  };

  //================================================================================================
  // Turn a generator into a integral generator
  //================================================================================================
  template<typename G> inline auto as_integer(G)
  {
    return []<typename T>(eve::as_<T>, auto& s) { return G{}( eve::as_<eve::as_integer_t<T>>{},s); };
  }

  //================================================================================================
  // arithmetic ramp - generate V V+1 .. V+n
  //================================================================================================
  template<typename V> auto ramp(V v)
  {
    return  [=]<typename T>(eve::as_<T>, auto&)
            {
              std::array<eve::element_type_t<T>, eve::cardinal_v<T>> d;
              for(std::ptrdiff_t i = 0;i<T::size();++i) d[i] = v+i;
              return d;
            };
  }

  //================================================================================================
  // logical ramp - generate 1 % K 2 %k .. N %K
  //================================================================================================
  template<typename V, typename K> auto logicals(V v, K k)
  {
    return  [=]<typename T>(eve::as_<T>, auto&)
            {
              std::array<eve::logical<eve::element_type_t<T>>,eve::cardinal_v<T>> d;
              for(std::ptrdiff_t i = 0;i<T::size();++i) d[i] = ((v+i)%k) == 0;
              return d;
            };
  }

  //================================================================================================
  // random arithmetic values
  //================================================================================================
  template<typename Mn, typename Mx> auto randoms(Mn mn, Mx mx)
  {
    return [=]<typename T>(eve::as_<T>, auto& gen)
    {
      using e_t = eve::element_type_t<T>;
      eve::prng<e_t> dist(as_value(mn,as_<e_t>{}),as_value(mx,as_<e_t>{}));

      std::array<e_t,eve::cardinal_v<T>> d;
      std::for_each(d.begin(),d.end(), [&](auto& e) { e = dist(gen); });

      return d;
    };
  }

  //================================================================================================
  // Constant value
  //================================================================================================
  template<typename V> auto value(V v)
  {
    return [=]<typename T>(eve::as_<T> tgt, auto&)
    {
      std::array<eve::element_type_t<T>,eve::cardinal_v<T>> d;
      auto val = as_value(v,tgt);

      for(auto& e : d) e = val;

      return d;
    };
  }

  //================================================================================================
  // Generators combinator
  //================================================================================================
  template<typename... G> inline auto generate(G... g)
  {
    return [=]<typename T>(eve::as_<T> t, auto& s)
    {
      return std::make_tuple(g(t,s)...);
    };
  }

  //================================================================================================
  // Lambda "seed" capture
  //================================================================================================
  template<typename TestBed> struct test_setup
  {
    test_setup(TestBed f) : base_test(f) {}
    auto operator+(auto TestBody) const
    {
      base_test( TestBody );
      return true;
    }

    TestBed base_test;
  };
}

#define EVE_TEST(DESCRIPTION,TYPES,SAMPLES)                                                         \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =  ::eve::test::test_setup{                       \
[](auto tests)                                                                                      \
  {                                                                                                 \
    auto s = SAMPLES;                                                                               \
    auto const single_test = [=]<typename T>( eve::as_<T> target)                                   \
    {                                                                                               \
      [=]<std::size_t... N>(std::index_sequence<N...>)                                              \
      {                                                                                             \
        ::tts::detail::test::acknowledge(::tts::detail::test                                        \
        {                                                                                           \
            std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"       \
          , [=]()                                                                                   \
            {                                                                                       \
              std::mt19937::result_type seed(18102008);                                             \
              seed = ::tts::arguments.value_or(seed, "-s", "--seed");                               \
              std::mt19937 gen(seed);                                                               \
                                                                                                    \
              constexpr std::make_index_sequence<sizeof...(N)> size = {};                           \
              auto data = s(eve::as_<T>{}, gen);                                                    \
              auto args = eve::test::make_args(data, size, eve::as_<T>{});                          \
              tests(std::get<N>(args)...);                                                          \
            }                                                                                       \
          });                                                                                       \
      }(std::make_index_sequence<std::tuple_size<decltype ( s ( target                              \
                                                              , std::declval<std::mt19937&>()       \
                                                              )                                     \
                                                          )>::value>{});                            \
    };                                                                                              \
                                                                                                    \
    [&]<template<class...> class L,typename... Ts>(L<Ts...>)                                        \
    {                                                                                               \
      (single_test( eve::as_<Ts>() ),...);                                                          \
    }( TYPES );                                                                                     \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                           \
/**/


#define EVE_TEST_BED(DESCRIPTION,TYPES,SAMPLES,TESTS)                                               \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =                                                 \
[]<template<class...> class List,typename... Ts, typename S>(List<Ts...>, S s)                      \
  {                                                                                                 \
    auto const single_test = [=]<typename T>( eve::as_<T> target)                                   \
    {                                                                                               \
      [=]<std::size_t... N>(std::index_sequence<N...>)                                              \
      {                                                                                             \
        ::tts::detail::test::acknowledge(::tts::detail::test                                        \
        {                                                                                           \
            std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"       \
          , [=]()                                                                                   \
            {                                                                                       \
              std::mt19937::result_type seed(18102008);                                             \
              seed = ::tts::arguments.value_or(seed, "-s", "--seed");                                              \
              std::mt19937 gen(seed);                                                               \
                                                                                                    \
              constexpr std::make_index_sequence<sizeof...(N)> size = {};                           \
              auto data = s(eve::as_<T>{}, gen);                                                    \
              auto args = eve::test::make_args(data, size, eve::as_<T>{});                          \
              TESTS(std::get<N>(args)...);                                                          \
            }                                                                                       \
          });                                                                                       \
      }(std::make_index_sequence<std::tuple_size<decltype ( s ( target                              \
                                                              , std::declval<std::mt19937&>()       \
                                                              )                                     \
                                                          )>::value>{});                            \
    };                                                                                              \
                                                                                                    \
    (single_test( eve::as_<Ts>() ),...);                                                            \
                                                                                                    \
    return true;                                                                                    \
  }( TYPES, SAMPLES)                                                                                \
/**/
