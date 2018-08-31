/*
1）运算符：rope支持operator += -= + - < ==
2）输入输出：可以用<<运算符由输入输出流读入或输出。
3）长度/大小：调用length()，size()都可以哦
4）插入/添加等：
    push_back(x);//在末尾添加x
    insert(pos,x);//在pos插入x，自然支持整个char数组的一次插入
    erase(pos,x);//从pos开始删除x个
    copy(pos,len,x);//从pos开始到pos+len为止用x代替
    replace(pos,x);//从pos开始换成x
    substr(pos,x);//提取pos开始x个
    at(x)/[x];//访问第x个元素
    
#include <ext/rope>
using namespace __gnu_cxx;
*/
