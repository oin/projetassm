vpath %.c src
vpath %.cpp src
vpath %.h include
vpath %.hpp include
vpath %.a lib

CPPFLAGS ?= -g -Wall -I/opt/local/include -Iinclude

sources = $(wildcard $(foreach ext,*.c *.cpp,src/$(ext)))
objects = $(subst .c,.o,$(subst .cpp,.o,$(sources)))

###
# $(call make-depend,source-file,object-file,depend-file)
define make-depend
	gcc -MM -MF dep/$(notdir $3) -MP -MT $2 $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $1
endef
###

LIB=lib/libassm.a

$(LIB): $(objects)
	$(AR) $(ARFLAGS)s $@ $^

%.o: %.c
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.o: %.cpp
	$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

gnuplot_i.o: CFLAGS += -Wno-write-strings

.PHONY: clean
clean:
	rm -rf src/*.o dep/*.d $(LIB)

# Inclut les dépendances des fichiers sources
ifneq "$(MAKECMDGOALS)" "clean"
-include $(addprefix dep/,$(notdir $(subst .o,.d,$(objects))))
endif