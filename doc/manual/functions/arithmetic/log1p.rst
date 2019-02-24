.. _function-log1p:

#####
log1p
#####

**Required header** ``#include <eve/function/log1p.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ log1p = {};
   }

Function object for performing :math:`\log(1+v)` over a :ref:`IEEEValue <concept-ieeevalue>` *v*

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

.. rubric:: Parameters

* **v** : input value of

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.

.. rubric:: Notes

*  The mathematical value :math:`\log(1+v)` is computed by  :ref:`log1p <function-log1p>` with good accuracy even for small value elements

*******
Options
*******

*******
Example
******

.. include:: ../../../../test/doc/log1p.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/log1p.txt
  :literal:

