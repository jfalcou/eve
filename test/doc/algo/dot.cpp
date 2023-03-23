#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <numeric>
#include <vector>
#include "print.hpp"

int main()
{
//   {
//     using e_t = float;
//     eve::algo::soa_vector<e_t>  v1 = {e_t(1.0f), e_t(2.0f), e_t(3.0f), e_t(4.0f)};
//     eve::algo::soa_vector<e_t>  v2 = {e_t(1.0f), e_t(-2.0f), e_t(3.0f), e_t(-4.0f)};
//     eve::algo::soa_vector<e_t>  r(4);

//     std::cout << " -> v1                                                                                                                        = "
//               << tts::as_string(v1)
//               << "\n";
//     std::cout << " -> v2                                                                                                                        = "
//               << tts::as_string(v2)
//               << "\n";

//     std::cout << " -> eve::algo::transform_to(eve::views::zip(v1, v2), r, [](auto x1, auto x2) { return x1*x2 })\n";
//     eve::algo::transform_to(eve::views::zip(v1, v2), r, [](auto x) { auto [x1, x2] = x; return x1*x2; });
//     doc_utils::print(r);
//     std::cout << eve::algo::reduce(r, e_t(0)) << std::endl;

//     auto d = eve::algo::transform_reduce(eve::views::zip(v1, v2), [](auto x) { auto [x1, x2] = x; return x1*x2; }, e_t(0));
//     std::cout << d << std::endl;
//   }
  {
    using e_t = eve::complex < float>;
    eve::algo::soa_vector<e_t>  v1 = {e_t(1.0f, 0.5), e_t(2.0f), e_t(3.0f), e_t(4.0f)};
    eve::algo::soa_vector<e_t>  v2 = {e_t(1.0f, 2.0), e_t(-2.0f), e_t(3.0f), e_t(-4.0f)};
    eve::algo::soa_vector<e_t>  r(4);

    std::cout << " -> v1                                                                                                                        = "
              << tts::as_string(v1)
              << "\n";
    std::cout << " -> v2                                                                                                                        = "
              << tts::as_string(v2)
              << "\n";

    std::cout << " -> eve::algo::transform_to(eve::views::zip(v1, v2), r, [](auto x1, auto x2) { return x1*x2 })\n";
    eve::algo::transform_to(eve::views::zip(v1, v2), r, [](auto x) { auto [x1, x2] = x; return x1*eve::conj(x2); });
    doc_utils::print(r);
    std::cout << eve::algo::reduce(r, e_t(0)) << std::endl;

    auto d = eve::algo::transform_reduce(eve::views::zip(v1, v2), [](auto x) { auto [x1, x2] = x; return x1*eve::conj(x2); }, e_t(0));
    std::cout << d << std::endl;
  }

//   std::cout << " -> eve::algo::transform_reduce(eve::views::zip(v1, v2), [](auto x1, auto x2) { return x1*x2 }, 0.f)                                                         = "
//             << eve::algo::transform_reduce(eve::views::zip(v1, v2), [](auto x1, auto x2) { return x1*x2; }, 0.) << "\n";


}
