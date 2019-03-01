.. _function-is_positive:

###########
is_positive
###########

**Required header** ``#include <eve/function/is_positive.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_positive = {};
   }

Function object determining if the given :ref:`Value <concept-value>` has it bit of sign set

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element has it bit of sign not set.
* [2] returns :ref:`True <constant-true_>` if **s** has it bit of sign not set.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_positive(x)`` is equivalent to ``is_not_greater(x, Zero(as(x)))``
  for :ref:`IntegralValues <concept-integralvalue>`, but for :ref:`IEEEValues <concept-ieeevalue>`
  the object returns :ref:`True <constant-true_>` if the most significant bit of the element is not set.
  More precisely, this implies that -0.0 and -0.0f are not 'positive' but are 'not greater than zero'.

Example
*******

.. include:: ../../../../test/doc/is_positive.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_positive.txt
  :literal:

