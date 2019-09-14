.. _function-atan:

#####
atan
#####

**Required header** ``#include <eve/function/atan.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ atan = {};
   }

Function object computing the inverse tangent of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``atan(x)`` returns the arc :math:`r` in the interval   :math:`[-\pi/2, \pi/2[` such that :math:`\tan(r) == x`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes the mathematical value :math:`\arctan(v)`.
* [2] Computes the mathematical value :math:`\arctan(s)`.
 
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

.. include:: ../../../../test/doc/atan.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/atan.txt
  :literal:

