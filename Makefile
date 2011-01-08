# Makefile
# Projet ASSM 2010
# J. Aceituno, Y. Tisserand

# lib: assm
assm_dir = ./libassm
assm_cppflags = -I$(assm_dir)/include
assm_ldflags = -L$(assm_dir)/lib

# lib: fftw3
fftw3_dir = /opt/local
fftw3_cppflags = -I$(fftw3_dir)/include
fftw3_ldflags = -L$(fftw3_dir)/lib -lfftw3

# lib : gtkmm
gtkmm_cppflags = `pkg-config gtkmm-2.4 --cflags`
gtkmm_ldflags = `pkg-config gtkmm-2.4 --libs`

# lib : projet
projet_dir = ./libprojet
projet_cppflags = -I$(projet_dir) -I$(projet_dir)/effets -I$(projet_dir)/interface

# libs:
librairies = assm fftw3 gtkmm projet

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

# Tous dépendent de libprojet
vpath %.h $(projet_dir) $(projet_dir)/effets $(projet_dir)/interface $(assm_dir)/include

projet_objects = $(patsubst %.cpp,%.o,$(wildcard $(projet_dir)/*.cpp))
projet_objects+= $(patsubst %.cpp,%.o,$(wildcard $(projet_dir)/interface/*.cpp))
projet_objects+= $(patsubst %.cpp,%.o,$(wildcard $(projet_dir)/effets/*.cpp))
projet_objects+= $(patsubst %.cpp,%.o,$(wildcard $(projet_dir)/imcc/*.cpp))
projet_objects+= $(patsubst %.c,%.o,$(wildcard $(projet_dir)/imcc/*.c))

##################

.PHONY: all libassm
.SECONDARY: 

all: libassm $(programmes)

libassm:
	make --directory=$(assm_dir)

%: %.src/*.cpp $(projet_objects) $(assm_dir)/lib/libassm.a
	$(LINK.cpp) $(OUTPUT_OPTION) $^

# libprojet.a: $(projet_objects)
#	$(AR) $(ARFLAGS)s $@ $^

%.o: %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $^

.PHONY: clean
clean:
	rm -rf *.o *.d $(programmes) $(addsuffix .dSYM,$(programmes)) $(addsuffix /*.o,$(programmes)) libprojet.a libprojet/*.o libprojet/interface/*.o libprojet/effets/*.o
	make --directory=$(assm_dir) clean