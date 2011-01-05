#if !defined(__ITERATOR_PART_HPP)
#define __ITERATOR_PART_HPP

#include <iterator>

template <class It>
struct iterator_part : public std::iterator<std::input_iterator_tag, void, void, void, void> {
	iterator_part(It& itp, size_t taille = 0) : itc_(itp), taille_(taille), actuel_(0) {}
	iterator_part(const It& itp) : itc_(const_cast<It&>(itp)), taille_(0), actuel_(0) {}
	iterator_part& operator++() { ++actuel_; ++itc_; return *this; }
	iterator_part& operator++(int) { ++actuel_; itc_++; return *this; }
	typename std::iterator_traits<It>::reference operator*() {
		return *itc_;
	}
	bool operator!=(iterator_part const& c) {
		if(actuel_ == taille_) {
			actuel_ = 0; return false;
		}
		return itc_ != c.itc_;
	}
private:	
	It& itc_;
	size_t taille_, actuel_;
};

template <class It>
iterator_part<It> iterator_parter(It& itd, size_t taille = 0) {
	return iterator_part<It>(itd, taille);
};

template <class It>
iterator_part<It> iterator_parter(const It& itd) {
	return iterator_part<It>(itd);
};

#endif