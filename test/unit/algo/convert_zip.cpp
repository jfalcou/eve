//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/convert.hpp>
#include <eve/algo/zip.hpp>

using i32_x2    = kumi::tuple<std::int32_t, std::int32_t>;

struct point2D : i32_x2 {};
template<>              struct eve::is_product_type<point2D> : std::true_type {};
template<>              struct std::tuple_size<point2D>      : std::tuple_size<i32_x2> {};
template<std::size_t I> struct std::tuple_element<I,point2D> : std::tuple_element<I, i32_x2> {};

using points2D_2 = kumi::tuple<point2D, point2D>;

struct line2D: points2D_2 {};

template<>              struct eve::is_product_type<line2D> : std::true_type {};
template<>              struct std::tuple_size<line2D>      : std::tuple_size<points2D_2> {};
template<std::size_t I> struct std::tuple_element<I,line2D> : std::tuple_element<I, points2D_2> {};

TTS_CASE("convert zip iter")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  using v_it = std::vector<int>::const_iterator;
  using c_it = std::vector<std::int8_t>::iterator;
  using c_to_v = eve::algo::converting_iterator<c_it, int>;

  using zip_v_c_to_v          = eve::algo::zip_iterator<v_it, c_to_v>;
  using zip_v_c_to_v_as_point = eve::algo::converting_iterator<zip_v_c_to_v, point2D>;

  // tuple and point
  {
    auto zipped = eve::algo::zip(v.begin(), c.begin());
    auto as_int_int = eve::algo::convert(zipped, eve::as<kumi::tuple<int, int>>{});
    TTS_TYPE_IS(decltype(as_int_int), zip_v_c_to_v);

    // As product
    auto as_point2D = eve::algo::convert(zipped, eve::as<point2D>{});
    TTS_TYPE_IS(decltype(as_point2D), zip_v_c_to_v_as_point);
  }

  // Line
  {
    using expected = eve::algo::converting_iterator<
      eve::algo::zip_iterator<v_it,c_to_v,v_it,v_it>,
      line2D
    >;

    auto actual1 = eve::algo::convert(
      eve::algo::zip(v.begin(), c.begin(), v.begin(), v.begin()), eve::as<line2D>{}
    );
    TTS_TYPE_IS(decltype(actual1), expected);

#if 0  // FIX-918
    auto actual2 = eve::algo::convert(
      eve::algo::zip(
        eve::algo::convert(eve::algo::zip(v, c), eve::as<point2D>{}),
        eve::algo::convert(eve::algo::zip(v, v), eve::as<point2D>{})
      ),
      eve::as<line2D>{});
    TTS_TYPE_IS(decltype(actual2), expected);
#endif
  }
}

TTS_CASE("convert zip range")
{
  std::vector<int> const   v{1, 2, 3, 4};
  std::vector<std::int8_t> c{'a', 'b', 'c', 'd'};

  using v_ref = eve::algo::range_ref_wrapper<std::vector<int> const>;
  using c_ref = eve::algo::range_ref_wrapper<std::vector<std::int8_t>>;
  using c_to_v = eve::algo::converting_range<c_ref, int>;

  using zip_v_c_to_v          = eve::algo::zip_range<v_ref, c_to_v>;
  using zip_v_c_to_v_as_point = eve::algo::converting_range<zip_v_c_to_v, point2D>;

  // tuple and point
  {
    auto zipped = eve::algo::zip(v, c);
    auto as_int_int = eve::algo::convert(zipped, eve::as<kumi::tuple<int, int>>{});
    TTS_TYPE_IS(decltype(as_int_int), zip_v_c_to_v);

    // As product
    auto as_point2D = eve::algo::convert(zipped, eve::as<point2D>{});
    TTS_TYPE_IS(decltype(as_point2D), zip_v_c_to_v_as_point);
  }

  // Line
  {
    using expected = eve::algo::converting_range<
      eve::algo::zip_range<v_ref,c_to_v,v_ref,v_ref>,
      line2D
    >;

    auto actual1 = eve::algo::convert(
      eve::algo::zip(v, c, v, v), eve::as<line2D>{}
    );
    TTS_TYPE_IS(decltype(actual1), expected);

#if 0  // FIX-918
    auto actual2 = eve::algo::convert(
      eve::algo::zip(
        eve::algo::convert(eve::algo::zip(v, c), eve::as<point2D>{}),
        eve::algo::convert(eve::algo::zip(v, v), eve::as<point2D>{})
      ),
      eve::as<line2D>{});
    TTS_TYPE_IS(decltype(actual2), expected);
#endif
  }
}
