.. _function-asin:

#####
asin
#####

**Required header** ``#include <eve/function/asin.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ asin = {};
   }

Function object computing the inverse sine of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``asin(x)`` returns the arc :math:`r` in the interval   :math:`[-\pi/2, \pi/2[` such that :math:`\sin(r) == x`.
If :math:`x` is outside :math:`[-1, 1[` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes the mathematical value :math:`\arcsin(v)` .
* [2] Computes the mathematical value :math:`\arcsin(s)`.


.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.


*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/asin.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/asin.txt
  :literal:

