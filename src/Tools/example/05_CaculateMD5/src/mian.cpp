#include "MD5.h"
#include <iostream>
using namespace std;
 
int main() {
 
	int i;
	unsigned char encrypt[] = "admin";//"admin";//21232f297a57a5a743894a0e4a801fc3
	unsigned char decrypt[16];

	MD5_CTX md5;

	MD5Init(&md5);
	MD5Update(&md5, encrypt, (int)strlen((char*)encrypt));//ֻ�Ǹ��м䲽��
	MD5Final(&md5, decrypt);//32λ

	printf("����ǰ:%s\n���ܺ�16λ:", encrypt);
	for (i = 4; i < 12; i++) {
		printf("%02x", decrypt[i]);
	}


	printf("\n����ǰ:%s\n���ܺ�32λ:", encrypt);
	for (i = 0; i < 16; i++) {
		printf("%02x", decrypt[i]);
	}

 
    return 0;
}
