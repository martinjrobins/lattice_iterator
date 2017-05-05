# A N-dimensional lattice iterator for C++ 

[![TravisCI](https://travis-ci.org/martinjrobins/lattice_iterator.svg?branch=master)](https://travis-ci.org/martinjrobins/lattice_iterator)

## Quick Start

Iterating over a set of 1D or 2D consecutive indicies is a common operation, for 
example, the following loop iterates over the values from `0` to `n-1`

```cpp
for(int i=0; i<n; ++i) {
    do_something(i);
}
```

And this is a 2D version, where we iterate from `(0,0)` to `(n-1,m-1)`

```cpp
for(int i=0; i<n; ++i) {
    for(int j=0; j<m; ++j) {
        do_something( {{i,j}} );
    }
}
```

This is all well and good, except if you don't know what dimension you wish to 
iterate over, or if you want to write some generic code that is independent of 
the dimension. In this case you would like to use some sort of iterator or 
generating function. This library provides such an iterator. 

The lattice iterator is full defined in `src/lattice_iterator.h`, and can be 
compiled by a suitable C++11 compiler. Note that the iterator implements a 
comparison with a `bool` type to judge whether the given range is exhausted, so 
is suitable for C++17 projects where ranges can have `begin` and `end` iterators 
of differing type.

As an example of use, we can re-implement the above 2D loop as

```cpp
lattice_iterator<2> it( {{0,0}}, {{n,m}} );
for(; it != false; ++it) {
    do_something(*it);
}
```

If you wish to use an `end` iterator of identical type, simply use the empty 
constructor for the iterator.

```cpp
lattice_iterator<2> it( {{0,0}}, {{n,m}} );
lattice_iterator<2> it_end;
for(; it != it_end; ++it) {
    do_something(*it[0],*it[1]);
}
```

## Extended Example

This type of iterator is very useful for stencil codes, often used in computer 
simulations (e.g. Finite Difference Method) or image processing (e.g. Gaussian 
blur). Below is a generic stencil code that solves the 2D heat equation on an 
`n` by `m` lattice with Dirichlet boundary conditions. The stencil order or the 
number of dimensions are parameters can can be changed easily (see the `tests/` 
sub-folder for a full code listing)


```cpp
const unsigned int D = 2;
typedef std::array<int,D> int_d;
const size_t m = 50;
const size_t n = 50;
const int order = 4;
const double h = 1.0/m;
const double dt = 0.9*std::pow(h,2)/(-stencil<order>(0)*D);
const double r = dt/std::pow(h,2);
const double t = 1.0;
const int timesteps = t/dt;
std::cout << "timesteps = "<<timesteps<<" r = "<<r<<std::endl;

const int_d min = {{0,0}};
const int_d max = {{n+order,m+order}};
const int_d min_domain = {{order/2,order/2}};
const int_d max_domain = {{n+order/2,m+order/2}};
const int_d max_left = {{order/2,m+order}};
const int_d min_right = {{n+order/2,0}};

auto all = make_iterator_range(
                    lattice_iterator<D>(min,max),
                    false);
auto domain = make_iterator_range(
                    lattice_iterator<D>(min_domain,max_domain),
                    false);
auto left_boundary = make_iterator_range(
                    lattice_iterator<D>(min,max_left),
                    false);
auto right_boundary = make_iterator_range(
                    lattice_iterator<D>(min_right,max),
                    false);

std::vector<double> values0(all.size(),0.0);
std::vector<double> values1(all.size(),0.0);

auto calculate = [&](const int_d& index) {
    int ret = 0;
    unsigned int multiplier = 1.0;
    for (size_t i = 0; i<D; ++i) {
        if (i > 0) {
            multiplier *= max[i-1];
        }
        ret += multiplier*index[i];
    }
    return ret;
};


for(const auto& index: left_boundary) {
    values0[calculate(index)] = 1.0;
    values1[calculate(index)] = 1.0;
}
for(const auto& index: right_boundary) {
    values0[calculate(index)] = 1.0;
    values1[calculate(index)] = 1.0;
}

for (int i = 0; i < timesteps; ++i) {
    for(const auto& index: domain) {
        const size_t base_index = calculate(index);
        values1[base_index] = values0[base_index];
        for (unsigned int d = 0; d < D; d++) {
            int_d stencil_index = index;
            for (int j = -order/2; j <= order/2; j++) {
                stencil_index[d] = j+index[d];
                const double coeff = stencil<order>(j);
                values1[base_index] += r*coeff*values0[calculate(stencil_index)];
            } 
        }
    }
    values1.swap(values0);
}
```

