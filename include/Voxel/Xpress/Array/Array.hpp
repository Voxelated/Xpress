//==--- Xpress/Array/Array.hpp ----------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Xpress
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//  
//==------------------------------------------------------------------------==//
//
/// \file  Array.hpp
/// \brief This file provides an implementation of an array class.
// 
//==------------------------------------------------------------------------==//

#pragma once 

#include "ArrayFwd.hpp"
#include <Voxel/Traits/ContainerTraits.hpp>
#include <Voxel/Utility/Portability.hpp>

namespace Voxx   {
namespace Xpress {

/// Implementation of the array class. This implementation has public aliase and
/// constexpr functions which conform to Voxel's  ContainerTraits class, and can
/// thus be used by algorithms which take a generic container.
/// 
/// \tparam   T         The type of the elements in the array.
/// \tparam   Elements  The number of elements in teh array.
template <typename T, std::size_t Elements>
class Array {
 public:
  // Note that the rest of the traits are available through ContainerTraits.
  
  /// Defines the type of data stored in the vector:
  using DataType       = T;
  /// Defines the size type used by the Array.
  using SizeType       = std::size_t;
  /// Defines the type of the array.
  using SelfType       = Array;
  /// Defines a reference type for the container.
  using Reference      = typename ContainerTraits<SelfType>::Reference;
  /// Defines a const reference type for the container.
  using ConstReference = typename ContainerTraits<SelfType>::ConstReference;

  //==--- Constants --------------------------------------------------------==//
  
  /// Returns true that the size of the container is fixed at compile time.
  static constexpr bool     isFixedSize = true;
  /// Returns the size of the container.
  static constexpr SizeType elements    = Elements; 

  //==--- Con/destruction -------------------------------------------------==//

  /// Default constructor -- creates an uninitialized array.
  VoxxDeviceHost constexpr Array() = default;

  /// Constructor which takes a single argument, and sets all elements to the 
  /// value \p v.
  /// 
  /// \todo Expand this implementation to used the correct filler.
  /// 
  /// \param[in] v The value to set the array elements to.
  VoxxDeviceHost constexpr Array(DataType v)
  : Array{std::move(v), std::make_index_sequence<elements>{}} {}

  /// Constructor -- creats an array from a variadic list of arguments. This
  /// does not handle the case that the variadic list is incorrectly sized. We
  /// assume that the user is also to specify the size of the array and then
  /// give the correct number of arguments. This overload is only invoked when
  /// there are two or more arguments.
  /// \param[in]  values The values to store in the array.
  /// \tparam     Values The types of the values for the array.
  template <typename... Values,
           typename = std::enable_if_t<sizeof...(Values) >= 2>>
  VoxxDeviceHost constexpr Array(Values&&... values) noexcept
  :   Data{std::forward<DataType>(values)...} {
    static_assert(sizeof...(Values) == Elements,
                  "Varaidic list size must equal container size");
  }

  /// Copy-constructor -- use the default version.
  /// \param[in] other  The other array to move.
  VoxxDeviceHost constexpr Array(const SelfType&) = default;

  /// Move-constructor -- use the default.
  /// \param[in] other  The other array to move.
  VoxxDeviceHost constexpr Array(SelfType&& other) = default;

  //==--- Operator overloads ----------------------------------------------==//

  /// Copy assignment overload -- use the default.
  /// \param[in] other  The other array to copy assign from.
  VoxxDeviceHost constexpr SelfType&
  operator=(const SelfType&) noexcept = default;

  /// Move assignment overload -- use the defult.
  /// \param[in] other  The other array to move assign from.
  VoxxDeviceHost constexpr SelfType& 
  operator=(SelfType&&) noexcept = default;

  /// Overload of access operator to access an element. __Note:__
  /// this does not check that the value of \p i is in range.
  /// \param[in] i The index of the element in the vetor to return.
  /// Returns the element at position \p i.
  VoxxDeviceHost constexpr Reference operator[](size_t i) {
    return Data[i];
  }  

  /// Overload of access operator to access an element in the array. __Note:__
  /// this does not check that the value of \p i is in range.
  /// \param[in] i The index of the element in the vetor to return.
  /// Returns the element at position \p i.
  VoxxDeviceHost constexpr ConstReference operator[](size_t i) const {
    return Data[i];
  }

  //==--- Methods ----------------------------------------------------------==//

  /// Returns the size of the array.
  VoxxDeviceHost constexpr SizeType size() const { return elements; }

/*
  /// Constructor --- creates an Array from a variadic list of values, as
  /// long as there is at least one value.
  template <typename    ValType   ,
            typename... ValueTypes,
            typename = std::enable_if_t< sizeof...(ValueTypes) != 0 &&
              std::is_convertible<ValType, ValueType>::value>>
  DeviceHost constexpr Array(ValType&& value, ValueTypes&&... values)
  :   Data{std::forward<ValueType>(value),
           std::forward<ValueType>(values)...} {
    static_assert(sizeof...(ValueTypes) + 1 == Elements, 
                  "Incorrect number of elements for array\n");
  }

  template <typename Container,typename = std::enable_if_t<
              !std::is_convertible<
                std::decay_t<Container>, ElementType>::value>>
  DeviceHost constexpr Array(Container&& container) {
    // TODO: Change to unrolled implementation ...
    for (std::size_t i = 0; i < elements; ++i)
      Data[i] = container[i];
  }

  } 
*/
 private:
  /// Constructor which fills the array with a singe element. This will result
  /// in significant code bloat for large arrays, so we need to update it to
  /// only call this for small sized arrays, and to use the parallel
  /// initializers for larger ones.
  /// \param[in]  value   The value to set all elements to.
  /// \param[in]  expand  Object to expand the value into the array.
  /// \tparam     I       The indices for the array elements.
  template <std::size_t... I>
  VoxxDeviceHost constexpr
  Array(DataType value, std::index_sequence<I...> expand) noexcept
  : Data{dummy<I>(std::move(value))...} {}


  /// Dummy function which takes a value and returns it. It allows a packe to
  /// be expanded, returning the value for each index in the pack.
  /// \param[in]  value  The value to return.
  /// \tparam     Index  The index used when unpacking with the function.
  template <std::size_t Index>
  VoxxDeviceHost constexpr DataType dummy(DataType value) const noexcept {
    return value;
  }

  //==--- Aliases ----------------------------------------------------------==//

  DataType Data[elements]; //!< Data elements.
};

}} // namespace Voxx::Xpress