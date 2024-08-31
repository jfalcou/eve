//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <numeric>
#include <span>
#include <vector>

template<typename T>
void
runTestForLen(eve::as<T>, int len)
{
  std::size_t                         ulen = (std::size_t)len;
  std::vector<eve::element_type_t<T>> haystack(std::max(3 * ulen + 5, std::size_t(60)), 0);

  std::size_t max_start = std::min((std::size_t)T::size() + 1, haystack.size() - ulen);

  for( std::size_t start = 0; start != max_start; ++start )
  {
    std::span<eve::element_type_t<T>> needle(haystack.data() + start, ulen);

    for( auto& e : needle )
    {
      e = 1;

      auto search = eve::algo::search[eve::algo::force_cardinal<T::size()>];

      TTS_EQUAL((std::ptrdiff_t)start, search(haystack, needle) - haystack.begin(), REQUIRED)
          << "\nneedle len: " << needle.size() << "\ne in haystack: " << (&e - haystack.data())
          << "\ne in needle: " << (&e - needle.data());
      e = 0;
    }
  }
}

template<typename T>
auto
interesting_lengths()
{
  constexpr int t_size = (int)T::size();
  return std::array {
      2,
      (t_size / 2),
      t_size,
      t_size + 1,
      t_size * 3 / 2,
      t_size * 3 / 2 + 1,
      t_size * 3 - 5,
      t_size * 3 + 4,
  };
}

TTS_CASE_TPL("eve.algo.search_different_lengths", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  for( int len : interesting_lengths<T>() )
  {
    if( len < 1 ) { continue; }
    runTestForLen(eve::as<T> {}, len);
  }
};
