/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "E.V.E", "index.html", [
    [ "The Expressive Vector Engine", "index.html", "index" ],
    [ "Installation & Quick Start", "install.html", [
      [ "Pre-requisites", "install.html#autotoc_md101", null ],
      [ "Retrieving the source", "install.html#autotoc_md102", [
        [ "Github", "install.html#autotoc_md103", null ],
        [ "CPM", "install.html#autotoc_md104", null ],
        [ "SPACK", "install.html#autotoc_md105", null ],
        [ "AUR", "install.html#autotoc_md106", null ],
        [ "Conan", "install.html#autotoc_md107", null ],
        [ "VCPKG", "install.html#autotoc_md108", null ]
      ] ],
      [ "Installation from Source", "install.html#autotoc_md109", [
        [ "Setting up the Library", "install.html#autotoc_md110", null ],
        [ "Building the Documentation", "install.html#autotoc_md111", null ]
      ] ],
      [ "Using the library", "install.html#autotoc_md112", [
        [ "Compilation", "install.html#autotoc_md113", null ],
        [ "Instruction Set Selection", "install.html#autotoc_md114", null ],
        [ "Execution", "install.html#autotoc_md115", null ],
        [ "Use in CMake", "install.html#autotoc_md116", null ]
      ] ],
      [ "Advanced options", "install.html#autotoc_md117", null ]
    ] ],
    [ "Tutorials", "tutorials.html", [
      [ "Basic Operations", "intro-01.html", [
        [ "Initial problem", "intro-01.html#autotoc_md143", null ],
        [ "From scalar to SIMD using eve::wide", "intro-01.html#autotoc_md144", null ],
        [ "Handling eve::wide", "intro-01.html#autotoc_md145", null ],
        [ "Mathematical Epilogue", "intro-01.html#autotoc_md146", null ],
        [ "Conclusion", "intro-01.html#autotoc_md147", null ]
      ] ],
      [ "Algorithms", "intro-02.html", [
        [ "Initial problem", "intro-02.html#autotoc_md148", null ],
        [ "Toward SIMD Algorithms", "intro-02.html#autotoc_md149", null ],
        [ "Tuning algorithms", "intro-02.html#autotoc_md150", null ],
        [ "Conclusion", "intro-02.html#autotoc_md151", null ]
      ] ],
      [ "Tuples", "intro-03.html", [
        [ "Tuple of SIMD registers", "intro-03.html#autotoc_md152", null ],
        [ "SIMD register of tuples", "intro-03.html#autotoc_md153", null ],
        [ "Conclusion", "intro-03.html#autotoc_md154", null ]
      ] ],
      [ "Data Structures", "intro-04.html", [
        [ "Adapting UDT to SIMD processing", "intro-04.html#autotoc_md155", null ],
        [ "Creating SIMD-aware UDT", "intro-04.html#autotoc_md156", null ],
        [ "Storage and Processing", "intro-04.html#autotoc_md157", null ],
        [ "Conclusion", "intro-04.html#autotoc_md158", null ]
      ] ],
      [ "Conditional operations", "conditional.html", [
        [ "Explicit Selection", "conditional.html#autotoc_md136", null ],
        [ "Conditional Function Syntax", "conditional.html#autotoc_md137", null ],
        [ "Conditional Expressions", "conditional.html#autotoc_md138", [
          [ "Mask with alternative", "conditional.html#autotoc_md139", null ],
          [ "Context-sensitive mask", "conditional.html#autotoc_md140", null ]
        ] ],
        [ "Conclusion", "conditional.html#autotoc_md141", null ]
      ] ],
      [ "Frequency Scaling.", "freqscale.html", null ],
      [ "Interaction with native code.", "inter-with-native.html", [
        [ "What about non-native sizes?", "inter-with-native.html#autotoc_md142", null ]
      ] ],
      [ "Handling Multiple Architecture Targets", "multiarch.html", [
        [ "The Issue", "multiarch.html#autotoc_md159", null ],
        [ "From static to dynamic dispatch", "multiarch.html#autotoc_md160", [
          [ "Writing the kernel", "multiarch.html#autotoc_md161", null ],
          [ "Writing the dynamic function hub", "multiarch.html#autotoc_md162", null ],
          [ "Compiling and Using Dynamic Kernels", "multiarch.html#autotoc_md163", null ]
        ] ],
        [ "Conclusion", "multiarch.html#autotoc_md164", null ]
      ] ]
    ] ],
    [ "Why and How", "eve-dev.html", [
      [ "Design Decisions", "design_rationale.html", [
        [ "SIMD registers as Type x Cardinal", "design_rationale.html#rationale-simd", null ],
        [ "Callable Function Objects as main API", "design_rationale.html#rationale-callable", null ],
        [ "Function customization via higher-order decorator", "design_rationale.html#rationale-decorator", null ],
        [ "Masked operations support", "design_rationale.html#rationale-mask", null ]
      ] ],
      [ "SIMD Algorithms", "algo_rationale.html", [
        [ "General Principles", "algo_rationale.html#autotoc_md81", null ],
        [ "Basic Components", "algo_rationale.html#autotoc_md82", [
          [ "Reusable loops", "algo_rationale.html#autotoc_md83", null ],
          [ "Ranges or Iterators", "algo_rationale.html#autotoc_md84", [
            [ "General concepts", "algo_rationale.html#autotoc_md85", null ],
            [ "Relaxed concepts", "algo_rationale.html#autotoc_md86", null ]
          ] ]
        ] ],
        [ "Customization", "algo_rationale.html#autotoc_md87", [
          [ "Algorithms traits", "algo_rationale.html#autotoc_md88", null ]
        ] ]
      ] ],
      [ "Components Semantic", "glossary_semantic.html", [
        [ "Property of EVE types", "glossary_semantic.html#autotoc_md92", [
          [ "Cardinal", "glossary_semantic.html#autotoc_md93", null ],
          [ "Element type", "glossary_semantic.html#autotoc_md94", null ],
          [ "ABI traits", "glossary_semantic.html#autotoc_md95", null ]
        ] ],
        [ "Operations Classification", "glossary_semantic.html#autotoc_md96", [
          [ "Generalized Element Access", "glossary_semantic.html#autotoc_md97", null ],
          [ "Element-wise Operations", "glossary_semantic.html#glossary_elementwise", null ],
          [ "Reductions", "glossary_semantic.html#glossary_reduction", null ]
        ] ],
        [ "Function Semantic", "glossary_semantic.html#autotoc_md98", [
          [ "Arithmetic Functions", "glossary_semantic.html#glossary_arithmetic", null ],
          [ "Bitwise Functions", "glossary_semantic.html#glossary_bitwise", null ],
          [ "Logical Functions", "glossary_semantic.html#glossary_logical", null ],
          [ "Constant Functions", "glossary_semantic.html#glossary_constant", null ],
          [ "General Principles", "glossary_semantic.html#autotoc_md99", null ],
          [ "Precision handling", "glossary_semantic.html#autotoc_md100", null ]
        ] ]
      ] ],
      [ "Development Environment", "dev_environment.html", [
        [ "Docker setup", "dev_environment.html#dev_docker_setup", null ],
        [ "Running EVE docker", "dev_environment.html#dev_docker_helper", null ]
      ] ],
      [ "Building for Testing", "dev_cmake.html", [
        [ "CMake setup", "dev_cmake.html#autotoc_md89", null ],
        [ "Compiling EVE Unit Tests", "dev_cmake.html#autotoc_md90", null ],
        [ "Compiling EVE Random Tests", "dev_cmake.html#autotoc_md91", null ]
      ] ]
    ] ],
    [ "Change Log", "changelog.html", [
      [ "Version 2023.02.15", "changelog.html#autotoc_md118", [
        [ "What's Changed", "changelog.html#autotoc_md119", [
          [ "Removal and Depreciation", "changelog.html#autotoc_md120", null ],
          [ "Architectures/Compilers Support & Fixes", "changelog.html#autotoc_md121", [
            [ "The One Big News for this release: SVE", "changelog.html#autotoc_md122", null ],
            [ "Other Fixes", "changelog.html#autotoc_md123", null ]
          ] ],
          [ "Features", "changelog.html#autotoc_md124", null ],
          [ "Bug Fixes", "changelog.html#autotoc_md125", null ]
        ] ]
      ] ],
      [ "Version 2022.09.1", "changelog.html#autotoc_md126", null ],
      [ "Version 2022.09.0", "changelog.html#autotoc_md127", [
        [ "What's Changed", "changelog.html#autotoc_md128", null ],
        [ "New Contributors", "changelog.html#autotoc_md129", null ]
      ] ],
      [ "Version 2022.03.0", "changelog.html#autotoc_md130", [
        [ "What's Changed", "changelog.html#autotoc_md131", null ],
        [ "New Contributors", "changelog.html#autotoc_md132", null ]
      ] ],
      [ "Version 2021.10.0", "changelog.html#autotoc_md133", [
        [ "What's Changed", "changelog.html#autotoc_md134", null ]
      ] ],
      [ "Version beta.2020.09", "changelog.html#autotoc_md135", null ]
    ] ],
    [ "Licence", "licence.html", null ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ]
      ] ]
    ] ],
    [ "Concepts", "concepts.html", "concepts" ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", null ],
        [ "Variables", "functions_vars.html", null ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Related Symbols", "functions_rela.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"algo_rationale.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';