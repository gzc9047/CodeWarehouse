#include <stdio.h>
#define C '"'
#define T '\\'
#define N '\n'
const char * src1 = "#include <stdio.h>%c#define C '%c'%c#define T '%c%c'%c#define N '%cn'%cconst char * src1 = %c%s%c;int main(){printf(src1,N,C,N,T,T,N,T,N,C,src1,C);return 0;}";int main(){printf(src1,N,C,N,T,T,N,T,N,C,src1,C);return 0;}

