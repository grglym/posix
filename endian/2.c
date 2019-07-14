#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
	unsigned long addr = inet_addr("192.168.0.100");
	printf("addr = %u\n", ntohl(addr));
	return 0;
}
