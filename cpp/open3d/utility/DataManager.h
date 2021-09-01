// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <string>

namespace open3d {
namespace utility {

/// Computes the full path of a file/directory inside the Open3D common data
/// root. If \p relative_path is specified, the full path is computed by
/// appending the \p relative_path to the common data root; otherwise, the
/// common data root is returned.
///
/// SetDataRootCommon() must be called before using GetDataPathCommon().
/// SetDataRootCommon() is typically called once in program initialization.
///
/// \param relative_path Relative path to Open3D common data root.
std::string GetDataPathCommon(const std::string& relative_path = "");

/// Computes the full path of a file/directory inside the Open3D
/// download data root. If \p relative_path is specified, the full
/// path is computed by appending the \p relative_path to the
/// download data root; otherwise, the download data root is
/// returned.
///
/// SetDataRootDownload() must be called before using GetDataPathDownload().
/// SetDataRootDownload() is typically called once in program initialization.
///
/// \param relative_path Relative path to Open3D download data root.
std::string GetDataPathDownload(const std::string& relative_path = "");

/// Set the Open3D common data root. This is typically done once during
/// the initialization phase of a program.
///
/// \param data_root Full path of the Open3D common data root directory.
void SetDataRootCommon(const std::string& data_root);

/// Set the Open3D download data root. This is typically done once during
/// the initialization phase of a program.
///
/// \param data_root Full path of the Open3D download data root directory.
void SetDataRootDownload(const std::string& data_root);

}  // namespace utility
}  // namespace open3d
