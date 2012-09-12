// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream

// ----------------
// global variables
// ----------------

const int SIZE = 1000001;
long long cache[SIZE];

// -------------------
// collatz_compute_cyc
// -------------------

/**
 * compute cycle length for arg
 * @param arg integer whose cycle length to be computed
 * @return the cycle length of arg
 */
int collatz_compute_cyc(long long arg) {
	assert(arg > 0);
	//Case 1: arg = 1, simply return 1.
	if (arg == 1) return 1;
	//Case 2: arg <= 1,000,000, in cache, simply use cache.
	if (arg < SIZE && cache[arg]) return cache[arg];
	//Case 3: arg <= 1,000,000, NOT in cache.
	if (arg < SIZE) {
		if (arg & 1) cache[arg] = 2 + collatz_compute_cyc(arg + (arg >> 1) + 1); //if arg is odd.
		else cache[arg] = 1 + collatz_compute_cyc(arg >> 1); //if arg is even.
		return cache[arg];
	}
	//Case 4: arg > 1,000,000, NOT in cache, of course.
	if (arg >= SIZE) {
		if (arg & 1) return 2 + collatz_compute_cyc(arg + (arg >> 1) + 1); //if arg is odd.
		else return 1 + collatz_compute_cyc(arg >> 1); //if arg is even.
	}
	return -1; //other cases indicate error (assertion in eval() will catch it).
}

// ------------
// collatz_read
// ------------

/**
 * reads two ints into i and j
 * @param r a  std::istream
 * @param i an int by reference
 * @param j an int by reference
 * @return true if that succeeds, false otherwise
 */
bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    int max_cycle = 0, c = (i <= j) ? i : j, max = (i > j) ? i : j;
    c = (c < max / 2) ? (max / 2) : c;
    int cur_cyc;
    for (; c <= max; c++) {
	cur_cyc = collatz_compute_cyc(c);
	assert(cur_cyc > 0);
	max_cycle = (max_cycle >= cur_cyc) ? max_cycle : cur_cyc;
    } 
    assert(max_cycle > 0);
    return max_cycle;}

// -------------
// collatz_print
// -------------

/**
 * prints the values of i, j, and v
 * @param w a std::ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

/**
 * read, eval, print loop
 * @param r a std::istream
 * @param w a std::ostream
 */
void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
