//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <eve/memory/aligned_ptr.hpp>

//==================================================================================================
// Realigned load tests
//==================================================================================================
TTS_CASE_TPL( "Check conditional load to wide from realigned pointer", eve::test::simd::all_types_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::logical<eve::element_type_t<T>>;
  v_t const x = true;

  if constexpr(T::size() == eve::expected_width_v<v_t>)
  {
    auto ptr = eve::previous_aligned_address(&x);

    auto loaded = eve::load[eve::unsafe](ptr);
    TTS_EXPECT(eve::any(loaded == x));

    loaded = eve::load[eve::unsafe](ptr.get());
    TTS_EXPECT(eve::any(loaded == x));

    for (auto ignore_ptr = ptr.get(); (&x - ignore_ptr) < T::size(); --ignore_ptr)
    {
      loaded = eve::load[eve::unsafe][eve::ignore_first(ptr.get() - ignore_ptr)](ignore_ptr);
      TTS_EXPECT(eve::any(loaded == x));
    }
  }

  [&]<std::ptrdiff_t...N>( std::integer_sequence<std::ptrdiff_t,N...> )
  {
    auto test = [&]<std::ptrdiff_t A>(eve::lanes_t<A> n)
    {
      auto ptr = eve::previous_aligned_address(&x, n);
      auto loaded = eve::load[eve::unsafe](ptr, n);

      TTS_EXPECT(eve::any(loaded == x));

      for (auto ignore_ptr = ptr.get(); (&x - ignore_ptr) < n(); --ignore_ptr)
      {
        loaded = eve::load[eve::unsafe][eve::ignore_first(ptr.get() - ignore_ptr)](ignore_ptr, n);
        TTS_EXPECT(eve::any(loaded == x));
      }
    };

    (test(eve::lanes<(1<<N)>),...);
  }( std::make_integer_sequence<std::ptrdiff_t,7>{});
};
