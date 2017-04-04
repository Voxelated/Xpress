//==--- Xpress/Array/Array.hpp ---------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Phyz
//
//                  Copyright (c) 2016 Voxel Technologies, Ltd.
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  Array.hpp
/// \brief This file implements an Array class.
//
//==-----------------------------------------------------------------------==//

#ifndef VOXEL_XPRESS_ARRAY_ARRAY_HPP
#define VOXEL_XPRESS_ARRAY_ARRAY_HPP

#include "ArrayFwd.hpp"
#include <Voxel/Utility/Portability.hpp>

#include <initializer_list>
#include <type_traits>
#include <cassert>
#include <utility>

#include <iostream>

namespace Voxx   {
namespace Xpress {

/// Implementation of the Array class.
/// \tparam     T         The type of the elements in the array.
/// \tparam     Elements  The number of elements in teh array.
template <typename T, std::size_t Elements>
class Array {
 public:
  //==--- Aliases ---------------------------------------------------------==//
  
  /// Defines the value type of an element.
  using ValueType          = std::decay_t<T>;
  /// Defines a reference type for the vector.
  using ReferenceType      = ValueType&;
  /// Defines a reference type for the vector.
  using ConstReferenceType = const ValueType&;
  /// Defines a pointer type for the view.
  using PointerType        = ValueType*;
    /// Defines a pointer type for the view.
  using ConstPointerType   = const ValueType*;
  /// Defines the size type used by the container.
  using SizeType           = size_t;

  //==--- Constants -------------------------------------------------------==//

  /// Returns the number of elements in the array.
  static constexpr SizeType elements = Elements;

 private:
  /// Defines the type of the array.
  using SelfType = Array<T, Elements>;
  /// Returns true if decayed U is the same as decayed T.
  template <typename U>
  static constexpr bool isValueType = 
    std::is_same<std::decay_t<T>, std::decay_t<U>>::value;
 
 public:
  //==--- Con/destruction -------------------------------------------------==//

  /// Default constructor -- creates an uninitialized array.
  VoxxDeviceHost constexpr Array() = default;

  /// Constructor which takes a single argument, and broadcasts the value to
  /// all components in the array,
  /// \param[in]  v   The value to set the array elements to.
  VoxxDeviceHost constexpr Array(ValueType v) : Data{v} {}

  /// Constructor -- creates an Array from a variadic list of values, where the
  /// ith value specifies the number of elements in the ith dimension. This
  /// overload only participates in overlaod resolution is the type Arg is the 
  /// same as ValueType.
  /// 
  /// \param[in]  value   The value for the first element in the array.
  /// \param[in]  values  The values of the rest of the elements in the array.
  /// \tparam     Arg     The type of the first value.
  /// \tparam     Args    The types of the rest of the values for the array.
  /// \tparam     Enable  Enables/disables this overload.
  template <typename    Arg                                       ,
            typename... Args                                      ,
            typename    Enable = std::enable_if_t<isValueType<Arg>>
  VoxxDeviceHost constexpr Array(Arg&& value, Args&&... values)
  :   Data{std::forward<Arg>(value), std::forward<Args>(values)...} {
    static_assert(sizeof...(Sizes) + 1 == Elements        ,
                  "Incorrect number of elements for array");
  }

  /// Constructor --- creates an array from another container type. This
  /// requires that the \p container elements can be accessed with operator[].
  /// This overload only participaes in overload resolution if Container is not
  /// the same type as ValueType.
  /// \todo Add compile time check for operator[] for container.
  /// \param[in]  container   The container to create the array from.
  /// \tparam     Container   The type of the container.
  /// \tparam     Enable      Enables/disables this overload.
  template <typename Container                                         ,
            typename Enable = std::enable_if_t<!isValueType<Container>>>
  VoxxDeviceHost constexpr Array(Container&& container) {
    // TODO: Change to unrolled implementation ...
    for (std::size_t i = 0; i < elements; ++i)
      Data[i] = container[i];
  }

  /// Copy constructor -- uses the default version.
  /// \param[in]  other   The other array to copy.
  VoxxDeviceHost constexpr Array(const ArrayType& other) = default;

  /// Move constructor -- uses the default implementation.
  /// \param[in]  other   The other array to move.
  VoxxDeviceHost constexpr Array(ArrayType&& other) noexcept = default;

  //==--- Operator overloads ----------------------------------------------==//

  /// Copy assignment overload -- uses the default.
  /// \param[in]  other   The other array to copy from.
  /// Returns a reference to the modified array.
  VoxxDeviceHost constexpr ArrayType& 
  operator=(const ArrayType& other) = default;

  /// Move assignment overload -- uses the default.
  /// \param[in]  other   The other array to move.
  /// Returns a reference to the modified array.
  VoxxDeviceHost constexpr ArrayType&
  operator=(ArrayType&& other) noexcept = default;

  /// Overload of access operator to access an element. __Note:__
  /// this does not check that the value of \p i is in range.
  /// \param[in]  i   The index of the element in the vetor to return.
  /// Returns a refernce to the element at index \p i.
  VoxxDeviceHost constexpr ReferenceType operator[](size_t i) {
    return Data[i];
  }  

  /// Overload of access operator to access an element in the array. __Note:__
  /// this does not check that the value of \p i is in range.
  /// \param[in]  i   The index of the element in the vetor to return.
  /// Returns a constant reference to the element at index \p i.
  VoxxDeviceHost constexpr ReferenceType operator[](size_t i) const {
    return Data[i];
  } 

  /// Returns the size of the array.
  VoxxDeviceHost constexpr SizeType size() const { return Elements; } 

 protected:
  ValueType Data[Elements]; //!< Data elements.
};

}} // namespace Voxx::Xpress

#endif // VOXEL_XPRESS_ARRAY_ARRAY_HPP
