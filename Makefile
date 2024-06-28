.PHONY: run clean
all: gcc/test gcc/test-tsan clang/test clang/test-tsan

gcc/test: test.cpp Makefile
	mkdir -p gcc
	g++ -o $@ -O2 -g -pthread $(LDFLAGS) $<
	-$@
gcc/test-tsan: test.cpp Makefile
	mkdir -p gcc
	g++ -o $@ -O2 -g -pthread -fsanitize=thread $(LDFLAGS) $<
	-$@
clang/test: test.cpp Makefile
	mkdir -p clang
	clang++ -o $@ -O2 -g -pthread $(LDFLAGS) $<
	-$@
clang/test-tsan: test.cpp Makefile
	mkdir -p clang
	clang++ -o $@ -O2 -g -pthread -fsanitize=thread $(LDFLAGS) $<
	-$@

clean:
	rm -rf gcc clang tsan.* ubsan.*
