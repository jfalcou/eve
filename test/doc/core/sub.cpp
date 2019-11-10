#include <eve/function/sub.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace eve::literal;
  eve::wide<float, eve::fixed<4>> w([](auto i, auto) { return 1.f + i; });

  std::cout << "sub(3.f, 5.5f) = " << eve::sub(3.f, 5.5f) << '\n';
  std::cout << "sub({3,3,3,3}, {1,2,3,4}) = " << eve::sub(3.0f, w) << '\n';
}
