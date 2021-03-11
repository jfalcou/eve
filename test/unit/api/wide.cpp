//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

auto linear_ramp = []<typename T>(eve::as_<T>, auto)
{
  std::array<eve::element_type_t<T>,eve::cardinal_v<T>> d;
  std::array<eve::logical<eve::element_type_t<T>>,eve::cardinal_v<T>> l;

  for(std::ptrdiff_t i = 0;i<T::size();++i)
  {
    d[i] = 1+i;
    l[i] = ((1+i)%2) == 0;
  }

  return std::make_tuple(d,l);
};

//==================================================================================================
// structured bindings support
//==================================================================================================
auto binding_tests  = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                                , T data, L logical_data
                                                )
{
  TTS_TYPE_IS( (typename std::tuple_element<0           , T>::type), eve::element_type_t<T>);
  TTS_TYPE_IS( (typename std::tuple_element<0           , L>::type), eve::element_type_t<L>);
  TTS_TYPE_IS( (typename std::tuple_element<T::size()-1 , T>::type), eve::element_type_t<T>);
  TTS_TYPE_IS( (typename std::tuple_element<T::size()-1 , L>::type), eve::element_type_t<L>);

  TTS_CONSTEXPR_EQUAL(std::tuple_size<T>::value, T::size());
  TTS_CONSTEXPR_EQUAL(std::tuple_size<L>::value, L::size());

  if constexpr(T::size() == 1)
  {
    auto [ a0 ] = data;
    auto [ l0 ] = logical_data;
    TTS_EQUAL(a0, data.get(0));
    TTS_EQUAL(l0, logical_data.get(0));
  }
  else  if constexpr(T::size() == 2)
  {
    auto [ a0, a1 ] = data;
    auto [ l0, l1 ] = logical_data;
    TTS_EQUAL(a0, data.get(0));
    TTS_EQUAL(a1, data.get(1));
    TTS_EQUAL(l0, logical_data.get(0));
    TTS_EQUAL(l1, logical_data.get(1));
  }
  else  if constexpr(T::size() == 4)
  {
    auto [ a0, a1, a2, a3 ] = data;
    auto [ l0, l1, l2, l3 ] = logical_data;
    TTS_EQUAL(a0, data.get(0));
    TTS_EQUAL(a1, data.get(1));
    TTS_EQUAL(a2, data.get(2));
    TTS_EQUAL(a3, data.get(3));
    TTS_EQUAL(l0, logical_data.get(0));
    TTS_EQUAL(l1, logical_data.get(1));
    TTS_EQUAL(l2, logical_data.get(2));
    TTS_EQUAL(l3, logical_data.get(3));
  }
  else  if constexpr(T::size() == 8)
  {
    auto [ a0, a1, a2, a3, a4, a5, a6, a7 ] = data;
    auto [ l0, l1, l2, l3, l4, l5, l6, l7 ] = logical_data;
    TTS_EQUAL(a0, data.get(0));
    TTS_EQUAL(a1, data.get(1));
    TTS_EQUAL(a2, data.get(2));
    TTS_EQUAL(a3, data.get(3));
    TTS_EQUAL(a4, data.get(4));
    TTS_EQUAL(a5, data.get(5));
    TTS_EQUAL(a6, data.get(6));
    TTS_EQUAL(a7, data.get(7));
    TTS_EQUAL(l0, logical_data.get(0));
    TTS_EQUAL(l1, logical_data.get(1));
    TTS_EQUAL(l2, logical_data.get(2));
    TTS_EQUAL(l3, logical_data.get(3));
    TTS_EQUAL(l4, logical_data.get(4));
    TTS_EQUAL(l5, logical_data.get(5));
    TTS_EQUAL(l6, logical_data.get(6));
    TTS_EQUAL(l7, logical_data.get(7));
  }
};

EVE_TEST_BED( "Check eve::wide support for structured bindings"
            , eve::test::simd::all_types
            , linear_ramp, binding_tests
            );

//==================================================================================================
// Construct from a list of values
//==================================================================================================
auto make_tests  = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                             , T ref, L logical_ref
                                             )
{
  T simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return T{(1+N)...};
            }( std::make_index_sequence<T::size()>());

  eve::logical<T>
  logical_simd  = [&]<std::size_t... N>(std::index_sequence<N...>)
            {
              return eve::logical<T>{((1+N)%2 == 0)...};
            }( std::make_index_sequence<L::size()>());

  TTS_EQUAL(simd        , ref         );
  TTS_EQUAL(logical_simd, logical_ref );
};

EVE_TEST_BED( "Check eve::wide enumerating constructor"
            , eve::test::simd::all_types
            , linear_ramp, make_tests
            );

//==================================================================================================
// Construct from a single value
//==================================================================================================
auto splat_tests  = []<typename T>( auto& runtime, bool verbose, auto const&, T)
{
  using l_t = eve::logical<eve::element_type_t<T>>;

  eve::logical<T> all_true([](auto, auto) { return true; } );
  eve::logical<T> all_false([](auto, auto) { return false; } );

  TTS_EQUAL(T(42), T([](auto, auto) { return 42; } ));

  TTS_EQUAL(eve::logical<T>(l_t{true}) , all_true );
  TTS_EQUAL(eve::logical<T>(true)      , all_true );
  TTS_EQUAL(eve::logical<T>(42)        , all_true );

  TTS_EQUAL(eve::logical<T>(l_t{false}) , all_false );
  TTS_EQUAL(eve::logical<T>(false)      , all_false );
  TTS_EQUAL(eve::logical<T>(0)          , all_false );
};

EVE_TEST_BED( "Check eve::wide splat constructor"
            , eve::test::simd::all_types
            , eve::test::no_data, splat_tests
            );

//==================================================================================================
// Raw storage access
//==================================================================================================
auto storage_tests  = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                                , T data, L logical_data
                                                )
{
  T ref;
  L logical_ref;

  auto const& st  = data.storage();
  auto const& lst = logical_data.storage();

  ref.storage()         = st;
  logical_ref.storage() = lst;

  TTS_EQUAL(data, ref);
  TTS_EQUAL(logical_data, logical_ref);

  TTS_EQUAL(data.front(), eve::element_type_t<T>(1)         );
  TTS_EQUAL(data.back() , eve::element_type_t<T>(T::size()) );

  TTS_EQUAL(logical_data.front(), false           );
  TTS_EQUAL(logical_data.back() , (L::size() != 1));

  T copy;
  std::copy( data.begin(), data.end(), copy.begin() );
  TTS_EQUAL(data, copy);
};

EVE_TEST_BED( "Check eve::wide raw storage handling"
            , eve::test::simd::all_types
            , linear_ramp, storage_tests
            );

//==================================================================================================
// Slice API
//==================================================================================================
auto slice_tests  = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                              , T d, L ld
                                              )
{
  if constexpr( T::size() > 1 )
  {
    {
      using split_t = typename eve::cardinal_t<T>::split_type;
      using ref_t   = typename T::template rescale<split_t>;

      auto [ low, high ] = d.slice();

      TTS_EQUAL(low                  , ref_t([&](auto i, auto  ) { return d.get(i);     } ) );
      TTS_EQUAL(high                 , ref_t([&](auto i, auto c) { return d.get(i + c); } ) );
      TTS_EQUAL(d.slice(eve::lower_) , ref_t([&](auto i, auto  ) { return d.get(i);     } ) );
      TTS_EQUAL(d.slice(eve::upper_) , ref_t([&](auto i, auto c) { return d.get(i + c); } ) );
    }
    {
      using split_t = typename eve::cardinal_t<T>::split_type;
      using ref_t   = typename L::template rescale<split_t>;

      auto [ low, high ] = ld.slice();

      TTS_EQUAL(low                   , ref_t([&](auto i, auto  ) { return ld.get(i);     } ) );
      TTS_EQUAL(high                  , ref_t([&](auto i, auto c) { return ld.get(i + c); } ) );
      TTS_EQUAL(ld.slice(eve::lower_) , ref_t([&](auto i, auto  ) { return ld.get(i);     } ) );
      TTS_EQUAL(ld.slice(eve::upper_) , ref_t([&](auto i, auto c) { return ld.get(i + c); } ) );
    }
  }
  else
  {
    TTS_PASS("Type is too small to be split.");
  }
};

EVE_TEST_BED( "Check eve::wide::slice behavior"
            , eve::test::simd::all_types
            , linear_ramp, slice_tests
            );

//==================================================================================================
// Combine API
//==================================================================================================
auto combine_tests  = []<typename T, typename L>( auto& runtime, bool verbose, auto const&
                                                , T d, L ld
                                                )
{
  using comb_t  = typename eve::cardinal_t<T>::combined_type;
  using ref_t   = typename T::template rescale<comb_t>;
  using lref_t  = typename L::template rescale<comb_t>;

  TTS_EQUAL( (ref_t{d,d})       , ref_t ( [=](auto i, auto c) { return  d.get(i % (c/2)); } ) );
  TTS_EQUAL( eve::combine(d,d)  , ref_t ( [=](auto i, auto c) { return  d.get(i % (c/2)); } ) );
  TTS_EQUAL( (lref_t{ld,ld})    , lref_t( [=](auto i, auto c) { return ld.get(i % (c/2)); } ) );

  TTS_EQUAL( eve::combine(ld,ld), lref_t( [=](auto i, auto c) { return ld.get(i % (c/2)); } ) );
};

EVE_TEST_BED( "Check eve::wide::combine behavior"
            , eve::test::simd::all_types
            , linear_ramp, combine_tests
            );
