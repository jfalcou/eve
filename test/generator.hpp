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
  template<typename S, typename T, std::size_t... N>
  auto make_args(S const& t, std::index_sequence<N...>, eve::as_<T>)
  {
    auto constexpr get = [](auto const& p)
    {
      if constexpr( eve::scalar_value<T> )  return *p.data();
      else                                  return as_wide_t< std::remove_cvref_t<decltype(*p.data())>
                                                            , eve::cardinal_t<T>
                                                            >(p.data());
    };

    return std::make_tuple( get(std::get<N>(t))... );
  }

  auto no_data = []<typename T>(eve::as_<T>, auto)
  {
    using d_t = std::array<eve::element_type_t<T>,eve::cardinal_v<T>>;
    return std::make_tuple(d_t{});
  };
}

#define EVE_TEST_BED(DESCRIPTION,TYPES,SAMPLES,TESTS)                                               \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =                                                 \
[]<template<class...> class List,typename... Ts, typename S, typename Test>( List<Ts...>, S, Test)  \
  {                                                                                                 \
    auto const single_test = [&]<typename T>( eve::as_<T> target)                                   \
    {                                                                                               \
      [&]<std::size_t... N>(std::index_sequence<N...>)                                              \
      {                                                                                             \
        ::tts::detail::test::acknowledge(::tts::detail::test                                        \
        {                                                                                           \
            std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"       \
          , []( ::tts::detail::env &r, bool v, ::tts::options const& a )                            \
            {                                                                                       \
              std::mt19937::result_type seed(18102008);                                             \
              seed = a.value_or(seed, "-s", "--seed");                                              \
                                                                                                    \
              constexpr std::make_index_sequence<sizeof...(N)> size = {};                           \
              auto data = S{}(eve::as_<T>{}, seed);                                                 \
              auto args = eve::test::make_args(data, size, eve::as_<T>{});                          \
              Test{}(r,v,a,std::get<N>(args)...);                                                   \
            }                                                                                       \
          });                                                                                       \
      }(std::make_index_sequence<std::tuple_size<decltype(S{}(target, 0))>::value>{});              \
    };                                                                                              \
                                                                                                    \
    (single_test( eve::as_<Ts>() ),...);                                                            \
                                                                                                    \
    return true;                                                                                    \
  }( TYPES, SAMPLES, TESTS)                                                                         \
/**/
