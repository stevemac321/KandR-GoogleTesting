
/*==============================================================================
 Name        : ch01.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : Compare SM solutions to K&R and the C Answer Book (CAB).
             * This file contains the K&R and CAB solutions.

 See README at the root of this project.  Also krtest comment header.
==============================================================================*/
#include <cstdio>
#include <cassert>
#include <tuple>
#include <iostream>
#include <vector>
/* C Answer Book Version (a.k.a. "CAB"): blank, tab, and newline count */
std::tuple<int,int,int>  Base_1_8()
{
	int c = 0;
	int nb = 0;
	int nt = 0;
	int nl = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	while ((c = getc(pf)) != EOF) {
		if (c == ' ')
			++nb;
		if (c == '\t')
			++nt;
		if (c == '\n')
			++nl;
	}

	fclose(pf);

        return std::make_tuple(nb,nt,nl);
}
/*CAB version of remove duplicate spaces. */
void Base_1_9()
{

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

        FILE *out = fopen("./baselogs/1_9.exp", "w");
        assert(out);

        int c = 0;
        int lastc = 0;

        while((c = getc(pf)) != EOF) {
                if(c != ' ' && lastc != ' ')
                        putc(c, out);

                lastc = c;
        }

        fclose(pf);
        fclose(out);
}
/* CAB make whitespace visible */
void Base_1_10()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
        assert(pf);
	FILE *out = fopen("./testlogs/1_10.tst", "w");
	assert(out);

        int c = 0;
        int last='a';
        while((c = getc(pf)) != EOF) {
                if(c == '\t')
                        fprintf(out, "\\t");
                else if(c == '\b')
                        fprintf(out, "\\b");
                else if(c == '\\')
                        fprintf(out, "\\\\");
                else
                        putc(c, out);
        }

        fclose(pf);
        fclose(out);
}
/*KR version of word count: 1.5.4 pg. 20 2nd ed.*/
std::tuple<int,int,int>  Base_1_11()
{
        const unsigned int IN = 1;
        const unsigned int OUT = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int c=0;
        int nl = 0;
        int nc = 0;
        int nw = 0;
        int state = OUT;

        while((c = getc(pf)) != EOF) {
                ++nc;
                if(c == '\n')
                        ++nl;

                if(c == ' ' || c == '\n' || c == '\t')
                        state = OUT;
                else if(state == OUT) {
                        state = IN;
                        ++nw;
                }

        }
        
        fclose(pf);
        return std::make_tuple(nl, nw, nc);
}
/* CAB version of 1-12. */
void Base_1_12()
{
        const unsigned int IN = 1;
        const unsigned int OUT = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);
	FILE *out = fopen("./baselogs/1_12.exp", "w");
	assert(out);

	int c=0;
        int state = OUT;

        while((c = getc(pf)) != EOF) {
                if(c == ' ' || c == '\n' || c == '\t') {
                        if(state == IN) {
                                putc('\n', out);
                                state = OUT;
                        }
                }else if(state == OUT) {
                        state = IN;
                        putc(c, out);
                }else
                        putc(c, out);
        }
        
        fclose(pf);
        fclose(out);
}
/* CAB version of 1.13 */
std::vector<int> Base_1_13()
{
        const unsigned int  MAXWORD=1000;
        const unsigned int  MAXHIST=64;
        const unsigned int IN = 1;        
        const unsigned int OUT = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

        int c=0;
        int len = 0;
        int nc = 0;
        int ovflow = 0;
        int state = OUT;
        
        /* wc utility informs us that kmod has less than 700 words */
        int wl[MAXWORD];
        
        for(int i=0; i < MAXWORD; i++)
                wl[i]=0;

        while((c = getc(pf)) != EOF) {
                if(c == ' ' || c == '\n' || c == '\t') {
                        state = OUT;
                        if(nc > 0)
                                if(nc < MAXWORD)
                                        ++wl[nc];
                                else
                                        ++ovflow;
                        nc = 0;
                } else if(state == OUT) {
                        state = IN;
                        nc = 1;
                }else
                        ++nc;
        }

        std::vector<int> v;
        for(size_t i=0; i < MAXWORD; i++)
                if(wl[i] > 0)
                        v.push_back(wl[i]);

        return v;
}
std::vector<int> Base_1_14()
{
        const unsigned int MAXHIST = 15;
        const unsigned int MAXCHAR = 128;
        int c=0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

        int cc[MAXCHAR];
        for(int i=0; i < MAXCHAR; i++)
                cc[i] = 0;

        while((c = getc(pf)) != EOF)
                if(c < MAXCHAR)
                        ++cc[c];

        fclose(pf);
        std::vector<int> v;
        for(int i=0; i < MAXCHAR; i++)
                v.push_back(cc[i]);

        return v;
}
