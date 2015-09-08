//
//  respbuffer.h
//
//  Created by Robert Lee Hudspeth
//  Last Modified on 9/2/15
//

#ifndef RESPBUFFER_H
#define RESPBUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

//Declare object of string struct, not of string class
struct str {
	char *ptr;  //Character array
	size_t len; //Length of array
};

//Constructor
void init_str(struct str *s);

//Write to buffer and store in ptr
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct str *s);

//Reset str
void reset_str(struct str *s);

#ifdef __cplusplus
}
#endif

#endif
