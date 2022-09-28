#include "files.h"

int main(int argc, char *argv[]) {
    int init = initialize(argc, argv);
    if (init != 0) {
	return 1;
    }
}
