
/*==============================================================================
 Name        : ch01.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : Compare SM solutions to K&R and the C Answer Book (CAB).
	     * this file contains the SM solutions.

 See README at the root of this project.  Also krtest comment header.
==============================================================================*/
#include <cstdio>
#include <cassert>
#include <tuple>
#include <iostream>
#include <vector>
#include <cstring>

/* SM version (note not very different from CAB. */
std::tuple<int, int, int> Test_1_8()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int blanks = 0;
	int tabs = 0;
	int newlines = 0;
	int c = 0;

	while ((c = getc(pf)) != EOF) {
		if (c == ' ')
			++blanks;
		else if (c == '\t')
			++tabs;
		else if (c == '\n')
			++newlines;
	}
	fclose(pf);
	return std::make_tuple(blanks, tabs, newlines);
}
/* SM version */
void Test_1_9()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);
	FILE *out = fopen("./testlogs/1_9.tst", "w");
	assert(out);

	int c = 0;
	int last = 'a';
	while ((c = getc(pf)) != EOF) {
		if (c != ' ' && last != ' ')
			putc(c, out);

		last = c;
	}

	fclose(pf);
	fclose(out);
}

/* SM version */
void Test_1_10()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);
	FILE *out = fopen("./testlogs/1_10.tst", "w");
	assert(out);

	int c = 0;
	int last = 'a';
	while ((c = getc(pf)) != EOF) {
		if (c == '\t')
			fprintf(out, "\\t");
		else if (c == '\\')
			fprintf(out, "\\\\");
		else
			putc(c, out);
	}

	fclose(pf);
	fclose(out);
}
/*SM version of word count*/
std::tuple<int, int, int> Test_1_11()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int c = 0;
	int lines = 0;
	int words = 0;
	int chars = 0;
	bool in_word = false;

	while ((c = getc(pf)) != EOF) {
		++chars;
		if (c == '\n')
			++lines;

		if (c == ' ' || c == '\n' || c == '\t')
			in_word = false;
		else if (in_word == false) {
			in_word = true;
			++words;
		}
	}

	fclose(pf);
	return std::make_tuple(lines, words, chars);
}
/* SM version */
void Test_1_12()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);
	FILE *out = fopen("./testlogs/1_12.tst", "w");
	assert(out);

	int c = 0;
	bool inword = false;

	while ((c = getc(pf)) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n') {
			inword = true;
			putc(c, out);
		} else if (inword == true) {
			putc('\n', out);
			inword = false;
		}
	}

	fclose(pf);
	fclose(out);
}
/* SM histogram lengths of words */
std::vector<int> Test_1_13()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);
        const unsigned int ARMAX = 1000;
        const unsigned int WORDMAX = 64;
	int wl[ARMAX];
	for (int i = 0; i < ARMAX; i++)
		wl[i] = 0;

	bool inword = false;
	char buf[WORDMAX];
	char *p = buf;

	while ((*p = getc(pf)) != EOF) {
		if (*p == ' ' || *p == '\n' || *p == '\t') {
			inword = false;
			if ((p - buf) > 0 && (p-buf) < WORDMAX) {
				*p = '\0';
				++wl[strlen(buf)];
				p = buf;
			}
		} else {
			++p;
			inword = true;
		}
	}

	fclose(pf);
	std::vector<int> v;
	for (int i = 0; i < ARMAX; i++)
		if (wl[i] > 0)
			v.push_back(wl[i]);
	return v;
}
std::vector<int> Test_1_14()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	const unsigned int SZ = 128;
	int table[SZ];

	for (int i = 0; i < SZ; i++)
		table[i] = 0;

	int c = 0;

	while ((c = getc(pf)) != EOF)
                if(c >= 0 && c < SZ)
		        table[c]++;

	fclose(pf);
        std::vector<int> v;
        for(int i=0; i < SZ; i++)
                v.push_back(table[i]);

        return v;
}
