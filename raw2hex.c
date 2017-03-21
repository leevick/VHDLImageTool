#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc,char* argv[])
{
    FILE *p = fopen(argv[1],"rb");
    FILE *q = fopen("hex.data","wb+");
    unsigned char *byte = (unsigned char *)malloc(1);
    unsigned char *buffer = (unsigned char*)malloc(1024*1024*16);
    int cnt=0;
    int flag =0;
    while(!feof(p))
    {
        flag = 1-cnt%2*2;
        fread(byte,1,1,p);
        for(int i=0;i<8;i++)
        {
            if((byte[0]>>i)&0x01==0x01)
            {
                buffer[cnt*8+7-i+8*flag]=0x03;
            }else
            {
                buffer[cnt*8+7-i+8*flag]=0x02;
            }
        }
        cnt++;
    }
    fwrite(buffer,1,(cnt-1)*8,q);
    fclose(p);
    fclose(q);
    free(byte);
    free(buffer);

}