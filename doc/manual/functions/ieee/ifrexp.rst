.. _function-ifrexp:

######
ifrexp
######

**Required header:** ``#include <eve/function/ifrexp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ifrexp = {};
   }

Function object Decomposing a :ref:`IEEEValue <ieeeconcept-value>` into a normalized fraction and an integral power of two.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  std::pair<wide<T,N>, wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    std::pair<T, T>                 operator()( T s ) noexcept;

* [1] Computes a pair : a normalized fraction and an integral exponent of two.
* [2] Computes a pair : a normalized fraction and an integral exponent of two.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A pair of values with the same type as the parameter. 

Notes
*****
  -  If arg is :math:`\pm0`, {:math:`\pm0`, :math:`\0`} is returned.
  -  If arg is NaN,            { NaN, Nan} is returned.

Options
*******

  - raw_: the raw_ option does not properly treat any of the corner cases described above
  - without options :math:`\infty` input is undefined behaviour and denormals are not properly treared
  - pedantic_: is standard conforming even with denormals



.. seealso::  :ref:`ifrexp <function-frexp>`,  :ref:`ldexp <function-ldexp`

Example
*******

.. include:: ../../../../test/doc/core/ifrexp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ifrexp.txt
  :literal:
