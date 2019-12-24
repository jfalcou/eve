.. _function-log:

#####
log
#####

**Required header** ``#include <eve/function/log.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ log = {};
   }

Function object computing the natural logarithm of an :ref:`IEEEValue <concept-ieeevalue>` **v**

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1,2] Computes the mathematical value :math:`\log(v)`.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.

.. seealso:: :ref:`log2 <function-log2>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, 
 :ref:`exp <function-exp>`, :ref:`exp2 <function-exp2>`,  :ref:`exp10 <function-exp10>`,  :ref:`expm1 <function-expm1>`

.. include:: ../../../../test/doc/core/log.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/log.txt
  :literal:

