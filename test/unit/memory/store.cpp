//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/replace.hpp>
#include <eve/function/store.hpp>

#include <array>
#include <numeric>

namespace
{
//==================================================================================================
// Unaligned store tests
//==================================================================================================
EVE_TEST( "Check store behavior with unaligned pointers"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L> (T data, L logical_data)
{
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

  std::array<eve::element_type_t<T>, 3 * T::size()> target;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_target;

  eve::store(data, &target[ 0            ]);
  eve::store(data, &target[ T::size()    ]);
  eve::store(data, &target[ 2 * T::size()]);

  eve::store(logical_data, &logical_target[ 0            ]);
  eve::store(logical_data, &logical_target[ T::size()    ]);
  eve::store(logical_data, &logical_target[ 2 * T::size()]);

  TTS_ALL_EQUAL(target        , ref         );
  TTS_ALL_EQUAL(logical_target, logical_ref );
};

//==================================================================================================
// Aligned store tests
//==================================================================================================
EVE_TEST( "Check store behavior with aligned pointers"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
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

  eve::store(data, eve::as_aligned<algt>(&target[ 0            ]) );
  eve::store(data, eve::as_aligned<algt>(&target[ T::size()    ]) );
  eve::store(data, eve::as_aligned<algt>(&target[ 2 * T::size()]) );

  eve::store(logical_data, eve::as_aligned<algt>(&logical_target[ 0            ]) );
  eve::store(logical_data, eve::as_aligned<algt>(&logical_target[ T::size()    ]) );
  eve::store(logical_data, eve::as_aligned<algt>(&logical_target[ 2 * T::size()]) );

  TTS_ALL_EQUAL(target        , ref         );
  TTS_ALL_EQUAL(logical_target, logical_ref );
};

//==================================================================================================
// Aligned store tests
//==================================================================================================
EVE_TEST( "Check store behavior with pointer of different alignment"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L>(T data, L logical_data)
{
  std::array<eve::element_type_t<T>, 256> ref;
  std::array<eve::element_type_t<L>, 256> logical_ref;

  auto test = [&]<typename D, std::ptrdiff_t A>(eve::fixed<A>, auto f, D d)
  {
    if (!eve::is_aligned<A>(f))   return;

    if constexpr (A >= T::static_alignment)
    {
      if(::tts::verbose_status) std::cout << "With alignment: " << A << std::endl;

      eve::aligned_ptr<eve::element_type_t<D>, static_cast<std::size_t>(A)> ptr{f};
      eve::store(d, ptr);
      TTS_EQUAL(D{f}, d);
      eve::store(D{0}, ptr);
      TTS_EQUAL(D{f}, D{0});
      eve::store[eve::ignore_none](d, ptr);
      TTS_EQUAL(D{f}, d);
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

template <typename T>
void store_ignore_test_pass(T what, eve::element_type_t<T> garbage_value, eve::element_type_t<T> other_value)
{
  using e_t = eve::element_type_t<T>;

  // ignore_all should not write anything
  {
    e_t garbage;
    eve::store[eve::ignore_all](what, &garbage + 5);
  }

  // write to one element (ASAN test).
  {
    e_t data;
    data = garbage_value;
    eve::store[eve::ignore_first(T::static_size - 1)](what, &data - T::static_size + 1);
    TTS_EQUAL(data, what.back());

    eve::store[eve::ignore_last(T::static_size - 1)](what, &data);
    TTS_EQUAL(data, what.front());

    eve::store[eve::ignore_extrema(0, T::static_size - 1)](what, &data);
    TTS_EQUAL(data, what.front());
  }

  // ignore doesn't write garbarge values
  {
    std::array<e_t, 2 * T::static_size> data;
    const T filler{garbage_value};

    auto run_one_case = [&](auto ptr, auto ignore)
    {
      eve::store(filler, ptr);
      eve::store[ignore](what, ptr);
      T actual(ptr);
      T expected = eve::replace_ignored(what, ignore, filler);
      TTS_EQUAL(actual, expected);

      eve::store(filler, ptr);
      eve::store[ignore.else_(other_value)](what, ptr);
      T alternative_actual(ptr);
      T alternative_expected = eve::replace_ignored(what, ignore, other_value);
      TTS_EQUAL(alternative_actual, alternative_expected);
    };

    auto run_all_ignores = [&](auto ptr)
    {
      for (int i = 0; i != T::static_size + 1; ++i)
      {
        run_one_case(ptr, eve::ignore_first(i));
        run_one_case(ptr, eve::ignore_last(i));

        for (int j = T::static_size - i; j != -1; --j)
        {
          run_one_case(ptr, eve::ignore_extrema(i, j));
        }
      }
    };

    for (e_t* f = data.begin(); f != data.end() - T::static_size; ++f)
    {
      run_all_ignores(f);

      static constexpr std::ptrdiff_t alignment = sizeof(e_t) * T::static_size;

      if (!eve::is_aligned<alignment>(f)) continue;

      run_all_ignores(eve::aligned_ptr<e_t, alignment>(f));

      static constexpr std::ptrdiff_t double_alignment = sizeof(e_t) * T::static_size * 2;

      if (!eve::is_aligned<double_alignment>(f)) continue;

      run_all_ignores(eve::aligned_ptr<e_t, double_alignment>(f));
    }
  }
}

EVE_TEST( "Check store behavior with ignore"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L>(T data, L logical_data)
{
  store_ignore_test_pass(data, 17, 19);
  store_ignore_test_pass(logical_data, true, false);
};

}
