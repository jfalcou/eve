//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>


const auto loader = []<std::size_t... N>(auto const& d, auto card, std::index_sequence<N...>)
{
  return kumi::make_tuple( eve::load(&d[N*card], card)... );
};

//==================================================================================================
// interleave test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of interleave on arithmetic data"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  [&]<std::size_t... Rs>( std::index_sequence<Rs...>)
  {
    auto rep = [&]<std::size_t Replication>( std::integral_constant<std::size_t,Replication> )
    {
      // Build and fill data blocks of Replication x T::size() elements for input and reference
      std::array<typename T::value_type,T::size() * Replication> data, ref;

      std::size_t index = 0;
      for(std::size_t r = 0; r < Replication; ++r)
        for(std::ptrdiff_t i = 0; i < T::size();++i)
          data[index++] = (i+1) + T::size()*r;

      index = 0;
      for(std::ptrdiff_t i = 0; i < T::size();++i)
        for(std::size_t r = 0; r < Replication; ++r)
          ref[index++] = (i+1) + T::size()*r;

      // Load the data & references then interleave
      using rep_t   = std::make_index_sequence<Replication>;
      using card_t  = typename T::cardinal_type;

      auto inputs       = loader(data, card_t{}, rep_t{});
      auto reference    = loader(ref , card_t{}, rep_t{});
      auto interleaved  = kumi::apply( [](auto... m) { return eve::interleave(m...); }, inputs);

      TTS_EXPECT( eve::all(interleaved == reference) )
        << "\ni: " << inputs
        << "\ne: " << reference
        << "\nr: " << interleaved
        << '\n';
    };

    ((rep( std::integral_constant<std::size_t,Rs>{} )),...);
  }(std::index_sequence<1,2,3,4,5,8,16>{});
};

TTS_CASE_TPL( "Check behavior of interleave on logical data"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  [&]<std::size_t... Rs>( std::index_sequence<Rs...>)
  {
    auto rep = [&]<std::size_t Replication>( std::integral_constant<std::size_t,Replication> )
    {
      // Build and fill data blocks of Replication x T::size() elements for input and reference
      std::array<typename l_t::value_type,l_t::size() * Replication> data, ref;

      std::size_t index = 0;
      for(std::size_t r = 0; r < Replication; ++r)
        for(std::ptrdiff_t i = 0; i < T::size();++i)
          data[index++] = ((i+1) + T::size()*r) % 2 == 0;

      index = 0;
      for(std::ptrdiff_t i = 0; i < T::size();++i)
        for(std::size_t r = 0; r < Replication; ++r)
          ref[index++] = ((i+1) + T::size()*r) % 2 == 0;

      // Load the data & references then interleave
      using rep_t   = std::make_index_sequence<Replication>;
      using card_t  = typename l_t::cardinal_type;

      auto inputs       = loader(data, card_t{}, rep_t{});
      auto reference    = loader(ref , card_t{}, rep_t{});
      auto interleaved  = kumi::apply( [](auto... m) { return eve::interleave(m...); }, inputs);

      TTS_EXPECT( eve::all(interleaved == reference) );
    };

    ((rep( std::integral_constant<std::size_t,Rs>{} )),...);
  }(std::index_sequence<1,2,3,4,5,8,16>{});
};
