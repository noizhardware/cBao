#ifndef __HTML_H__
#define __HTML_H__
/* 202007241418 */

/* C90 compliant <3 */

#include <stdbool.h>
#include "baostring.h"
#include "baoutil.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
<canvas id="myCanvas">Your browser does not support the HTML5 canvas tag.</canvas>
htmlMakeTagOpen h1 >> <h1>
htmlMakeTagClose
 */

/* prototypes */
static __inline__ char* htmlHeader(char* input, unsigned char headerNum, bool freeTheSource);
static __inline__ char* htmlParagraph(char* input, bool freeTheSource);
static __inline__ char* htmlBold(char* input, bool freeTheSource);
static __inline__ char* htmlItalic(char* input, bool freeTheSource);
static __inline__ char* htmlCenter(char* input, bool freeTheSource);
static __inline__ char* htmlBr(); /* newline*/
static __inline__ char* htmlHr(); /* horizontal ruler*/
static __inline__ char* htmlLinkExt(char* address, char* text, bool freeTheSources);
static __inline__ char* htmlLinkLoc(char* address, char* text, bool freeTheSources);
static __inline__ char* htmlList(char** list, bool freeTheSource);
/************************/

static __inline__ char* htmlHeader(char* input, unsigned char headerNum, bool freeTheSource){ /* headernum must be <10*/
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(input)+11); /* 1 terminator + 10 chars "<hx></hx>\n" */
     memcpy(output, "<h", 3);
     output = appendChar(output, digitToChar(headerNum), true);
     output = appendChar(output, '>', true);
     output = appendString(output, input, true);
     output = appendString(output, "</h", true);
     output = appendChar(output, digitToChar(headerNum), true);
     output = appendString(output, ">\n", true);
     if(freeTheSource){
          free(input);} /* frees the old allocation*/
     return output;}
     
static __inline__ char* htmlParagraph(char* input, bool freeTheSource){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(input)+9); /* 1 terminator + 8 chars "<p></p>\n" */
     memcpy(output, "<p>", 4);
     output = appendString(output, input, true);
     output = appendString(output, "</p>\n", true);
     if(freeTheSource){
          free(input);} /* frees the old allocation*/
     return output;}
     
static __inline__ char* htmlBold(char* input, bool freeTheSource){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(input)+8); /* 1 terminator + 7 chars "<b></b>" */
     memcpy(output, "<b>", 4);
     output = appendString(output, input, true);
     output = appendString(output, "</b>", true);
     if(freeTheSource){
          free(input);} /* frees the old allocation*/
     return output;}
     
static __inline__ char* htmlItalic(char* input, bool freeTheSource){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(input)+8); /* 1 terminator + 7 chars "<i></i>" */
     memcpy(output, "<i>", 4);
     output = appendString(output, input, true);
     output = appendString(output, "</i>", true);
     if(freeTheSource){
          free(input);} /* frees the old allocation*/
     return output;}
     
static __inline__ char* htmlCenter(char* input, bool freeTheSource){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(input)+18); /* 1 terminator + 17 chars "<center></center>" */
     memcpy(output, "<center>", 9);
     output = appendString(output, input, true);
     output = appendString(output, "</center>", true);
     if(freeTheSource){
          free(input);} /* frees the old allocation*/
     return output;}
     
static __inline__ char* htmlBr(){ /* newline*/
     char* output; /* new internal char* */
     output = (char*)malloc(6); /* 1 terminator + 5 chars "<br>\n" */
     memcpy(output, "<br>\n", 6);
     return output;}
     
static __inline__ char* htmlHr(){ /* horizontal ruler*/
     char* output; /* new internal char* */
     output = (char*)malloc(6); /* 1 terminator + 5 chars "<hr>\n" */
     memcpy(output, "<hr>\n", 6);
     return output;}
     
static __inline__ char* htmlLinkExt(char* address, char* text, bool freeTheSources){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(address)+strlen(text)+49); /* 1 terminator + 48 chars <a href="" target="_blank" class="external"></a> */
     memcpy(output, "<a href=\"", 10);
     output = appendString(output, address, true);
     output = appendString(output, "\" target=\"_blank\" class=\"external\">", true);
     output = appendString(output, text, true);
     output = appendString(output, "</a>", true);
     if(freeTheSources){
          free(address);
          free(text);} /* frees the old allocations */
     return output;}
     
static __inline__ char* htmlLinkLoc(char* address, char* text, bool freeTheSources){
     char* output; /* new internal char* */
     output = (char*)malloc(strlen(address)+strlen(text)+35); /* 1 terminator + 34 chars <a href=".html" class="local"></a> */
     memcpy(output, "<a href=\"", 10);
     output = appendString(output, address, true);
     output = appendString(output, ".html", true);
     output = appendString(output, "\" class=\"local\">", true);
     output = appendString(output, text, true);
     output = appendString(output, "</a>", true);
     if(freeTheSources){
          free(address);
          free(text);} /* frees the old allocations */
     return output;}
     
static __inline__ char* htmlList(char** list, bool freeTheSource){
     char* output; /* new internal char* */
     int i;
     output = (char*)malloc(12+sizeof(list)+(ARRAYELEMS(list)*11)); /* 1 terminator + 11 chars <ul>\n</ul>\n + 11 char \t<li></li>\n per each element*/
     memcpy(output, "<ul>\n", 6);
     for(i = 0; i < ARRAYELEMS(list); i++){
          output = appendString(output, "\t<li>", true);
          output = appendString(output, list[i], true);
          output = appendString(output, "</li>\n", true);}
     output = appendString(output, "</ul>\n", true);
     if(freeTheSource){
          free(list);} /* frees the old allocation*/
     return output;}

#ifdef __cplusplus
}
#endif

#endif /* __HTML_H__ */