  #include <stdio.h>
  #include <stdlib.h>
  
  #define NAME_STR_LEN  32
  
  #define offsetof(type, member) (size_t)&(((type*)0)->member)
  
  #define container_of(ptr, type, member) ({ const typeof( ((type *)0)->member ) *__mptr = (ptr);\
  (type *)( (char *)__mptr - offsetof(type,member) );})
 
 typedef struct student_info
 {
     int  id;
     char name[NAME_STR_LEN];
     int  age;
 }student_info;
 
 
 int main()
 {
     size_t off_set = 0;
     off_set = offsetof(student_info, id);
     printf("id offset: %u\n",off_set);
     off_set = offsetof(student_info, name);
     printf("name offset: %u\n",off_set);
     off_set = offsetof(student_info, age);
     printf("age offset: %u\n",off_set);
     student_info *stu = (student_info *)malloc(sizeof(student_info));
     stu->age = 10;
     student_info *ptr = container_of(&(stu->age), student_info, age);
     printf("age:%d\n", ptr->age);
     printf("stu address:%p\n", stu);
     printf("ptr address:%p\n", ptr);
     return 0;
 }

