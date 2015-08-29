//many, many, many thanks to the author of this page, which very clearly and concisely explains the differences between arrays and pointers and the way that they function: http://www.lysator.liu.se/c/c-faq/c-2.html

#include <stdlib.h>
#include <stdio.h>

//potentially add restrictions for cpy, cat, and str

//note on return statements in cpy, cat, chr, and str:
//cpy and cat return _just_ variables because those variables are already pointers and by default return a memory address
//chr and str need the ampersand (&) in their return statements because, without the ampersand, they would return dereferenced variables (as a[i] is equivalent to *(a+i)); _with_ the ampersand, they return a memory address

int mystrlen(char*);
char *mystrcpy(char*,char*);
char *mystrncpy(char*,char*,int);
char *mystrcat(char*,char*);
char *mystrncat(char*,char*,int);
int mystrcmp(char*,char*);
char *mystrchr(char*,char);
char *mystrstr(char*,char*);

int main(){

  printf("\n\n");

  char test[]="testing_the_length_of_this_string";

  printf("Test for strlen:\n string: %s\n length: %d\n",test,mystrlen(test));

  printf("\n");

  char src[]="source",
    dest[]="destination";

  printf("Test for strcpy:\n before copying:\n  src: %s\n  dest: %s\n",src,dest);

  printf(" after copying:\n  src: %s\n  dest: %s\n",src,mystrcpy(dest,src));

  printf("\n");

  char src0[]="source",
    dest0[]="destination";
  int n=3;

  printf("Test for strncpy:\n before copying:\n  src: %s\n  dest: %s\n  n: %d\n",src0,dest0,n);

  printf(" after copying:\n  src: %s\n  dest: %s\n",src,mystrncpy(dest0,src0,n));

  printf("\n");

  char src1[]="source",
    dest1[]="destination";

  printf("Test for strcat:\n before concatenation:\n  src: %s\n  dest: %s\n",src1,dest1);

  printf(" after concatenation:\n  src: %s\n  dest: %s\n",src1,mystrcat(dest1,src1));

  printf("\n");

  char src2[]="source",
    dest2[]="destination";
  int m=3;

  printf("Test for strncat:\n before concatenation:\n  src: %s\n  dest: %s\n  n: %d\n",src2,dest2,m);

  printf(" after concatenation:\n  src: %s\n  dest: %s\n",src2,mystrncat(dest2,src2,m));

  printf("\n");

  char stra[]="apple",
    strb[]="pie";

  printf("Test for strcmp:\n a: %s\n b: %s\n a compared to b: %d\n",stra,strb,mystrcmp(stra,strb));

  printf("\n");

  char strc[]="pie",
    strd[]="bpple";

  printf("Test 2 for strcmp:\n a: %s\n b: %s\n a compared to b: %d\n",strc,strd,mystrcmp(strc,strd));

  printf("\n");

  char stre[]="x",
    strf[]="x";

  printf("Test for 3 strcmp:\n a: %s\n b: %s\n a compared to b: %d\n",stre,strf,mystrcmp(stre,strf));

  printf("\n");

  char s[]="string",
    c1='r',
    c2='a';

  printf("Test for strchr:\n s: %s\n c1: %c\n c2: %c\n char c1 as found in in s: [%c] at location %p\n char c2 as found in s: [%c] at location %p\n",s,c1,c2,*mystrchr(s,c1),mystrchr(s,c1),*mystrchr(s,c2),mystrchr(s,c2));

  printf("\n");

  char haystack[]="haystack",
    needle1[]="needle",
    needle2[]="sta";

  printf("Test for strstr:\n haystack: %s\n needle1: %s\n needle2: %s\n substring beginning with needle1 in haystack: [%s] at location %p (the terminating null)\n substring beginning with needle2 in haystack: [%s] at location %p\n",haystack,needle1,needle2,mystrstr(haystack,needle1),mystrstr(haystack,needle1),mystrstr(haystack,needle2),mystrstr(haystack,needle2));

  printf("\n");

  char haystack2[]="ababa",
    needle1a[]="b",
    needle2a[]="ab";

  printf("Test 2 for strstr:\n haystack: %s\n needle1: %s\n needle2: %s\n substring beginning with needle1 in haystack: [%s]\n substring beginning with needle2 in haystack: [%s]\n",haystack2,needle1a,needle2a,mystrstr(haystack2,needle1a),mystrstr(haystack2,needle2a));
  printf("(demonstrates that the function looks for the first occurence of the substring (needle), not the last or an arbitrary one)\n");

  printf("\n");

  return 0;
}

int mystrlen(char *s){
  int i=0;
  while(s[i]){
    i++;
  }
  return i;
}

char *mystrcpy(char *dest, char *src){
  int i=0;
  while(src[i]){
    dest[i]=src[i];
    i++;
  }
  //final assignment to include the terminating null; accounts for an empty string, too
  dest[i]=0;
  return dest;
}

char *mystrncpy(char *dest,char *src, int n){
  int i=0;
  while(i<n){
    dest[i]=src[i];
    i++;
  }
  dest[i]=0;
  return dest;
}

//str(n)cat can just make use of str(n)cpy
//rewriting code was not necessary

char *mystrcat(char *dest,char *src){
  int i=0,
    dest_len=mystrlen(dest);
    //printf("\ndest_len: %d\n",dest_len);
  while(src[i]){
    dest[dest_len+i]=src[i];
    i++;
  }
  dest[dest_len+i]=0;
  return dest;
}

char *mystrncat(char *dest,char *src,int n){
  int i=0,
    dest_len=mystrlen(dest);
  while(i<n){
    dest[dest_len+i]=src[i];
    i++;
  }
  dest[dest_len+i]=0;
  return dest;
}

int mystrcmp(char *a,char *b){
  int i=0;
  //without adding (&&a[i]&&b[i]), the while loop will keep comparing characters, including and _passing_ the terminating null
  //e.g. a --> [t][e][s][t][0][0][h][e][l][l][o]
  //and b ---> [t][e][e][t][0][0][w][o][r][l][d]
  //the loop would pass "test\0\0" in both and then compare the values 'h' and 'w' and return _that_, incorrectly
  while(a[i]==b[i]&&a[i]&&b[i]){
    i++;
  }
  return a[i]-b[i];
}

char *mystrchr(char *s,char c){
  int i=0;
  while(s[i]){
    if(s[i]==c){
      return &s[i];
    }
    i++;
  }
  //return s's terminating null if c does not exist in s
  return &s[i]; 
}

//this can be done more concisely
char *mystrstr(char *haystack,char *needle){
  int i=0,j=0;
  while(haystack[i]&&needle[j]){
    if(haystack[i]==needle[j]){
      i++;
      j++;
      //if you've reached the end of needle after matching all the chars, return the location of the first character of the substring in haystack
      if(!needle[j]){
      	return &haystack[i-j];
      }
    }else{
      i++;
      j=0;
    }
  }
  return &haystack[i];
}
