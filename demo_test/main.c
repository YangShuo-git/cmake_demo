#include <stdio.h>

void boy_home(int* meipo) {
	static int boy = 23;
	meipo = &boy;
}
 
int main(void) {
	int* meipo = NULL;
	boy_home(meipo);
	printf("%d\n",*meipo);
	return 0;
}