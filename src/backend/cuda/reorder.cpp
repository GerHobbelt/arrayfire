/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <reorder.hpp>

#include <Array.hpp>
#include <common/half.hpp>
#include <err_cuda.hpp>
#include <kernel/reorder.hpp>

#include <stdexcept>

using arrayfire::common::half;

namespace arrayfire {
namespace cuda {

template<typename T>
Array<T> reorder(const Array<T> &in, const af::dim4 &rdims) {
    const af::dim4 &iDims = in.dims();
    af::dim4 oDims(0);
    for (int i = 0; i < 4; i++) { oDims[i] = iDims[rdims[i]]; }

    Array<T> out = createEmptyArray<T>(oDims);

    kernel::reorder<T>(out, in, rdims.get());

    return out;
}

#define INSTANTIATE(T) \
    template Array<T> reorder<T>(const Array<T> &in, const af::dim4 &rdims);

INSTANTIATE(float)
INSTANTIATE(double)
INSTANTIATE(cfloat)
INSTANTIATE(cdouble)
INSTANTIATE(int)
INSTANTIATE(uint)
INSTANTIATE(schar)
INSTANTIATE(uchar)
INSTANTIATE(char)
INSTANTIATE(intl)
INSTANTIATE(uintl)
INSTANTIATE(short)
INSTANTIATE(ushort)
INSTANTIATE(half)

}  // namespace cuda
}  // namespace arrayfire
