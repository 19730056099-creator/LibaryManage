#include <stdio.h>
#define MAX_BOOKS 1000

struct Book {
    char id[20];
    char title[100];
    char author[100];
    int quantity;
    int available;
};

struct Book books[MAX_BOOKS];

int bookCount = 0;
//bookCount表示当前实际有几本书

//该函数负责查找,不要在里面直接打印提示
int findBookIndex{
    //从1遍历到bookCount-1
    //  如果 books[i].id 和 目标 id 相同
    //    返回 i
    //遍历结束
    //放回 -1
    
};
//ques:C语言中返回0,1,-1分别代表什么意思

int addBook(){
    //如果 bookCount >= 1000
    //    返回 0
    //如果 findBookIndex()id != -1
    //    返回 0

    //从传入的数据复制到 books[bookCount]
    //bookCount++
    //返回 1
    
};

void listAllBooks();

void displayMenu();

//以下这个main()中为什么要填写void，这里面有什么说法么
int main(void){
    //菜单循环
}