.. _function-if_else:

##############
if_else
##############

**Required header:** ``#include <eve/function/if_else.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ if_else = {};
   }

Function object performing a logical selection between two :ref:`Values <concept-value>` of same element type
according to a :ref:`Value <concept-value>`or a :ref:`logical Value <concept-logicalvalue>`.
The element-wise scheme is: if the first parameter is 'true' returns the second parameter else the third.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N, typename U> wide<U,N> operator()( wide<T,N> const& v, wide<U,N> const& w , wide<U,N> const& x ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, T s, T t ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<logical<T>,N> const& v, T s, T t ) noexcept;
   template<typename T, typename N, typename U> wide<U,N> operator()( wide<T,N> const& v, wide<U,N> const& w , U s ) noexcept;
   template<typename T, typename N, typename U> wide<U,N> operator()( wide<T,N> const& v, U s , wide<U,N> const& w)
   template<typename T, typename U> constexpr   T         operator()( T r, U s, U t ) noexcept;

* [1] Selects elements between **w** and **x** based on the values of **v**. 
* [2,3] Selects  **s** or **t** based on the values of **v**. 
* [4] Selects  between **w** elements and **s**  based on the values of **v**. 
* [5] Selects  between **s** and **w** elements based on the values of **v**.    
* [6] Selects **r** or **t** based on **r**.

.. rubric:: Parameters

* **v**: Instances of **wide<T,N>**
* **w**, **x**, **r**: Instances of **wide<U,N>**
* **r**: Scalar value  of type **T**
* **s**, **t**: Scalar values of type **U**

.. rubric:: Return value

* [1,4,5] A value of the type **wide<U,N>**                  
* [2,3]   A value of the type **wide<T,N>**
* [6]     A value of type **T**

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/if_else.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/if_else.txt
  :literal:
