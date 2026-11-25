//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/translation/common.hpp"

#include <eve/memory/stack_buffer.hpp>

template<typename Ptr> struct custom_source
{
  using value_type = eve::value_type_t<Ptr>;
  Ptr ptr;

  template<eve::callable_options O, typename W>
  auto load(O const& opts, eve::as<W> tgt) const
  {
    return eve::load[opts](ptr, tgt);
  }
};

template<typename W, typename E>
void check_loads(tts::type<W>, tts::type<E>)
{
  using T  = eve::element_type_t<W>;
  using WE = eve::wide<E, eve::lanes<W::size()>>;

  W nums{[](int i, int) { return i; }};
  eve::stack_buffer<W> buf;
  eve::store(nums, buf.ptr());
  auto ptr = (E const*) buf.ptr().get();

  W    alt_nums{(T) (W::size() + 1)};
  WE   alt      = eve::bit_cast(alt_nums, eve::as<WE>{});
  auto ignore   = eve::ignore_first(1).else_(alt);
  auto expected = eve::replace_ignored(nums, eve::ignore_first(1), alt_nums);

  auto const as_nums = [](WE v) { return eve::bit_cast(v, eve::as<W>{}); };

  TTS_EQUAL(as_nums(eve::load(ptr, eve::as<WE>{})), nums);
  TTS_EQUAL(as_nums(eve::load[ignore](ptr, eve::as<WE>{})), expected);

  custom_source<decltype(ptr)> src{ptr};
  TTS_EQUAL(as_nums(eve::load(src, eve::as<WE>{})), nums);
  TTS_EQUAL(as_nums(eve::load[ignore](src, eve::as<WE>{})), expected);
}

TTS_CASE_TPL("Translatable - load from a pointer and a custom source", eve::test::simd::all_types)
<typename W>(tts::type<W>)
{
  using T = eve::element_type_t<W>;

  if constexpr (std::integral<T>)
  {
    enum class E : T {};
    check_loads(tts::type<W>{}, tts::type<E>{});
  }

  check_loads(tts::type<W>{}, tts::type<BaseStruct<T>>{});
};
