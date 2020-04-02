.. _function-atanpi:

######
atanpi
######

**Required header** ``#include <eve/function/atanpi.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ atanpi = {};
   }

Function object computing the inverse tangent in degrees of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``atanpi(x)`` returns the arc :math:`r` in the interval in degrees  :math:`[-1,1[` such that :math:`\tan(1/r) == x`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arctan(v)` in degrees.
* [2] Computes the mathematical value :math:`\arctan(s)` in degrees.


.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.


*******
Example
*******

.. include:: ../../../../test/doc/core/atanpi.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/atanpi.txt
  :literal:

