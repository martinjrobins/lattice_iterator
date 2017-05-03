
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "lattice.h"
using namespace lattice;

TEST_CASE( "iterators work", "[iterator]" ) {
    const unsigned int D = 2;

    typedef std::array<int,D> int_d;

    lattice_iterator<D> it({{0,0}}, {{2,2}});
    int_d value;

    SECTION( "initial value" ) {
        value = *it; 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "pre-increment" ) {
        value = *(++it); 

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "post-increment" ) {
        value = *(it++); 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 0 );

        value = *it;

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "increment by n" ) {
        value = *(it+2); 

        REQUIRE( value[0] == 0 );
        REQUIRE( value[1] == 1 );
    }

    SECTION( "decrement by n" ) {
        it += 3;
        it -= 2;
        value = *it; 

        REQUIRE( value[0] == 1 );
        REQUIRE( value[1] == 0 );
    }

    SECTION( "looping" ) {

        lattice_iterator<2> end;

        SECTION( "fori loop" ) {
            int count = 0;
            for (size_t i = 0; i < end-it; ++i) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "iterator bool loop" ) {
            int count = 0;
            for (; it != false; ++it) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "iterator loop" ) {
            int count = 0;
            for (; it != end; ++it) {
                ++count;
            }

            REQUIRE( count == 4 );
        }

        SECTION( "range loop" ) {
            auto test_range = make_iterator_range(it,end);
            int count = 0;
            for (auto& val: test_range) {
                ++count;
            }

            REQUIRE( count == 4 );
        }
    }
}

TEST_CASE( "finite difference") {
    const unsigned int D = 2;
    const size_t m = 10;
    const size_t n = 11;
    const size_t order = 5;

    const std::array<int,D> min = {{0,0}};
    const std::array<int,D> max = {{n+2*order,m+2*order}};
    const std::array<int,D> min_domain = {{order,order}};
    const std::array<int,D> max_domain = {{n+order,m+order}};
    const std::array<int,D> max_left = {{order,m+2*order}};
    const std::array<int,D> min_right = {{n+order+1,0}};

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

    std::vector<double> values(all.size(),0.0);

    for(auto it=left_boundary.begin(); it!=left_boundary.end(); ++it) {
        values[static_cast<size_t>(it)] = 1.0;
    }
    for(auto it=right_boundary.begin(); it!=right_boundary.end(); ++it) {
        values[static_cast<size_t>(it)] = 1.0;
    }

    for (int i = 0; i < 100; ++i) {
        for(auto it=domain.begin(); it!=domain.end(); ++it) {
            for (unsigned int d = 0; d < D; d++) {
                for (size_t j = 0; j < order; j++) {
                    
                } 
            }
        }
    }


    

