//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/traits/common_type.hpp>

#include <eve/constant/zero.hpp>

#include <tuple>

TTS_CASE("eve::common_type, half_c integrals")
{
  // Explanation
  TTS_TYPE_IS((std::common_type_t<std::int32_t,  std::uint32_t>), std::uint32_t);
  TTS_TYPE_IS((std::common_type_t<std::int32_t,  std::uint64_t>), std::uint64_t);
  TTS_TYPE_IS((std::common_type_t<std::uint32_t, std::int64_t> ), std::int64_t);

  // std::int8_t
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::int8_t>  ), std::int8_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::uint8_t> ), std::uint8_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::int8_t, std::uint16_t>), std::uint16_t);

  // std::uint8_t
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::uint8_t> ), std::uint8_t );
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::uint8_t, std::uint16_t>), std::uint16_t);

  // std::int16_t
  TTS_TYPE_IS((eve::common_type_t<std::int16_t, std::int16_t> ), std::int16_t );
  TTS_TYPE_IS((eve::common_type_t<std::int16_t, std::uint16_t>), std::uint16_t);
}

EVE_TEST_TYPES("eve::common_type for two types comutes", eve::test::scalar::all_types )
<typename T>(eve::as<T>)
{
  auto one_type = []<typename U> (eve::as<U>) {
    TTS_TYPE_IS((eve::common_type_t<T, U>), (eve::common_type_t<U, T>));
  };

  [&]<typename ...Us> (eve::detail::types<Us...>) {
    (one_type(eve::as<Us>{}), ...);
  }(eve::test::scalar::all_types);
};

EVE_TEST_TYPES("eve::common_type matches std::common_type", eve::test::scalar::all_types )
<typename T>(eve::as<T>)
{
  auto one_type = []<typename U> (eve::as<U>) {
    TTS_TYPE_IS((eve::common_type_t<T, U>), (std::common_type_t<T, U>));
  };

  [&]<typename ...Us> (eve::detail::types<Us...>) {
    (one_type(eve::as<Us>{}), ...);
  }(eve::detail::types<
    std::int32_t, std::uint32_t,
    std::int64_t, std::uint64_t,
    float       , double
  >{});
};

using i32_u32_f64 = kumi::tuple<std::int32_t, std::uint32_t, double>;
using i32_i32_i32 = kumi::tuple<std::int32_t, std::int32_t,  std::int32_t>;

using i32_x2    = kumi::tuple<std::int32_t, std::int32_t>;
using i32_x4    = kumi::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>;
using i32_x2_x2 = kumi::tuple<i32_x2, i32_x2>;

struct product : i32_u32_f64 {};
template<>              struct eve::is_product_type<product> : std::true_type {};
template<>              struct std::tuple_size<product>      : std::tuple_size<i32_u32_f64> {};
template<std::size_t I> struct std::tuple_element<I,product> : std::tuple_element<I, i32_u32_f64> {};

struct smaller_product : i32_i32_i32 {};
template<>              struct eve::is_product_type<smaller_product> : std::true_type {};
template<>              struct std::tuple_size<smaller_product>      : std::tuple_size<i32_i32_i32> {};
template<std::size_t I> struct std::tuple_element<I,smaller_product> : std::tuple_element<I, i32_i32_i32> {};

struct point : i32_x2 {};
template<>              struct eve::is_product_type<point> : std::true_type {};
template<>              struct std::tuple_size<point>      : std::tuple_size<i32_x2> {};
template<std::size_t I> struct std::tuple_element<I,point> : std::tuple_element<I, i32_x2> {};

using point_x2 = kumi::tuple<point, point>;

struct line : point_x2 {};

template<>              struct eve::is_product_type<line> : std::true_type {};
template<>              struct std::tuple_size<line>      : std::tuple_size<point_x2> {};
template<std::size_t I> struct std::tuple_element<I,line> : std::tuple_element<I, point_x2> {};

TTS_CASE("eve::common_type, product type")
{
  TTS_TYPE_IS(
    (eve::common_type_t<i32_u32_f64, i32_i32_i32>), i32_u32_f64);

  TTS_TYPE_IS((eve::common_type_t<product, i32_i32_i32>), product);
  TTS_TYPE_IS((eve::common_type_t<i32_i32_i32, product>), product);

  TTS_TYPE_IS((eve::common_type_t<product, i32_u32_f64>), product);
  TTS_TYPE_IS((eve::common_type_t<i32_u32_f64, product>), product);

  TTS_TYPE_IS((eve::common_type_t<product, smaller_product>), product);
  TTS_TYPE_IS((eve::common_type_t<smaller_product, product>), product);

  TTS_TYPE_IS((eve::common_type_t<point_x2, line>), line);
  TTS_TYPE_IS((eve::common_type_t<line, point_x2>), line);

  TTS_TYPE_IS((eve::common_type_t<line, i32_x4>), line);
  TTS_TYPE_IS((eve::common_type_t<i32_x4, line>), line);

  TTS_TYPE_IS((eve::common_type_t<line, i32_x2_x2>), line);
  TTS_TYPE_IS((eve::common_type_t<i32_x2_x2, line>), line);
}

TTS_CASE("eve::common_type, have_common_type")
{
  TTS_CONSTEXPR_EXPECT((eve::have_common_type<int, float>));
  TTS_CONSTEXPR_EXPECT((eve::have_common_type<product, smaller_product>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::have_common_type<kumi::tuple<int, int>,
                                                  kumi::tuple<int, int, int>>));
}

TTS_CASE("eve::common_type, reduction")
{
  TTS_TYPE_IS(
    (eve::common_type_t<std::int8_t, std::int16_t, std::int32_t>),
    std::int32_t
  );
  TTS_TYPE_IS(
    (eve::common_type_t<std::int32_t, std::int16_t, std::int8_t>),
    std::int32_t
  );
}

TTS_CASE("eve::common_type, generic constants")
{
  TTS_TYPE_IS(
    (eve::common_type_t<int, decltype(eve::zero)>),
    int
  );
  TTS_TYPE_IS(
    (eve::common_type_t<decltype(eve::zero), int>),
    int
  );
}
