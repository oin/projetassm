#if !defined(__ITERATOR_BIN_HPP)
#define __ITERATOR_BIN_HPP

#include <iterator>
#include <iostream>

// Adapté librement de http://stackoverflow.com/questions/1855704/c-binary-file-i-o-to-from-containers-other-than-char-using-stl-algorithms/1856092#1856092

template <class T>
struct input_iterator_bin : public std::iterator<std::input_iterator_tag, T> {
	input_iterator_bin(std::istream& s) : s_(&s) {}
	input_iterator_bin() : s_(0) {}
	input_iterator_bin& operator++() { return *this; }
	input_iterator_bin& operator++(int) { return *this; }
	T& operator*() {
		static T actuel;
		s_->read(reinterpret_cast<char*>(&actuel), sizeof(T));
		return actuel;
	}
	bool operator!=(input_iterator_bin const& c) {
		bool fini = (s_ == 0 || !s_->good());
		bool c_fini = (c.s_ == 0 || !c.s_->good());
		return !(fini && c_fini);
	}
private:
	std::istream* s_;
};

template <class T>
struct output_iterator_bin : public std::iterator<std::output_iterator_tag, void, void, void, void> {
	output_iterator_bin(std::ostream& s) : s_(s) {}
	output_iterator_bin& operator++() { return *this; }
	output_iterator_bin& operator++(int) { return *this; }
	output_iterator_bin& operator*() { return *this; }
	output_iterator_bin& operator=(T const& d) {
		s_.write(reinterpret_cast<char const*>(&d), sizeof(T));
		return *this;
	}
private:
	std::ostream& s_;
};

#endif