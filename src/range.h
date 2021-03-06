/*

Copyright (c) 2005-2016, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Aboria.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifndef RANGE_H_ 
#define RANGE_H_ 

#include <utility>
#include <iterator>

namespace lattice {

template <typename IteratorType1, typename IteratorType2>
struct iterator_range{
    IteratorType1 m_begin;
    IteratorType2 m_end;

    iterator_range()
    {}

    iterator_range(IteratorType1&& begin, IteratorType2&& end):
        m_begin(std::forward<IteratorType1>(begin)),m_end(std::forward<IteratorType2>(end))
    {}

    const IteratorType1 &begin() const { return m_begin; }
    const IteratorType2 &end() const { return m_end; }
    IteratorType1 &begin() { return m_begin; }
    IteratorType2 &end() { return m_end; }
    size_t size() const { return m_end - m_begin; }
};

template <typename IteratorType1>
struct iterator_range<IteratorType1,bool> {
    IteratorType1 m_begin;
    typedef bool IteratorType2;
    IteratorType2 m_end;

    iterator_range()
    {}

    iterator_range(IteratorType1&& begin, IteratorType2&& end):
        m_begin(std::forward<IteratorType1>(begin)),m_end(std::forward<IteratorType2>(end))
    {}

    const IteratorType1 &begin() const { return m_begin; }
    const IteratorType2 &end() const { return m_end; }
    IteratorType1 &begin() { return m_begin; }
    IteratorType2 &end() { return m_end; }
    size_t size() const { return IteratorType1() - m_begin; }
};

template <typename IteratorType1, typename IteratorType2>
iterator_range<IteratorType1, IteratorType2> make_iterator_range(IteratorType1&& begin, IteratorType2&& end) {
    return iterator_range<IteratorType1, IteratorType2>(std::forward<IteratorType1>(begin),
                                                        std::forward<IteratorType2>(end));
}

}

#endif
