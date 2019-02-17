#include <eve/function/add.hpp>
#include <eve/literals.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace eve::literal;
  eve::wide<float> w( [](int i, int) { return 1.f+i; } );

  std::cout << "add(3.f, 5.5f) = " << eve::add(3.f,5.5f) << '\n';
  std::cout << "add({3,3,3,3}, {1,2,3,4}) = " << eve::add(3._wf, w ) << '\n';
}
