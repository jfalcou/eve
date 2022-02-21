//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/regular/load.hpp>
#include <eve/module/core/regular/any.hpp>
#include <array>
#include <list>

//==================================================================================================
// Conditionally load into wide from an aligned pointer
//==================================================================================================
EVE_TEST_TYPES( "Check conditional load to wides from aligned pointer", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t     = eve::element_type_t<T>;
  using lanes_t = eve::cardinal_t<T>;

  auto [data  ,idx  ] = page<v_t, lanes_t>();

  auto ptr          = eve::as_aligned(&data[idx], lanes_t{});
  auto const_ptr    = eve::as_aligned((v_t const*)(ptr), lanes_t{});

  TTS_WHEN("For some given relative masks")
  {
    // Conditional selectors
    auto il = eve::ignore_last(T::size()/4);
    auto i1 = eve::ignore_first(T::size()/4);
    auto kf = eve::keep_first(T::size()/4);
    auto kl = eve::keep_last(T::size()/4);
    auto kb = eve::keep_between ( std::min(std::ptrdiff_t(0),std::ptrdiff_t(T::size()/3))
                                , std::max(std::ptrdiff_t(0),std::ptrdiff_t((T::size()*2)/3))
                                );

    auto ie = i1 && il;

    // Conditional selectors' masks
    auto ml   = il.mask( eve::as<T>() );
    auto m1   = i1.mask( eve::as<T>() );
    auto mkf  = kf.mask( eve::as<T>() );
    auto mkl  = kl.mask( eve::as<T>() );
    auto mkb  = kb.mask( eve::as<T>() );
    auto mie  = ie.mask( eve::as<T>() );
    auto mia  = eve::ignore_all.mask( eve::as<T>() );

    // Reference values
    T full_ref(ptr);
    T ignore_last_ref   = full_ref & ml.mask();
    T ignore_first_ref  = full_ref & m1.mask();
    T keep_first_ref    = full_ref & mkf.mask();
    T keep_last_ref     = full_ref & mkl.mask();
    T keep_between_ref  = full_ref & mkb.mask();
    T ignore_ext_ref    = full_ref & mie.mask();

    // lanes value
    auto lanes = eve::lane<T::size()>;

    TTS_AND_THEN("load is applied on aligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ptr, lanes)               , full_ref          );
      TTS_EQUAL((eve::load[il](ptr  , lanes) &  ml.mask() )           , ignore_last_ref   );
      TTS_EQUAL((eve::load[i1](ptr  , lanes) &  m1.mask() )           , ignore_first_ref  );
      TTS_EQUAL((eve::load[kf](ptr  , lanes) &  mkf.mask())           , keep_first_ref    );
      TTS_EQUAL((eve::load[kl](ptr  , lanes) &  mkl.mask())           , keep_last_ref     );
      TTS_EQUAL((eve::load[kb](ptr  , lanes) &  mkb.mask())           , keep_between_ref  );
      TTS_EQUAL((eve::load[ie](ptr  , lanes) &  mie.mask())           , ignore_ext_ref    );
      TTS_EQUAL((eve::load[eve::ignore_all](ptr, lanes) & mia.mask()) , T{0}              );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](const_ptr, lanes)               , full_ref        );
      TTS_EQUAL((eve::load[il](const_ptr, lanes) & ml.mask() )              , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](const_ptr, lanes) & m1.mask() )              , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](const_ptr, lanes) & mkf.mask())              , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](const_ptr, lanes) & mkl.mask())              , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](const_ptr, lanes) & mkb.mask())              , keep_between_ref);
      TTS_EQUAL((eve::load[ie](const_ptr, lanes) & mie.mask())              , ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all](const_ptr, lanes) & mia.mask()) , T{0}            );
    }

    if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
    {
      TTS_AND_THEN("load is applied on aligned pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](ptr)              , full_ref        );
        TTS_EQUAL((eve::load[il](ptr) & ml.mask() )             , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](ptr) & m1.mask() )             , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](ptr) & mkf.mask())             , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](ptr) & mkl.mask())             , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](ptr) & mkb.mask())             , keep_between_ref);
        TTS_EQUAL((eve::load[ie](ptr) & mie.mask())             , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all](ptr) & mia.mask()), T{0}            );
      }

      TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](const_ptr)              , full_ref        );
        TTS_EQUAL((eve::load[il](const_ptr) & ml.mask() )             , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](const_ptr) & m1.mask() )             , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](const_ptr) & mkf.mask())             , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](const_ptr) & mkl.mask())             , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](const_ptr) & mkb.mask())             , keep_between_ref);
        TTS_EQUAL((eve::load[ie](const_ptr) & mie.mask())             , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all](const_ptr) & mia.mask()), T{0}            );
      }
    }
  }
};

//==================================================================================================
// Realigned load tests
//==================================================================================================
EVE_TEST_TYPES( "Check conditional load to wide from realigned pointer", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  v_t const x = 123;

  if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
  {
    auto ptr = eve::previous_aligned_address(&x);

    auto loaded = eve::unsafe(eve::load)(ptr);
    TTS_EXPECT(eve::any(loaded == x));

    loaded = eve::unsafe(eve::load)(ptr.get());
    TTS_EXPECT(eve::any(loaded == x));

    for (auto ignore_ptr = ptr.get(); (&x - ignore_ptr) < T::size(); --ignore_ptr)
    {
      loaded = eve::unsafe(eve::load[eve::ignore_first(ptr.get() - ignore_ptr)])(ignore_ptr);
      TTS_EXPECT(eve::any(loaded == x));
    }
  }

  [&]<std::ptrdiff_t...N>( std::integer_sequence<std::ptrdiff_t,N...> )
  {
    auto test = [&]<std::ptrdiff_t A>(eve::fixed<A> n)
    {
      auto ptr = eve::previous_aligned_address(&x, n);
      auto loaded = eve::unsafe(eve::load)(ptr, n);

      TTS_EXPECT(eve::any(loaded == x));

      for (auto ignore_ptr = ptr.get(); (&x - ignore_ptr) < n(); --ignore_ptr)
      {
        loaded = eve::unsafe(eve::load[eve::ignore_first(ptr.get() - ignore_ptr)])(ignore_ptr, n);
        TTS_EXPECT(eve::any(loaded == x));
      }
    };

    (test(eve::lane<(1<<N)>),...);
  }( std::make_integer_sequence<std::ptrdiff_t,7>{});
};
