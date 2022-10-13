/**
 * 读取与写入结构体数据
 * 结构体字节对齐问题。
 * 字节对齐的规则如下：
 *   1.结构体的大小等于其最大成员的整数倍；
 *   2.结构体成员的首地址相对于结构体首地址的偏移量是其类型大小的整数倍。比如double型成员的首地址相对于结构体首地址的偏移量应该是8的倍数；
 *   3.满足前两条规则后，编译器会在结构体成员之后进行字节填充。
 * 
 */

#include <stdio.h>
#include <string.h>

struct stu
{
    char name[30];  // 30 
    int age;        // 4
    double score;   // 8   
    // 共42，要凑成最大成员的整数倍，最大成员是8，往上最近的整数倍为48
};

int main ()
{
    stu student[2];

    strcpy(student[0].name, "Tom");
    student[0].age = 21;
    student[0].score = 92.1f;

    strcpy(student[1].name, "jerry");
    student[1].age = 19;
    student[1].score = 86.2f;

    FILE *fp;
    fp = fopen("struct_file", "w+b");
    if (!fp)
    {
        printf("Fail to open file!\n");
    }


    printf("int = %d\n", sizeof(int));  // 4    
    printf("double = %d\n", sizeof(double)); // 8

    printf("stu size = %d\n", sizeof(stu));  // 48 = 32+8+8
    printf("student size = %d\n", sizeof(student));  // 96 = 48*2

    int ret = fwrite(&student, sizeof(stu), 2, fp);
    printf("ret = %d\n", ret); //2

    ret = fread(&student, sizeof(stu), 2, fp);
    
    fclose(fp);
    return 0;
}
