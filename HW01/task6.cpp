#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " N\n";
        return 1;
    }

    int N = std::stoi(argv[1]);

    // (b) ascending, 0..N, with printf, space-separated, trailing newline
    for (int i = 0; i <= N; ++i) {
        if (i > 0) printf(" ");
        printf("%d", i);
    }
    printf("\n");

    // (c) descending, N..0, with std::cout, space-separated, trailing newline
    for (int i = N; i >= 0; --i) {
        if (i < N) std::cout << ' ';
        std::cout << i;
    }
    std::cout << '\n';

    return 0;
}