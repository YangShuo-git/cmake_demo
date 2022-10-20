/**
 * serverName = 1区    表示服务器名字
 * serverID = 100001   表示服务器ID
 * 
 *
 * 
 * 
 */



#include <iostream>
#include <string.h>
#include <vector>

using std::cout;

// 存放配置信息，项目中都是存放在文件中，这里做了简化
struct conf
{
    char item[40];
    char content[100];
};

// 根据name，获取对应conf的content
char *getConf(std::vector<conf *> &confList, const char *item)
{
    for (auto pos = confList.begin(); pos != confList.end(); ++pos)
    {
        if (strcmp((*pos)->item, item) == 0)
        {
            return (*pos)->content;
        } 
    }
    return nullptr;
}


int main ()
{
    conf *pConfName = new conf;
    conf *pConfID = new conf;
    std::vector<conf *> confList;

    strcpy(pConfName->item, "ServerName");
    strcpy(pConfName->content, "1区");
    strcpy(pConfID->item, "ServerID");
    strcpy(pConfID->content, "100001");  

    confList.push_back(pConfName);
    confList.push_back(pConfID);

    char *pConent = getConf(confList, "ServerName");
    if (pConent)
    {
        cout << pConent << "\n"; // 1区
    }
    pConent = getConf(confList, "ServerID");
    if (pConent)
    {
        cout << pConent << "\n"; // 100001
    }
    
    // 需要用vs2019跑一下
    //有new出来的资源，所以需要delete
    //而且这里的delete并没有破坏迭代器，因为没有往容器confList里增加/删除数据，push_back/erase
    //只是删除迭代器里元素指向的由我们自己分配的内存。
    std::vector<conf *>::iterator it;
    for (it = confList.begin(); it != confList.end(); ++it)
    {
        delete (*it);  //可以理解为 it是指向confList中元素的指针，所以（*it）是取出confList中的元素，即pConfName、pConfID
    }

    if (confList.empty())
    {
        cout << "容器已空！" << "\n";
    }
    
    confList.clear();  //这个要不要都可以，因为容器本身里边的内容，在容器失效后，系统会自动释放 
    return 0;
}