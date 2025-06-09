//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <utility>
#include <eve/detail/kumi.hpp>

namespace eve
{
  template<kumi::product_type Data>
  struct coefficients : Data
  {
    coefficients(Data const& d) : Data{d} {}

    template<typename... Cs>
    coefficients(Cs const&... cs) : Data{cs...} {}
  };

  template<typename... Cs>
  coefficients(Cs const&... cs) -> coefficients<kumi::tuple<Cs...>>;

  template<kumi::product_type Data>
  struct nodes : Data
  {
    nodes(Data const& d) : Data{d} {}

    template<typename... Cs>
    nodes(Cs const&... cs) : Data{cs...} {}
  };

  template<typename... Cs>
  nodes(Cs const&... cs) -> nodes<kumi::tuple<Cs...>>;
}

template<kumi::product_type Data>
struct std::tuple_size<eve::coefficients<Data>> : kumi::size<Data> {};

template<std::size_t I, kumi::product_type Data>
struct std::tuple_element<I,eve::coefficients<Data>> : std::tuple_element<I,Data> {};

template<kumi::product_type Data>
struct std::tuple_size<eve::nodes<Data>> : kumi::size<Data> {};

template<std::size_t I, kumi::product_type Data>
struct std::tuple_element<I,eve::nodes<Data>> : std::tuple_element<I,Data> {};
