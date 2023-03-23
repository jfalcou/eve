#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  {
    std::vector<double>  v = {2.5,6.8,10.62,3.2,8.8,2.7,6.66,8.5,2.01,4.8};

    std::cout << " -> v                                    = ";
    doc_utils::print(v);

    std::cout << " -> eve::views::map(v, eve::sqrt)        = ";
    doc_utils::print(eve::views::map(v, eve::sqrt));

    std::cout << R"( -> eve::views::map ( v, [](auto x)
                         {
                           return convert(sqrt(x), as<int>{});
                         }
                    )  = )";
    doc_utils::print( eve::views::map ( v
                                      , [](auto x)
                                        {
                                          return eve::convert(eve::sqrt(x), eve::as<int>{});
                                        }
                                      )
                  );
  }
  {
    std::cout << std::endl;
    using c_t = eve::complex<double>;
    eve::algo::soa_vector<c_t>  v = {c_t(-2.5),c_t(6.8),c_t(10.62),c_t(3.2),c_t(8.8),c_t(2.7),c_t(6.66),c_t(8.5),c_t(2.01),c_t(4.8)};

    std::cout << " -> v                                    = ";
    doc_utils::print(v);

    std::cout << " -> eve::views::map(v, eve::sqrt)        = ";
    doc_utils::print(eve::views::map(v, eve::sqrt));

    std::cout << R"( -> eve::views::map ( v, [](auto x)
                         {
                           return sqrt(x);
                         }
                    )  = )";
    doc_utils::print( eve::views::map ( v
                                      , [](auto x)
                                        {
                                          return eve::sqrt(x);
                                        }
                                      )
                    );
  }
  return 0;
}
