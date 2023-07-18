#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>

#include <numeric>
#include <iostream>
#include <utility>
#include <vector>

#include <tts/tts.hpp>

void
basic_example()
{
  std::cout << "basic =================\n";

  std::vector<int> v1 {1, 3, 5, 7};
  std::vector<int> v2 {2, 3, 4, 5, 6};
  std::vector<int> r;

  /*
   * The basic case, where output has guaranteed enough space
   * for the intersected elements.
   *
   * We will see all of the common elements in the output.
   * in1, in2 equal to the v1.end(), v2.end()
   */
  r.resize(v1.size());
  r.erase(eve::algo::set_intersection(v1, v2, r).out, r.end());
  TTS_EQUAL(r, (std::vector{3, 5}));

  std::cout << "-> v1:" << tts::as_string(v1) << '\n';
  std::cout << "-> v2:" << tts::as_string(v2) << '\n';
  std::cout << "-> r: " << tts::as_string(r) << '\n';
}

void not_enough_space_example()
{
  std::cout << "not enough space ====================\n";

  std::vector<int> v1 {1, 3, 5, 7};
  std::vector<int> v2 {2, 3, 4, 5, 6};
  std::vector<int> r;

  /*
   * The not enough space case - we will stop whe the output
   * runs out.
   *
   * in1 and in2 will be after the last common element.
   */
  r.resize(1);
  auto [in1, in2, out] = eve::algo::set_intersection(v1, v2, r);

  TTS_EQUAL(r, std::vector{3});
  TTS_EQUAL(*in1, 5);
  TTS_EQUAL(*in2, 4);
  TTS_EQUAL(out, r.end());

  std::cout << "r:             " << tts::as_string(r) << "\n";
  std::cout << "*in1:          " << *in1 << "\n";
  std::cout << "*in2:          " << *in2 << "\n";
  std::cout << "out == r.end() " << tts::as_string(out == r.end()) << "\n";
}

void
pairs_example()
{
  std::cout << "mixing types, custom predicate =================\n";

  /*
   * Example that does set_union for tuples and integers.
   */

  using pair_t = kumi::tuple<int, double>;

  eve::algo::soa_vector<pair_t> pairs {{0, 1.1f}, {2, 2.2f}, {3, 3.3f}, {4, 4.4f}};
  std::vector<int>              scalars {2, 4};

  eve::algo::soa_vector<pair_t> r;
  r.resize(pairs.size());

  auto project = []<typename T>(T a) {
    if constexpr (eve::like<T, pair_t>) return get<0>(a);
    else return a;
  };

  /*
   * Unfortunately, unlike std::set_intersect, we for now require that
   * the callback applies both ways.
   * FIX-1631
   */
  auto lt = [&](auto a, auto b) {
    return project(a) < project(b);
  };

  auto eq = [&](auto a, auto b) {
    return project(a) == project(b);
  };

  r.erase(eve::algo::set_intersection(pairs, scalars, r, lt, eq).out, r.end());

  eve::algo::soa_vector<pair_t> r_expected {{2, 2.2f}, {4, 4.4f}};
  TTS_EQUAL(r, r_expected);

  std::cout << "-> pairs:   " << tts::as_string(pairs) << '\n';
  std::cout << "-> sclaras: " << tts::as_string(scalars) << '\n';
  std::cout << "-> r:       " << tts::as_string(r) << '\n';
}

void
different_scalar_types_example()
{
  std::cout << "different_scalar_types =================\n";

  std::vector<double> f64 {10.1, 20, 30.3, 40.4};
  std::vector<int>    i32 {20, 40};

  // We will convert from the intersection to the output type
  std::vector<float> r0(5u, 0.0);

  // We will use eve::common_type for comparisons between different types
  // if predicates are defaulted.
  r0.erase(eve::algo::set_intersection(f64, i32, r0).out, r0.end());
  TTS_EQUAL(r0, std::vector<float>{20});

  auto project = [](auto a) {
    return eve::convert(a, eve::as<std::int64_t>{}) / 10;
  };

  auto lt = [&](auto a, auto b) {
    return project(a) < project(b);
  };

  auto eq = [&](auto a, auto b) {
    return project(a) == project(b);
  };

  // The output is always copied from the first range, so r1, r2 will give
  // different results.
  std::vector<float> r1(5u, 0.0);
  r1.erase(eve::algo::set_intersection(f64, i32, r1, lt, eq).out, r1.end());
  TTS_EQUAL(r1, (std::vector<float>{20, 40.4}));

  std::vector<float> r2(5u, 0.0);
  r2.erase(eve::algo::set_intersection(i32, f64, r2, lt, eq).out, r2.end());
  TTS_EQUAL(r2, (std::vector<float>{20, 40}));

  std::cout << "-> f64: " << tts::as_string(f64) << '\n';
  std::cout << "-> i32: " << tts::as_string(i32) << '\n';
  std::cout << "-> r0:  " << tts::as_string(r0) << '\n';
  std::cout << "-> r1:  " << tts::as_string(r1) << '\n';
  std::cout << "-> r2:  " << tts::as_string(r2) << '\n';
}

void
biase_example()
{
  std::cout << "smaller range hint =================\n";
  std::vector<int> v1(1000u, 0), v2{531, 917};
  std::iota(v1.begin(), v1.end(), 0);

  std::vector<int> r0{0, 1}, r1{0, 1};

  eve::algo::set_intersection[eve::algo::expect_smaller_range<0>](v1, v2, r0);
  eve::algo::set_intersection[eve::algo::expect_smaller_range<1>](v2, v1, r1);

  TTS_EQUAL(r0, v2);
  TTS_EQUAL(r1, v2);

  std::cout << "-> r0:  " << tts::as_string(r0) << '\n';
  std::cout << "-> r1:  " << tts::as_string(r1) << '\n';
}

int
main()
{
  basic_example();
  not_enough_space_example();
  pairs_example();
  different_scalar_types_example();
  biase_example();
}
