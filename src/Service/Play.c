#include "Play.h"
#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>

// 新增数据为为data的剧目信息服务
inline int Play_Srv_Add(const play_t *data) {
       return Play_Perst_Insert(data);
}
// 修改主键为ID的剧目信息服务
inline int Play_Srv_Modify(const play_t *data) {
       return Play_Perst_Update(data);
}
// 删除主键为ID的剧目信息服务
inline int Play_Srv_DeleteByID(int ID) {
       return Play_Perst_DeleteByID(ID);
}
// 查找主键为ID的剧目信息,并将其信息保存在buf所指的内存单元中
inline int Play_Srv_FetchByID(int ID, play_t *buf) {
	return Play_Perst_SelectByID(ID,buf);
}
// 获取所有剧目服务
inline int Play_Srv_FetchAll(play_list_t list) {
       return Play_Perst_SelectAll(list);
}

//根据剧目名称载入剧目，返回载入的剧目数量
int Play_Srv_FetchByName(play_list_t list, char condt[]){
       return Play_Perst_SelectByName(list,condt);
}



//根据剧目名称过滤词filter对list进行过滤，返回过滤后剩余的剧目数量
int Play_Srv_FilterByName(play_list_t list, char filter[]){
	int PlayCount = 0;
	play_list_t pNew = list->next;
	PlayCount = Play_Srv_FetchAll(list);
	pNew = list->next;
	while(pNew != list)
	{
		if (strcmp(pNew->data.name,filter) == 0)
		{
			List_FreeNode(pNew);
			PlayCount--;
		}
		pNew = pNew->next;		
	}
       	return PlayCount;
}


