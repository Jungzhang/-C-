#include "Play.h"
#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>

// ��������ΪΪdata�ľ�Ŀ��Ϣ����
inline int Play_Srv_Add(const play_t *data) {
       return Play_Perst_Insert(data);
}
// �޸�����ΪID�ľ�Ŀ��Ϣ����
inline int Play_Srv_Modify(const play_t *data) {
       return Play_Perst_Update(data);
}
// ɾ������ΪID�ľ�Ŀ��Ϣ����
inline int Play_Srv_DeleteByID(int ID) {
       return Play_Perst_DeleteByID(ID);
}
// ��������ΪID�ľ�Ŀ��Ϣ,��������Ϣ������buf��ָ���ڴ浥Ԫ��
inline int Play_Srv_FetchByID(int ID, play_t *buf) {
	return Play_Perst_SelectByID(ID,buf);
}
// ��ȡ���о�Ŀ����
inline int Play_Srv_FetchAll(play_list_t list) {
       return Play_Perst_SelectAll(list);
}

//���ݾ�Ŀ���������Ŀ����������ľ�Ŀ����
int Play_Srv_FetchByName(play_list_t list, char condt[]){
       return Play_Perst_SelectByName(list,condt);
}



//���ݾ�Ŀ���ƹ��˴�filter��list���й��ˣ����ع��˺�ʣ��ľ�Ŀ����
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


