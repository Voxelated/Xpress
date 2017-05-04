//==--- Xpress/Array/ArrayFwd.hpp -------------------------- -*- C++ -*- ---==//
//            
//                                Voxel : Xpress
//
//                        Copyright (c) 2017 Rob Clucas
//  
//  This file is distributed under the MIT License. See LICENSE for details.
//  
//==------------------------------------------------------------------------==//
//
/// \file  ArrayFwd.hpp
/// \brief This file provides the definition of the array class.
// 
//==------------------------------------------------------------------------==//

#pragma once

namespace Voxx   {
namespace Xpress {

/// The Array class defines a structure to store a fixed-size number of
/// elements contiguously. The class will work on both the host and the device.
///
/// \tparam   T         The tyoe of the elements in the array.
/// \tparam   Elements  The number of elements in the array.
template <typename T, std::size_t Elements>
class Array;

}} // namespace Voxx::Xpress