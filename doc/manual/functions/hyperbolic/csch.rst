.. _function-csch:

####
csch
####

**Required header:** ``#include <eve/function/csch.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ csch = {};
   }

Function object computing the hyperbolic cosecant  of a :ref:`Value <concept-value>`,
that is :math:`2/(e^x-e^{-x})`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  hyperbolic cosecant of the :ref:`wide <type-wide>`.
* [2] Computes the hyperbolic cosecant of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`exp <function-exp>`,  :ref:`cosh <function-cosh>`,  :ref:`sinh <function-sinh>`, 
 :ref:`tanh <function-tanh>`,  :ref:`coth <function-coth>`,  :ref:`sech <function-sech>`

Example
*******

.. include:: ../../../../test/doc/core/csch.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/csch.txt
  :literal:
