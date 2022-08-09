//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <array>
#include <list>

//==================================================================================================
// Conditionally load into wide from an aligned pointer
//==================================================================================================
TTS_CASE_WITH( "Check conditional load to wides from aligned pointer with alternatives"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(50))
        )
<typename T>(T others)
{
  using v_t     = eve::element_type_t<T>;
  using lanes_t = eve::cardinal_t<T>;

  auto [data  ,idx  ] = page<v_t, lanes_t>();

  auto ptr          = eve::as_aligned(&data[idx], lanes_t{});
  auto const_ptr    = eve::as_aligned((v_t const*)(ptr), lanes_t{});

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
    T full_ref(ptr);
    T ignore_last_ref   = eve::replace_ignored(full_ref,il,others);
    T ignore_first_ref  = eve::replace_ignored(full_ref,i1,others);
    T keep_first_ref    = eve::replace_ignored(full_ref,kf,others);
    T keep_last_ref     = eve::replace_ignored(full_ref,kl,others);
    T keep_between_ref  = eve::replace_ignored(full_ref,kb,others);
    T ignore_ext_ref    = eve::replace_ignored(full_ref,ie,others);

    // lanes value
    auto lanes = eve::lane<T::size()>;

    TTS_AND_THEN("load is applied on aligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ptr, lanes)                 , full_ref        );
      TTS_EQUAL((eve::load[il](ptr, lanes))                             , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](ptr, lanes))                             , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](ptr, lanes))                             , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](ptr, lanes))                             , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](ptr, lanes))                             , keep_between_ref);
      TTS_EQUAL((eve::load[ie](ptr, lanes))                             , ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](ptr, lanes) ) , others          );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](const_ptr, lanes)               , full_ref        );
      TTS_EQUAL((eve::load[il](const_ptr, lanes))                           , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](const_ptr, lanes))                           , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](const_ptr, lanes))                           , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](const_ptr, lanes))                           , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](const_ptr, lanes))                           , keep_between_ref);
      TTS_EQUAL((eve::load[ie](const_ptr, lanes))                           , ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](const_ptr, lanes)), others          );
    }

    if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
    {
      TTS_AND_THEN("load is applied on aligned pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](ptr)                , full_ref        );
        TTS_EQUAL((eve::load[il](ptr) )                           , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](ptr) )                           , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](ptr) )                           , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](ptr) )                           , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](ptr) )                           , keep_between_ref);
        TTS_EQUAL((eve::load[ie](ptr) )                           , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](ptr)) , others          );
      }

      TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](const_ptr)                , full_ref        );
        TTS_EQUAL((eve::load[il](const_ptr) )                           , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](const_ptr) )                           , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](const_ptr) )                           , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](const_ptr) )                           , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](const_ptr) )                           , keep_between_ref);
        TTS_EQUAL((eve::load[ie](const_ptr) )                           , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all.else_(others)](const_ptr)) , others          );
      }
    }
  }
};
