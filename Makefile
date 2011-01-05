# Makefile
# Projet ASSM 2010
# J. Aceituno, Y. Tisserand

# lib: assm
assm_dir = ./libassm
assm_cppflags = -I$(assm_dir)/include
assm_ldflags = -L$(assm_dir)/lib -lassm

# lib: fftw3
fftw3_dir = /opt/local
fftw3_cppflags = -I$(fftw3_dir)/include
fftw3_ldflags = -L$(fftw3_dir)/lib -lfftw3

# lib : gtkmm
gtkmm_cppflags = `pkg-config gtkmm-2.4 --cflags`
gtkmm_ldflags = `pkg-config gtkmm-2.4 --libs`

# libs:
librairies = assm fftw3 gtkmm

# Concaténation de toutes les choses nécessaires aux librairies
librairies_cppflags = $(foreach lib,$(librairies),$($(addsuffix _cppflags,$(lib))))
librairies_ldflags = $(foreach lib,$(librairies),$($(addsuffix _ldflags,$(lib))))

# Options à passer au compilateur
CPPFLAGS ?= -g -Wall
CPPFLAGS += $(addprefix -I,$(chercher_dans))
CPPFLAGS += $(librairies_cppflags)

# Options à passer à l'éditeur de liens
LDFLAGS ?= -lm
LDFLAGS += $(addprefix -L,$(chercher_dans))
LDFLAGS += $(librairies_ldflags)

# Tous les programmes sont pourvus de l'extension .src
programmes = $(patsubst %.src,%,$(wildcard *.src))

##################

.PHONY: all libassm

all: libassm $(programmes)

libassm:
	make --directory=$(assm_dir)

%: %.src/*.cpp $(assm_dir)/lib/libassm.a
	$(LINK.cpp) $(OUTPUT_OPTION) $^

%.o: %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $^

.PHONY: clean
clean:
	rm -rf *.o *.d $(programmes) $(addsuffix .dSYM,$(programmes)) $(addsuffix /*.o,$(programmes))
	make --directory=$(assm_dir) clean