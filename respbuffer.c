//
//  respbuffer.c
//
//  Created by Robert Lee Hudspeth
//  Last Modified on 9/2/15
//

#include "respbuffer.h"

//Constructor
void init_str(struct str *s) {
	s->len = 0;
	s->ptr = (char*)(malloc(s->len+1));
	if (s->ptr == NULL) {
		printf("malloc() failed\n");
		exit(1);}
	s->ptr[0] = '\0';}

//Write to buffer and store in ptr
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct str *s) {
	size_t new_len = s->len + size*nmemb;
	s->ptr = (char*)(realloc(s->ptr, new_len+1));
	if (s->ptr == NULL) {
		printf("realloc() failed\n");
		exit(1);}
	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;}

//Reset str (Destructor)
void reset_str(struct str *s) {
	s->len = 0;
	free(s->ptr);}
