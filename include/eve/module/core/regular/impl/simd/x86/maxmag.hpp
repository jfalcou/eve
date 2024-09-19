
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> maxmag_(EVE_REQUIRES(avx512_),
                                     O          const & opts,

                                     wide<T, N> const & v0,
                                     wide<T, N> const & v1) noexcept requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic) || O::contains(saturated))
      return  maxmag.behavior(cpu_{}, opts, v0, v1);
    else
    {
      constexpr auto cat  = categorize<wide<T, N>>();
      constexpr auto ctrl = range_ctrl::absolute_max | range_ctrl::sign_from_cmp;
      // float
      if constexpr( cat == category::float32x4 ) return _mm_range_ps(v0, v1, ctrl);
      else if constexpr( cat == category::float32x8 ) return _mm256_range_ps(v0, v1, ctrl);
      else if constexpr( cat == category::float32x16 ) return _mm512_range_ps(v0, v1, ctrl);
      // double
      else if constexpr( cat == category::float64x2 ) return _mm_range_pd(v0, v1, ctrl);
      else if constexpr( cat == category::float64x4 ) return _mm256_range_pd(v0, v1, ctrl);
      else if constexpr( cat == category::float64x8 ) return _mm512_range_pd(v0, v1, ctrl);
      else return maxmag.behavior(cpu_{}, opts, v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> maxmag_(EVE_REQUIRES(avx512_),
                                     C          const &cx,
                                     O          const &opts,
                                     wide<T, N> const &v,
                                     wide<T, N> const &w) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(numeric) || O::contains(pedantic) || O::contains(saturated))
      return maxmag.behavior(cpu_{}, opts, v, w);
    else
    {
      constexpr auto c = categorize<wide<T, N>>();
      auto           src  = alternative(cx, v, as<wide<T, N>> {});
      auto           m    = expand_mask(cx, as<wide<T, N>> {}).storage().value;
      constexpr auto ctrl = range_ctrl::absolute_max | range_ctrl::sign_from_cmp;

      if constexpr( c == category::float32x16 ) return _mm512_mask_range_ps(src, m, v, w, ctrl);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_range_pd(src, m, v, w, ctrl);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_range_ps(src, m, v, w, ctrl);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_range_pd(src, m, v, w, ctrl);
      else if constexpr( c == category::float32x4 ) return _mm_mask_range_ps(src, m, v, w, ctrl);
      else if constexpr( c == category::float64x2 ) return _mm_mask_range_pd(src, m, v, w, ctrl);
      else return maxmag.behavior(cpu_{}, opts, v, w);
    }
  }
}
