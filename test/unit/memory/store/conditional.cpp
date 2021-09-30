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
    eve::store[eve::ignore_first(T::size() - 1)](what, &data - T::size() + 1);
    TTS_EQUAL(data, what.back());

    eve::store[eve::ignore_last(T::size() - 1)](what, &data);
    TTS_EQUAL(data, what.front());

    eve::store[eve::ignore_extrema(0, T::size() - 1)](what, &data);
    TTS_EQUAL(data, what.front());
  }

  // ignore doesn't write garbage values
  {
    std::array<e_t, 2 * T::size()> data;
    const T filler{garbage_value};

    auto run_one_case = [&,what](auto ptr, auto ignore)
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
      constexpr auto sz = std::min(T::size()/2,std::ptrdiff_t{8});

      for (int i = 0; i != sz + 1; ++i)
      {
        run_one_case(ptr, eve::ignore_first(i));
        run_one_case(ptr, eve::ignore_last(i));
        run_one_case(ptr, eve::ignore_first(sz-1-i));
        run_one_case(ptr, eve::ignore_last(sz-i-i));

        for (int j = i; j != -1; --j)
        {
          std::cout << "cond: " << eve::ignore_extrema(i, j) << "\n";
          run_one_case(ptr, eve::ignore_extrema(i, j));
        }
      }
    };

    for (e_t* f = data.begin(); f != data.end() - T::size(); ++f)
    {
      std::cout << "Test @" << (void*)(f) << "\n";
      run_all_ignores(f);

      if (!eve::is_aligned(f,eve::cardinal_t<T>{})) continue;

      run_all_ignores(eve::aligned_ptr<e_t, eve::cardinal_t<T>>(f));

      if (!eve::is_aligned(f, typename eve::cardinal_t<T>::combined_type{})) continue;

      run_all_ignores(eve::aligned_ptr<e_t, typename eve::cardinal_t<T>::combined_type>(f));
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
