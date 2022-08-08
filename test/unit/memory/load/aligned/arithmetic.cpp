//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <array>
#include <list>

//==================================================================================================
// Load into wide from an aligned pointer
//==================================================================================================
TTS_CASE_WITH( "Check load to wides from aligned pointer"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1))
        )
<typename T>(T reference)
{
  using v_t = eve::element_type_t<T>;
  using lanes_t = eve::cardinal_t<T>;

  auto [data  ,idx  ] = page<v_t , lanes_t>();

  auto* ptr              = &data[idx];
  auto const* const_ptr  = ptr;

  TTS_EQUAL(T(eve::as_aligned(ptr,lanes_t{}))                           , reference );
  TTS_EQUAL(T(eve::as_aligned(const_ptr,lanes_t{}))                     , reference );
  TTS_EQUAL((eve::load(eve::as_aligned(ptr,lanes_t{})      , lanes_t{})), reference );
  TTS_EQUAL((eve::load(eve::as_aligned(const_ptr,lanes_t{}), lanes_t{})), reference );

  if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
  {
    TTS_EQUAL(eve::load(eve::as_aligned(ptr,lanes_t{}))       , reference  );
    TTS_EQUAL(eve::load(eve::as_aligned(const_ptr,lanes_t{})) , reference  );
  }
};

//==================================================================================================
// Realigned load tests
//==================================================================================================
TTS_CASE_TPL( "Check load to wides from re-aligned pointer", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  std::array<v_t               , 256> ref;

  std::iota(ref.begin()         , ref.end()         , 0);

  auto test = [&]<typename D, typename P, std::ptrdiff_t A>(eve::fixed<A>, P* f, D expected)
  {
    if (!eve::is_aligned(f, eve::fixed<A>{}))   return;

    if constexpr (A*sizeof(P) >= D::alignment())
    {
      eve::aligned_ptr<P, eve::fixed<A>> ptr{f};
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
    }( std::make_integer_sequence<std::ptrdiff_t,6>{});
  }
};
