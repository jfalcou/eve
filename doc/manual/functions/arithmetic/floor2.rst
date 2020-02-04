.. _function-floor2:

######
floor2
######

**Required header:** ``#include <eve/function/floor2.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ floor2 = {};
   }

Function object computing the greatest power of two value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise greatest power of two values less or equal to the value of the :ref:`wide <type-wide>`.
* [2] Computes the greatest power of two value less or equal to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - if the expected result does not exists (input less than one) or is not representable in the parameter type 
    the result is undefined.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/floor2.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/floor2.txt
  :literal:
