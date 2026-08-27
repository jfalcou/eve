//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/eve.hpp>
#include <eve/module/math.hpp>
#include <span>

//==================================================================================================
// A 1D bilateral filter. Every sample becomes a weighted average of its neighbours, the weight
// decreasing both with distance and with intensity difference. That second term is what preserves
// edges - and what makes the filter interesting to vectorize, as the weights depend on the data.
//
// Both versions take the exponential as a parameter so the very same code can be run with
// std::exp, eve::exp or eve::exp[eve::raw].
//==================================================================================================
namespace bilateral
{
  inline constexpr int   radius  = 5;
  inline constexpr float sigma_s = 3.0f;
  inline constexpr float sigma_i = 0.5f;

  //! [scalar]
  template<typename ExpFunc>
  void filter_scalar(std::span<float const> in, std::span<float> out, ExpFunc exp_func)
  {
    int   n     = static_cast<int>(in.size());
    float var_s = 2.0f * sigma_s * sigma_s;
    float var_i = 2.0f * sigma_i * sigma_i;

    for(int i = radius; i < n - radius; ++i)
    {
      float sum        = 0.0f;
      float weight_sum = 0.0f;

      for(int j = -radius; j <= radius; ++j)
      {
        float spatial_diff   = static_cast<float>(j * j);
        float val_j          = in[i + j];
        float intensity_diff = (in[i] - val_j) * (in[i] - val_j);
        float weight         = exp_func(-(spatial_diff / var_s + intensity_diff / var_i));

        sum        += val_j * weight;
        weight_sum += weight;
      }

      out[i] = sum / weight_sum;
    }
  }
  //! [scalar]

  //! [simd]
  template<typename ExpFunc>
  void filter_simd(std::span<float const> in, std::span<float> out, ExpFunc eve_exp)
  {
    int   n     = static_cast<int>(in.size());
    float var_s = 2.0f * sigma_s * sigma_s;
    float var_i = 2.0f * sigma_i * sigma_i;

    using w_t = eve::wide<float>;
    int N     = w_t::size();

    int end_simd = (n - radius) - N;
    int i        = radius;

    for(; i <= end_simd; i += N)
    {
      w_t img_i(&in[i]);
      w_t sum(0.0f);
      w_t weight_sum(0.0f);

      for(int j = -radius; j <= radius; ++j)
      {
        float spatial_diff = static_cast<float>(j * j);
        w_t   val_j(&in[i + j]);

        w_t intensity_diff = (img_i - val_j) * (img_i - val_j);
        w_t weight         = eve_exp(-(spatial_diff / var_s + intensity_diff / var_i));

        sum        += val_j * weight;
        weight_sum += weight;
      }

      eve::store(sum / weight_sum, &out[i]);
    }

    // Whatever does not fill a full register is finished off one sample at a time.
    if(i < n - radius)
    {
      std::size_t tail = static_cast<std::size_t>(i - radius);
      filter_scalar(in.subspan(tail), out.subspan(tail), eve_exp);
    }
  }
  //! [simd]
}
