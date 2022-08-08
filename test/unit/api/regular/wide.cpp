//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// Construct from a list of values
//==================================================================================================
TTS_CASE_WITH( "Check eve::wide enumerating constructor"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T ref, L logical_ref)
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

  // Test smaller size wide for non-garbage
  using v_t = typename T::value_type;
  if constexpr( T::size() < eve::fundamental_cardinal_v<v_t> && !eve::has_emulated_abi_v<T> )
  {
    using w_t   = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;
    using wl_t  = eve::as_logical_t<w_t>;

    w_t  fsimd(simd.storage());
    wl_t flogical(logical_simd.storage());

    for(std::ptrdiff_t i = T::size(); i < w_t::size();++i)
    {
      TTS_EQUAL(fsimd.get(i), v_t(0));
      TTS_EQUAL(flogical.get(i), false);
    }
  }
};

//==================================================================================================
// Construct from a single value
//==================================================================================================
TTS_CASE_TPL( "Check eve::wide splat constructor", eve::test::simd::all_types)
<typename T>(tts::type<T>)
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


  // Test smaller size wide for non-garbage
  using v_t = typename T::value_type;
  if constexpr( T::size() < eve::fundamental_cardinal_v<v_t> && !eve::has_emulated_abi_v<T> )
  {
    using w_t   = eve::as_wide_t<v_t, eve::fundamental_cardinal_t<v_t>>;
    using wl_t  = eve::as_logical_t<w_t>;

    w_t  fsimd(T(42).storage());
    wl_t flogical(eve::logical<T>(true).storage());

    for(std::ptrdiff_t i = T::size(); i < w_t::size();++i)
    {
      TTS_EQUAL(fsimd.get(i), v_t(0));
      TTS_EQUAL(flogical.get(i), false);
    }
  }
};

//==================================================================================================
// Raw storage access
//==================================================================================================
TTS_CASE_WITH( "Check eve::wide raw storage handling"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T data, L logical_data)
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
};

//==================================================================================================
// Slice API
//==================================================================================================
TTS_CASE_WITH( "Check eve::wide::slice behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T d, L ld)
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
    TTS_PASS("Type is too half_c to be split.");
  }
};

//==================================================================================================
// Combine API
//==================================================================================================
TTS_CASE_WITH( "Check eve::wide::combine behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1),tts::logicals(1,2))
        )
<typename T, typename L>(T d, L ld)
{
  if constexpr(T::size() < 64)
  {
    using comb_t  = typename eve::cardinal_t<T>::combined_type;
    using ref_t   = typename T::template rescale<comb_t>;
    using lref_t  = typename L::template rescale<comb_t>;

    TTS_EQUAL( (ref_t{d,d})       , ref_t ( [=](auto i, auto c) { return  d.get(i % (c/2)); } ) );
    TTS_EQUAL( eve::combine(d,d)  , ref_t ( [=](auto i, auto c) { return  d.get(i % (c/2)); } ) );
    TTS_EQUAL( (lref_t{ld,ld})    , lref_t( [=](auto i, auto c) { return ld.get(i % (c/2)); } ) );

    TTS_EQUAL( eve::combine(ld,ld), lref_t( [=](auto i, auto c) { return ld.get(i % (c/2)); } ) );
  }
  else
  {
    TTS_PASS("No combine for 512 bits char wide");
  }
};
