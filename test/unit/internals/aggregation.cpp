//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/arch.hpp>

TTS_CASE("Check that aggregated_ ABI differs with architecture specificities" )
{
# if defined(SPY_SIMD_IS_X86_AVX512) || defined(EVE_SIMD_IS_ANY_FIXED_SVE)
  TTS_EXPECT_NOT( eve::aggregated_::is_wide_logical );
# else
  TTS_EXPECT( eve::aggregated_::is_wide_logical );
# endif
};

int aggregation_kind( eve::internal_wide_logical::aggregated_ ) { return +1; }
int aggregation_kind( eve::internal_bit_logical::aggregated_  ) { return -1; }

TTS_CASE("Check that aggregated_ ABI participates to function mangling" )
{
# if defined(SPY_SIMD_IS_X86_AVX512) || defined(EVE_SIMD_IS_ANY_FIXED_SVE)
  TTS_EQUAL( aggregation_kind(eve::aggregated_{}), -1);
# else
  TTS_EQUAL( aggregation_kind(eve::aggregated_{}), +1);
# endif
};

namespace eve
{
	template <typename Options>
	struct test_upgrade_t : strict_elementwise_callable<test_upgrade_t, Options>
	{
		template <typename T, typename N>
		wide<upgrade_t<T>, typename N::split_type> operator()(wide<T, N> a) const {
			return EVE_DISPATCH_CALL(a);
		}

		EVE_CALLABLE_OBJECT(test_upgrade_t, test_upgrade_);
	};

	template <typename Options>
	struct test_downgrade_t : strict_elementwise_callable<test_downgrade_t, Options>
	{
		template <typename T, typename N>
		wide<downgrade_t<T>, N> operator()(wide<T, N> a) const
		{
			return EVE_DISPATCH_CALL(a);
		}

		EVE_CALLABLE_OBJECT(test_downgrade_t, test_downgrade_);
	};

	template <typename Options>
	struct test_pt_t : strict_elementwise_callable<test_pt_t, Options>
	{
		template <typename T, typename N>
		zipped<wide<upgrade_t<T>, N>, wide<std::uint8_t, N>> operator()(wide<T, N> a, zipped<wide<T, N>, wide<T, N>> b) const
		{
			return EVE_DISPATCH_CALL(a, b);
		}

	EVE_CALLABLE_OBJECT(test_pt_t, test_pt_);
	};

	inline constexpr auto test_upgrade   = functor<test_upgrade_t>;
	inline constexpr auto test_downgrade = functor<test_downgrade_t>;
	inline constexpr auto test_pt        = functor<test_pt_t>;
}

namespace eve::detail
{
	template <callable_options O, typename T, typename N>
	wide<upgrade_t<T>, typename N::split_type> test_upgrade_(EVE_REQUIRES(cpu_), O const&, wide<T, N> v)
	{
		using r_t = wide<upgrade_t<T>, typename N::split_type>;
		using out_t = upgrade_t<T>;

		for (std::ptrdiff_t i = 1; i < v.size(); ++i)
		{
			TTS_EQUAL(v.get(i), T(v.get(i - 1) + 3));
		}

		return r_t{ [&](auto i, auto){ return out_t(v.get(i * 2)); } };
	}

	template <callable_options O, typename T, typename N>
	wide<downgrade_t<T>, N> test_downgrade_(EVE_REQUIRES(cpu_), O const&, wide<T, N> v)
	{
		return eve::convert(v, eve::as<downgrade_t<T>>{});
	}

	template <callable_options O, typename T, typename N>
	zipped<wide<upgrade_t<T>, N>, wide<std::uint8_t, N>> test_pt_(EVE_REQUIRES(cpu_), O const&, wide<T, N> a, zipped<wide<T, N>, wide<T, N>> b)
	{
		auto x = eve::convert(a, eve::as<upgrade_t<T>>{});
    auto [b0, b1] = b;
		auto y = eve::convert(b0 + b1, eve::as<std::uint8_t>{});
		return zip(x, y);
	}
}

TTS_CASE_TPL("aggregate stress test - upgrade", eve::test::simd::all_types)
<typename W0>(tts::type<W0>)
{
	using T = eve::element_type_t<W0>;
	using W = typename W0::combined_type;

	W a([](auto i, auto){ return T((i + 2) * 3); });
	auto r = eve::test_upgrade(tts::poison(a));

	for (std::ptrdiff_t i = 0; i < r.size(); ++i)
	{
		TTS_EQUAL(r.get(i), eve::upgrade_t<T>(T((i + 1) * 6)));
	}
};

TTS_CASE_TPL("aggregate stress test - downgrade", eve::test::simd::all_types)
<typename W0>(tts::type<W0>)
{
	using T = eve::element_type_t<W0>;
	using W = typename W0::combined_type;

	W a([](auto i, auto){ return T(i); });
	TTS_EQUAL(eve::test_downgrade(tts::poison(a)), eve::convert(a, eve::as<eve::downgrade_t<T>>{}));
};

TTS_CASE_TPL("aggregate stress test - product type", eve::test::simd::all_types)
<typename W0>(tts::type<W0>)
{
	using T = eve::element_type_t<W0>;
	using W = typename W0::combined_type;

	W a([](auto i, auto){ return T(i * 2 + 10); });
	W b0([](auto i, auto){ return T(i + 1); });
	W b1([](auto i, auto){ return T(i * 3); });

	auto [ra, rb] = eve::test_pt(tts::poison(a), eve::zip(tts::poison(b0), tts::poison(b1)));

	TTS_EQUAL(ra, eve::convert(a, eve::as<eve::upgrade_t<T>>{}));
	TTS_EQUAL(rb, eve::convert(b0 + b1, eve::as<std::uint8_t>{}));
};
