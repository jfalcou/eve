//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/memory/aligned_ptr.hpp>

#include <array>
#include <numeric>

namespace
{
//==================================================================================================
// Aligned store tests
//==================================================================================================
TTS_CASE_WITH( "Check store behavior with aligned pointers"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T data, L logical_data)
{
  constexpr auto algt = eve::alignment_v<T>;

  std::array<eve::element_type_t<T>, 3 * T::size()> ref;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_ref;

  for(int i = 0; i < T::size(); ++i)
  {
    ref[ i              ] =  1 + i;
    ref[ i + T::size()  ] =  1 + i;
    ref[ i + 2*T::size()] =  1 + i;

    logical_ref[ i              ] = ((1+i) % 2) == 0;
    logical_ref[ i + T::size()  ] = ((1+i) % 2) == 0;
    logical_ref[ i + 2*T::size()] = ((1+i) % 2) == 0;
  }

  alignas(algt) std::array<eve::element_type_t<T>, 3 * T::size()> target;
  alignas(algt) std::array<eve::element_type_t<L>, 3 * T::size()> logical_target;

  eve::store(data, eve::as_aligned(&target[ 0            ], eve::cardinal_t<T>{}) );
  eve::store(data, eve::as_aligned(&target[ T::size()    ], eve::cardinal_t<T>{}) );
  eve::store(data, eve::as_aligned(&target[ 2 * T::size()], eve::cardinal_t<T>{}) );

  eve::store(logical_data, eve::as_aligned(&logical_target[ 0            ], eve::cardinal_t<T>{}) );
  eve::store(logical_data, eve::as_aligned(&logical_target[ T::size()    ], eve::cardinal_t<T>{}) );
  eve::store(logical_data, eve::as_aligned(&logical_target[ 2 * T::size()], eve::cardinal_t<T>{}) );

  TTS_ALL_EQUAL(target        , ref         );
  TTS_ALL_EQUAL(logical_target, logical_ref );
};

//==================================================================================================
// Aligned store tests
//==================================================================================================
TTS_CASE_WITH( "Check store behavior with pointer of different alignment"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T data, L logical_data)
{
  std::array<eve::element_type_t<T>, 256> ref;
  std::array<eve::element_type_t<L>, 256> logical_ref;

  auto test = [&]<typename D, std::ptrdiff_t A>(eve::fixed<A>, auto f, D d)
  {
    if (!eve::is_aligned(f, eve::fixed<A>{}))   return;

    if constexpr (A*sizeof(eve::element_type_t<D>) >= T::alignment())
    {
      if(::tts::arguments()[{"-v","--verbose"}])
        std::cout << "With alignment: " << A << std::endl;

      eve::aligned_ptr<eve::element_type_t<D>, eve::fixed<A>> ptr{f};
      eve::store(d, ptr);
      TTS_EQUAL(D{f}, d);
      eve::store(D{0}, ptr);
      TTS_EQUAL(D{f}, D{0});
      eve::store[eve::ignore_none](d, ptr);
      TTS_EQUAL(D{f}, d);
    }
    else
    {
      TTS_PASS("No test for this size");
    }
  };

  for (auto* f = ref.begin();f != ref.end() - T::size() + 1;++f)
  {
    [&]<std::ptrdiff_t...N>( std::integer_sequence<std::ptrdiff_t,N...> )
    {
      (test(eve::lane<(1<<(N+2))>, f, data),...);
    }( std::make_integer_sequence<std::ptrdiff_t,5>{});
  }

  for (auto* f = logical_ref.begin();f != logical_ref.end() - T::size() + 1;++f)
  {
    [&]<std::ptrdiff_t...N>( std::integer_sequence<std::ptrdiff_t,N...> )
    {
      (test(eve::lane<(1<<(N+2))>, f, logical_data),...);
    }( std::make_integer_sequence<std::ptrdiff_t,5>{});
  }
};
}
