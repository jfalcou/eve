#include <cfenv>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
// #pragma STDC FENV_ACCESS ON

int main()
{
    static constexpr std::pair<const char*, const double> samples[]
    {
        {" 12.0", 12.0},  {" 12.1", 12.1}, {"-12.1", -12.1}, {" 12.5", 12.5},
        {"-12.5", -12.5}, {" 12.9", 12.9}, {"-12.9", -12.9}, {" 13.0", 13.0}
    };

    std::cout <<
        "| sample |  FE_DOWNWARD  |   FE_UPWARD   | FE_TONEAREST  | FE_TOWARDZERO |\n";

    for (const auto& [str, fp] : samples)
    {
        std::cout << "| " << std::setw(6) << str << " |  ";
        for (const int dir : {FE_DOWNWARD, FE_UPWARD, FE_TONEAREST, FE_TOWARDZERO})
        {
            std::fesetround(dir);
            std::cout << std::setw(10) << std::fixed << std::nearbyint(fp) << "   |  ";
        }
        std::cout << '\n';
    }
}
