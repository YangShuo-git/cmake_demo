#include <stdio.h>

typedef struct
{
	int id;
	char name[20];
	float score;
}Student;

int max(Student* stu)
{
	int res = 0;
	res = stu->score < 60 ? -1 : 1;
	stu->score = 100;
	
	return res;
}

 
int main(void) {
	// 结构体指针初始化的两种方式
	// Student* stu1 = malloc(sizeof(Student));
	// stu1->id = 10;
	// strcpy(stu1->name, "tom");
	// stu1->score = 59;
	Student* stu1 = &(Student){
		.id = 10,
		.name = "tom",
		.score = 59,
	};

	float res = max(stu1);

	printf("name= %s \n", stu1->name);
	printf("res= %f, new score= %f \n", res, stu1->score);

	return 0;
}