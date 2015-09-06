/*
 * studio.c
 *
 *  Created on: 2015年6月12日
 *      Author: Administrator
 */
#include "Studio.h"
#include "../Persistence/Studio_Persist.h"
#include <stdlib.h>
#include <assert.h>

//向文件中添加影厅信息,失败返回0成功返回写入信息的个数
inline int Studio_Srv_Add(const studio_t *data) {
	return Studio_Perst_Insert(data);
}

//向文件中更新修改的数据,成功返回1,失败返回0
inline int Studio_Srv_Modify(const studio_t *data) {
	return Studio_Perst_Update(data);
}

//通过ID删除某个演出厅信息,成功返回1,失败返回0
inline int Studio_Srv_DeleteByID(int ID) {
	return Studio_Perst_DeleteByID(ID);
}

//根据ID获取相应演出厅的信息,成功返回1,失败返回0
inline int Studio_Srv_FetchByID(int ID, studio_t *buf) {
	return Studio_Perst_SelectByID(ID, buf);

}

//将所有的信息载入链表,失败返回0,成功返回载入的个数
inline int Studio_Srv_FetchAll(studio_list_t list) {
	return Studio_Perst_SelectAll(list);
}

//通过ID在list中查找对应放映厅结点,成功返回节点指针,失败返回空
inline studio_node_t *Studio_Srv_FindByID(studio_list_t list, int ID){
	assert(NULL!=list);
	studio_node_t *ptr=list->next;
	while(ptr!=list){
		if(ptr->data.id==ID)
			return ptr;
		else
			ptr=ptr->next;
	}

	return NULL;
}
