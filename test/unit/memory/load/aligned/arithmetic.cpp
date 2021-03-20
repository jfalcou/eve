//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>
#include <array>
#include <list>

//==================================================================================================
// Load into wide from an aligned pointer
//==================================================================================================
auto aligned_tests = []<typename T>(T reference)
{
  using v_t = eve::element_type_t<T>;

  constexpr std::ptrdiff_t algt   = eve::alignment_v<T>;

  auto [data  ,idx  ] = page<v_t , eve::fixed<T::size()>>();

  auto* ptr              = &data[idx];
  auto const* const_ptr  = ptr;

  TTS_EQUAL(T(eve::as_aligned<algt>(ptr))                                       , reference );
  TTS_EQUAL(T(eve::as_aligned<algt>(const_ptr))                                 , reference );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ptr)      , eve::lane<T::size()>)) , reference );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(const_ptr), eve::lane<T::size()>)) , reference );

  if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
  {
    TTS_EQUAL(eve::load(eve::as_aligned<algt>(ptr))       , reference         );
    TTS_EQUAL(eve::load(eve::as_aligned<algt>(const_ptr)) , reference         );
  }
};

EVE_TEST_BED( "Check load to wides from aligned pointer"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::ramp(1))
            , aligned_tests
            );

//==================================================================================================
// Realigned load tests
//==================================================================================================
auto realigned_tests = []<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  std::array<v_t               , 256> ref;

  std::iota(ref.begin()         , ref.end()         , 0);

  auto test = [&]<typename D, typename P, std::ptrdiff_t A>(eve::fixed<A>, P* f, D expected)
  {
    if (!eve::is_aligned<A>(f))   return;

    if constexpr (A >= D::static_alignment)
    {
      eve::aligned_ptr<P, static_cast<std::size_t>(A)> ptr{f};
      TTS_EQUAL(D{ptr}                                           , expected);
      TTS_EQUAL(eve::unsafe(eve::load)(ptr, eve::lane<D::size()>), expected);
    }
  };

  for (auto* f = ref.begin();f != ref.end() - T::size() + 1;++f)
  {
    T expected(f);
    [&]<std::ptrdiff_t...N>( std::integer_sequence<std::ptrdiff_t,N...> )
    {
      (test(eve::lane<(1<<(N+2))>, f, expected),...);
    }( std::make_integer_sequence<std::ptrdiff_t,5>{});
  }
};

EVE_TEST_BED( "Check load to wides from re-aligned pointer"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , realigned_tests
            );
