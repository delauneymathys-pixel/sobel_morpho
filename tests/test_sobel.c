#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sobel.h"
#include "../include/morph.h"

int tests_passed = 0;
int tests_failed = 0;

void assert_equal(const char *test_name, unsigned char expected, unsigned char actual) {
    if (expected == actual) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: expected %d, got %d\n", test_name, expected, actual);
        tests_failed++;
    }
}

// ---- SOBEL ----
void test_sobel_uniform() {
    // Image uniforme -> gradients nuls -> sortie nulle
    int w = 5, h = 5;
    unsigned char input[25];
    unsigned char output[25];
    memset(input, 128, 25);
    memset(output, 0, 25);
    sobel(w, h, input, output);
    assert_equal("sobel: image uniforme -> sortie nulle", 0, output[1 * w + 1]);
}

void test_sobel_bord_gauche() {
    // Le bord gauche doit valoir 0
    int w = 5, h = 5;
    unsigned char input[25];
    unsigned char output[25];
    memset(input, 100, 25);
    memset(output, 99, 25);
    sobel(w, h, input, output);
    assert_equal("sobel: bord gauche = 0", 0, output[0]);
}

// ---- DILATION ----
void test_dilation_uniforme() {
    // Image uniforme -> dilation identique
    int w = 5, h = 5, window = 1;
    unsigned char input[25];
    unsigned char output[9]; // (h-2*window)*w = 3*3
    memset(input, 50, 25);
    memset(output, 0, 9);
    dilation(h, w, window, input, output);
    assert_equal("dilation: image uniforme", 50, output[0]);
}

void test_dilation_max() {
    // Un pixel blanc au centre -> dilation propage le max
    int w = 5, h = 5, window = 1;
    unsigned char input[25];
    unsigned char output[15]; // (5-2)*5
    memset(input, 0, 25);
    input[2 * w + 2] = 255; // pixel blanc au centre
    dilation(h, w, window, input, output);
    assert_equal("dilation: propage le max", 255, output[1 * w + 2]);
}

// ---- EROSION ----
void test_erosion_uniforme() {
    // Image uniforme -> erosion identique
    int w = 5, h = 5, window = 1;
    unsigned char input[25];
    unsigned char output[15];
    memset(input, 80, 25);
    memset(output, 0, 15);
    erosion(h, w, window, input, output);
    assert_equal("erosion: image uniforme", 80, output[0]);
}

void test_erosion_min() {
    // Un pixel noir au centre -> erosion propage le min
    int w = 5, h = 5, window = 1;
    unsigned char input[25];
    unsigned char output[15];
    memset(input, 255, 25);
    input[2 * w + 2] = 0; // pixel noir au centre
    erosion(h, w, window, input, output);
    assert_equal("erosion: propage le min", 0, output[1 * w + 2]);
}

int main() {
    printf("=== Tests unitaires ===\n\n");

    test_sobel_uniform();
    test_sobel_bord_gauche();
    test_dilation_uniforme();
    test_dilation_max();
    test_erosion_uniforme();
    test_erosion_min();

    printf("\n%d passed, %d failed\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}
