//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "mismatch_generic_test.hpp"
#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

template<typename TraitsSupport> struct search_equal_ : TraitsSupport
{
  template<typename R1, typename R2>
  EVE_FORCEINLINE bool operator()(const R1& roi1, const R2& roi2) const
  {
    auto [r1, r2] = eve::views::zip(roi1, roi2);
    return operator()(r1, r2);
  }

  EVE_FORCEINLINE bool operator()(eve::algo::relaxed_range auto const& r1,
                                  eve::algo::relaxed_range auto const& r2) const
  {
    std::ptrdiff_t size1 = r1.end() - r1.begin();
    std::ptrdiff_t size2 = r2.end() - r2.begin();
    if( size1 != size2 ) return false;

    auto res = eve::algo::search[TraitsSupport::get_traits()](r1, r2);
    if( res == r1.begin() ) return true;
    if( res == r1.end() ) return false;

    TTS_FAIL("res shoudld be begin or end");
    return false;
  }
};

inline constexpr auto search_equal =
    eve::algo::function_with_traits<search_equal_>[eve::algo::search.get_traits()];

TTS_CASE_TPL("search_equal generic", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  algo_test::mismatch_generic_test(eve::as<T> {},
                                   search_equal,
                                   [](auto, auto zip_l, auto expected, bool actual)
                                   { TTS_EQUAL((expected == zip_l), actual); });
};
