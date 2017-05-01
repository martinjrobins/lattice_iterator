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
#ifndef LATTICE_ITERATOR_H_ 
#define LATTICE_ITERATOR_H_ 

#include <array>
#include <cmath>
#include <cassert>

namespace lattice {

template <unsigned int D>
class lattice_iterator {
    typedef lattice_iterator<D> iterator;
    typedef std::array<double,D> double_d;
    typedef std::array<int,D> int_d;
    typedef std::array<size_t,D> size_d;

    int_d m_min;
    int_d m_max;
    int_d m_index;
    int_d m_size;
public:
    typedef const int_d pointer;
	typedef std::random_access_iterator_tag iterator_category;
    typedef const int_d& reference;
    typedef const int_d value_type;
	typedef std::ptrdiff_t difference_type;

    lattice_iterator()
    {}

    lattice_iterator(const int_d &min, 
                     const int_d &max, 
                     const int_d &start):
        m_min(min),
        m_max(max),
        m_index(start),
        m_size(minus(max,min))
    {}


    reference operator *() const {
        return dereference();
    }

    reference operator ->() const {
        return dereference();
    }

    iterator& operator++() {
        increment();
        return *this;
    }

    iterator operator++(int) {
        iterator tmp(*this);
        operator++();
        return tmp;
    }

    iterator operator+(const int n) {
        iterator tmp(*this);
        tmp.increment(n);
        return tmp;
    }

    iterator& operator+=(const int n) {
        increment(n);
        return *this;
    }

    iterator& operator-=(const int n) {
        increment(-n);
        return *this;
    }

    iterator operator-(const int n) {
        iterator tmp(*this);
        tmp.increment(-n);
        return tmp;
    }

    size_t operator-(iterator start) const {
        const int distance = collapse_index_vector(minus(m_index,start.m_index));
        assert(distance > 0);
        return distance;
    }

    inline bool operator==(const iterator& rhs) const {
        return equal(rhs);
    }

    inline bool operator!=(const iterator& rhs) const {
        return !operator==(rhs);
    }

private:

    static inline 
    int_d minus(const int_d& arg1, const int_d& arg2) {
        int_d ret;
        for (size_t i = 0; i < D; ++i) {
            ret[i] = arg1[i]-arg2[i];
        }
        return ret;
    }

    int collapse_index_vector(const int_d &vindex) const {
        int index = 0;
        unsigned int multiplier = 1.0;
        for (size_t i = 0; i<D; ++i) {
            if (i > 0) {
                multiplier *= m_size[i-1];
            }
            index += multiplier*vindex[i];
        }
        return index;
    }

    int_d reassemble_index_vector(const int index) const {
        int_d vindex;
        int i = index;
        for (size_t d = 0; d<D; --d) {
            double div = (double)i / m_size[d];
            vindex[d] = std::round((div-std::floor(div)) * m_size[d]);
            i = std::floor(div);
        }
        return vindex;
    }

    bool equal(iterator const& other) const {
        for (size_t i = 0; i < D; ++i) {
           if (m_index[i] != other.m_index[i]) {
               return false;
           }
        }
        return true;
    }

    reference dereference() const { 
        return m_index; 
    }

    void increment() {
        for (size_t i=0; i<D; i++) {
            ++m_index[i];
            if (m_index[i] < m_max[i]) break;
            if (i != D-1) {
                m_index[i] = m_min[i];
            } 
        }
    }

    void increment(const int n) {
        int collapsed_index = collapse_index_vector(m_index);
        m_index = reassemble_index_vector(collapsed_index += n);
    }
};

}

#endif
