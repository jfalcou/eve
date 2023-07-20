//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>

template <typename T>
auto prod(auto m,   std::array<T, 3> const & v)
{
  std::array<T, 3> r;
  for(size_t i=0; i < v.size(); ++i)
  {
    r[i] = m[i][0]*v[0]+m[i][1]*v[1]+m[i][2]*v[2];
  }
  return r;
}

// TTS_CASE_WITH ( "Check behavior of to_rotation_matrix on scalar"
//               , tts::bunch<eve::test::scalar::ieee_reals>
//               , tts::generate( tts::randoms(0.5, +1.0)
//                              , tts::randoms(0.5, +1.0)
//                              , tts::randoms(0.5, +1.0)
//                              , tts::randoms(0.5, +1.0)
//                              )
//               )
//   <typename T>(T const& a0, T const& a1, T const& a2, T const&  a3)
// {
//   using e_t =  typename T::value_type;
//   using q_t = eve::quaternion<e_t>;
//   using c_t = eve::complex<e_t>;
//   std::array<e_t, 3> v{1, 2, 3};
//   for(size_t i = 0; i < a0.size(); ++i)
//   {
//     auto q = eve::sign(q_t(a0[i], a1[i], a2[i], a3[i]));
//     auto q1 = q_t(a0[i], a1[i], a2[i], a3[i]);
//     q_t qv(0, v[0], v[1], v[2]);
//     auto res = eve::to_rotation_matrix(q, std::span(v), eve::Assume_normalized);
//     auto refq = q*qv*eve::conj(q);
//     std::array<e_t, 3> ref{eve::ipart(refq), eve::jpart(refq), eve::kpart(refq)};
//     auto res1 = eve::to_rotation_matrix(q1, std::span(v), eve::Normalize);
//     for(int j=0; j <3 ; ++j)
//     {
//       TTS_RELATIVE_EQUAL(res[j], ref[j], 0.0001);
//       TTS_RELATIVE_EQUAL(res1[j], ref[j], 0.0001);
//     }
//     auto c = eve::sign(c_t(a0[i], a1[i]));
//     auto q2= eve::sign(q_t(a0[i], a1[i], 0, 0));
//     auto refq2 = q2*qv*eve::conj(q2);
//     std::array<e_t, 3> ref2{eve::ipart(refq2), eve::jpart(refq2), eve::kpart(refq2)};
//     auto res2 = eve::to_rotation_matrix(c, std::span(v), eve::Normalize);
//     for(int j=0; j <3 ; ++j)
//     {
//       TTS_RELATIVE_EQUAL(res2[j], ref2[j], 0.0001);
//     }


//   }
// };

TTS_CASE_WITH ( "Check behavior of to_rotation_matrix on wide"
              , eve::test::simd::ieee_reals
              , tts::generate( tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             , tts::randoms(0.5, +1.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t =  eve::element_type_t<T> ;
  using wq_t = eve::wide<eve::quaternion<e_t>, eve::cardinal_t<T>>;
  std::array<T, 3> v{T(1), T(2), T(3)};
  auto q = eve::sign(wq_t(a0, a1, a2, a3));
  wq_t qv(0, v[0], v[1], v[2]);
  auto m = eve::to_rotation_matrix(q, eve::Assume_normalized);
  auto refq = q*qv*eve::conj(q);
  auto res  = prod(m, v);
  std::array<T, 3> ref{eve::ipart(refq), eve::jpart(refq), eve::kpart(refq)};
  for(int j=0; j <3 ; ++j)
  {
    TTS_RELATIVE_EQUAL(res[j], ref[j], 0.0001);
  }
  auto q1 = wq_t(a0, a1, a2, a3);
  auto m1 = eve::to_rotation_matrix(q1, eve::Normalize);
  auto res1  = prod(m1, v);
  for(int j=0; j <3 ; ++j)
  {
    TTS_RELATIVE_EQUAL(res1[j], ref[j], 0.0001);
  }
};
