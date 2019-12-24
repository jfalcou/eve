.. _function-log2:

#####
log2
#####

**Required header** ``#include <eve/function/log2.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ log2 = {};
   }

Function object computing the base 2 logarithm of an :ref:`IEEEValue <concept-ieeevalue>` **v**

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1,2] Computes the mathematical value :math:`\log(v)/\log(2)`.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.

.. seealso:: :ref:`log <function-log>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, ref:`exp <function-exp>`, :ref:`exp2 <function-exp2>`,  :ref:`exp10 <function-exp10>`,  :ref:`expm1 <function-expm1>`


.. include:: ../../../../test/doc/core/log.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/log.txt
  :literal:

