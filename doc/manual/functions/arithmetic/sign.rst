.. _function-sign:

####
sign
####

**Required header:** ``#include <eve/function/sign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sign = {};
   }

Function object computing the sign (-1,0 or 1) of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise sign of the value of the :ref:`wide <type-wide>`.
* [2] Computes the sign of the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/sign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sign.txt
  :literal:
