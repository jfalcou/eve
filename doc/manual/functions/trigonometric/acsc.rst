.. _function-acsc:

#####
acsc
#####

**Required header** ``#include <eve/function/acsc.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acsc = {};
   }

Function object computing  the inverse cosecant in radian: (:math:`\arcsin(1/x)`) of an :ref:`IEEEValue <concept-ieeevalue>` **v**
   
       
********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arcsin(1/v)`.
* [2] Computes the mathematical value :math:`\arcsin(1/s)`.
  

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

.. include:: ../../../../test/doc/acsc.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/acsc.txt
  :literal:

