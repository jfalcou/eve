.. _function-sinhcosh:

########
sinhcosh
########

**Required header:** ``#include <eve/function/sinhcosh.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sinhcosh = {};
   }

Function object computing conjointly the hyperbolic sine and the hyperbolic cosine 
of a :ref:`Value <concept-value>`,
that is :math:`(e^x-e^{-x})/2` and :math:`(e^x+e^{-x})/2`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  hyperbolic sine of the :ref:`wide <type-wide>`.
* [2] Computes the hyperbolic sine of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 

.. rubric:: Notes

* the conjoint computation is more economic than the two separate calls.

.. seealso::  :ref:`exp <function-exp>`,  :ref:`sinh <function-sinh>`, :ref:`cosh <function-cosh>`,  :ref:`tanh <function-tanh>`, 
 :ref:`coth <function-coth>`,  :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Example
*******

.. include:: ../../../../test/doc/core/sinhcosh.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sinhcosh.txt
  :literal:
