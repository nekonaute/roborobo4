//
// Created by Paul Ecoffet on 18/02/2021.
//

#ifndef ROBOROBO3_PYARRAYHELPERS_H
#define ROBOROBO3_PYARRAYHELPERS_H

#include <pybind11/pybind11.h>



template <typename Sequence>
inline py::array_t<typename Sequence::value_type> as_pyarray(Sequence &v) {
    py::str dummyDataOwner;
    auto pyarr = py::array_t<typename Sequence::value_type>(v.size(), v.data(), dummyDataOwner); // hack to prevent copy
    // see https://github.com/pybind/pybind11/issues/323#issuecomment-575717041
    assert(!pyarr.owndata());
    assert(pyarr.data() == v.data());
    return pyarr;
}



#endif //ROBOROBO3_PYARRAYHELPERS_H
