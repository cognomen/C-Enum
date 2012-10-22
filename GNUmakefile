PROJ := test.out

DOS2UNIX := echo 2>&1 > /dev/null
INDENT := indent
DOXYGEN := doxygen

INCLUDES := \
		-I. \
		-Itest \

DEFINES := -g -std=c99 -pedantic -DUNIT_TEST=test_enum

INDENT_FLAGS := --k-and-r-style \
				--blank-lines-after-declarations \
				--braces-after-if-line \
				--brace-indent0 \
				--break-function-decl-args \
				--cuddle-do-while \
				--declaration-comment-column0 \
				--no-tabs \
				--line-length78

#--blank-lines-after-commas \

CSRCS := \
	test/test_enum.c \
	test/main.c \

COBJS := $(patsubst %.c, %.o, $(filter %.c,$(CSRCS)))
CPREPS := $(patsubst %.c, %.E, $(filter %.c,$(CSRCS)))

EXAMPLE := example.out
EXAMPLE_CSRCS := \
	example/example_main.c \
	example/shape.c \

EXAMPLE_COBJS := $(patsubst %.c, %.o, $(filter %.c,$(EXAMPLE_CSRCS)))
EXAMPLE_CPREPS := $(patsubst %.c, %.E, $(filter %.c,$(EXAMPLE_CSRCS)))

.PHONY: prep all clean docs test example

all: test example docs
test: $(PROJ)
example: $(EXAMPLE)

prep: $(CPREPS)
example_prep: $(EXAMPLE_CPREPS)

%.E : %.c enum.h
	$(CC) $(DEFINES) -D PREPROCESS $(INCLUDES) -E -P -o $@ $<
	$(DOS2UNIX) $@
	$(INDENT) $(INDENT_FLAGS) $@

%.o : %.c enum.h
	$(CC) -c $(DEFINES) $(INCLUDES) -o $@ $<

$(PROJ) : $(COBJS)
	$(CC) -o $@ $(COBJS)

$(EXAMPLE) : $(EXAMPLE_COBJS)
	$(CC) -o $@ $(EXAMPLE_COBJS)

docs:
	$(DOXYGEN) Doxyfile

clean:
	@-$(RM) -rf $(COBJS) $(CPREPS) $(PROJ) doc
	@-$(RM) -rf $(EXAMPLE_COBJS) $(EXAMPLE_CPREPS) $(EXAMPLE)
