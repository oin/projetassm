#include "apercu_son.h"
#include <algorithm>

assm::son apercu_son::son_vide_(512, 44100);

void apercu_son::reconstruire() {
		pas_ = static_cast<size_t>(std::floor(s_.size() * 1.0 / nb_points_));
		for(size_t i = 0; i < nb_points_; ++i)
			apercu_[i] = *std::max_element(s_.data().begin() + std::min(i * pas_, s_.size() - 1), s_.data().begin() + std::min((i+1) * pas_, s_.size()));
	}