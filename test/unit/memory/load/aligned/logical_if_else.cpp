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
#include <eve/function/any.hpp>
#include <eve/function/load.hpp>
#include <eve/constant/false.hpp>
#include <array>
#include <list>

//==================================================================================================
// Conditionally load into wide from an aligned pointer
//==================================================================================================
auto aligned_tests = []<typename T>(T others)
{
  using v_t = eve::element_type_t<typename T::mask_type>;
  using e_t = eve::element_type_t<T>;
  constexpr std::ptrdiff_t l_algt = eve::alignment_v<T>;

  auto [ldata ,lidx ] = logical_page<v_t, eve::fixed<T::size()>>();

  auto l_ptr        = eve::as_aligned<l_algt>(&ldata[lidx]);
  auto l_const_ptr  = eve::as_aligned<l_algt>((e_t const*)(&ldata[lidx]));

  TTS_WHEN("For some given relative masks")
  {
    // Conditional selectors
    auto il = eve::ignore_last(T::size()/4).else_(others);
    auto i1 = eve::ignore_first(T::size()/4).else_(others);
    auto kf = eve::keep_first(T::size()/4).else_(others);
    auto kl = eve::keep_last(T::size()/4).else_(others);
    auto kb = eve::keep_between ( std::min(std::ptrdiff_t(0),std::ptrdiff_t(T::size()/3))
                                , std::max(std::ptrdiff_t(0),std::ptrdiff_t((T::size()*2)/3))
                                ).else_(others);

    auto ie = (i1 && il).else_(others);

    // Reference values
    T l_full_ref(l_ptr);
    T l_ignore_last_ref   = eve::replace_ignored(l_full_ref,il,others);
    T l_ignore_first_ref  = eve::replace_ignored(l_full_ref,i1,others);
    T l_keep_first_ref    = eve::replace_ignored(l_full_ref,kf,others);
    T l_keep_last_ref     = eve::replace_ignored(l_full_ref,kl,others);
    T l_keep_between_ref  = eve::replace_ignored(l_full_ref,kb,others);
    T l_ignore_ext_ref    = eve::replace_ignored(l_full_ref,ie,others);

    // lanes value
    auto lanes = eve::lane<T::size()>;

    using eve::false_;

    TTS_AND_THEN("load is applied on aligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](l_ptr, lanes)   , l_full_ref          );
      TTS_EQUAL((eve::load[il](l_ptr, lanes))               , l_ignore_last_ref   );
      TTS_EQUAL((eve::load[i1](l_ptr, lanes))               , l_ignore_first_ref  );
      TTS_EQUAL((eve::load[kf](l_ptr, lanes))               , l_keep_first_ref    );
      TTS_EQUAL((eve::load[kl](l_ptr, lanes))               , l_keep_last_ref     );
      TTS_EQUAL((eve::load[kb](l_ptr, lanes))               , l_keep_between_ref  );
      TTS_EQUAL((eve::load[ie](l_ptr, lanes))               , l_ignore_ext_ref    );
      TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](l_ptr, lanes) ) , others              );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](l_const_ptr, lanes) , l_full_ref        );
      TTS_EQUAL((eve::load[il](l_const_ptr, lanes))             , l_ignore_last_ref );
      TTS_EQUAL((eve::load[i1](l_const_ptr, lanes))             , l_ignore_first_ref);
      TTS_EQUAL((eve::load[kf](l_const_ptr, lanes))             , l_keep_first_ref  );
      TTS_EQUAL((eve::load[kl](l_const_ptr, lanes))             , l_keep_last_ref   );
      TTS_EQUAL((eve::load[kb](l_const_ptr, lanes))             , l_keep_between_ref);
      TTS_EQUAL((eve::load[ie](l_const_ptr, lanes))             , l_ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](l_const_ptr, lanes)), others            );
    }

    if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
    {
      TTS_AND_THEN("load is applied on aligned pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](l_ptr)                , l_full_ref        );
        TTS_EQUAL((eve::load[il](l_ptr))                            , l_ignore_last_ref );
        TTS_EQUAL((eve::load[i1](l_ptr))                            , l_ignore_first_ref);
        TTS_EQUAL((eve::load[kf](l_ptr))                            , l_keep_first_ref  );
        TTS_EQUAL((eve::load[kl](l_ptr))                            , l_keep_last_ref   );
        TTS_EQUAL((eve::load[kb](l_ptr))                            , l_keep_between_ref);
        TTS_EQUAL((eve::load[ie](l_ptr))                            , l_ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](l_ptr)) , others            );
      }

      TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](l_const_ptr)                , l_full_ref        );
        TTS_EQUAL((eve::load[il](l_const_ptr) )                           , l_ignore_last_ref );
        TTS_EQUAL((eve::load[i1](l_const_ptr) )                           , l_ignore_first_ref);
        TTS_EQUAL((eve::load[kf](l_const_ptr) )                           , l_keep_first_ref  );
        TTS_EQUAL((eve::load[kl](l_const_ptr) )                           , l_keep_last_ref   );
        TTS_EQUAL((eve::load[kb](l_const_ptr) )                           , l_keep_between_ref);
        TTS_EQUAL((eve::load[ie](l_const_ptr) )                           , l_ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](l_const_ptr)) , others            );
      }
    }
  }
};

EVE_TEST_BED( "Check load to logical from aligned pointer with alternatives"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::logicals(1,2))
            , aligned_tests
            );
