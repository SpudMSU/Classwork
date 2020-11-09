/**
 * @file
 * Simple main function designed to exercise and test bin2dec
 */

#include <stdio.h>
#include "bin2dec.h"

/*
 * Forward references
 */
void test_binary(const char *binary);

/**
 * Program main entry point 
 */
int main()
{
	printf("%u\n", bin2dec("TFTFFFTTT"));
    test_binary("F");
    test_binary("T");
    test_binary("TFT F T");
    test_binary("T T");
    test_binary("T F F T");
    test_binary("T");
    test_binary("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
    test_binary("FTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
    test_binary("FTTTTTTTTTTTFTTTTTTFTTTTTTTTTTTT");
    test_binary("TF");
    test_binary("TFF");
    test_binary("TFFF");
    test_binary("TFFFF");
    test_binary("TFFF");
    test_binary("aTFcT TT");
    return 0;
}

/**
 * A simple function that converts a binary number and displays the result
 */
void test_binary(const char *binary)
{
    printf("'%s' converts to %u\n", binary, bin2dec(binary));
}
