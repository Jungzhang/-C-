#ifndef PLAY_H_
#define PLAY_H_

#include "../Common/Common.h"

//剧目类型枚举
typedef enum {
	PLAY_TYPE_FILM=1,			//
	PLAY_TYPE_OPEAR=2,			//歌剧
	PLAY_TYPE_CONCERT=3			//音乐会
} play_type_t;

//剧目等级枚举
typedef enum {
	PLAY_RATE_CHILD = 1,		//小孩
	PLAY_RATE_TEENAGE = 2,		//青少年
	PLAY_RATE_ADULT = 3			//成年
} play_rating_t;


//剧目实体数据类型定义
typedef struct {
	int id;						//剧目ID
	char name[31];				//剧目名称
	play_type_t type;			//剧目类型
	char area[9];				//剧目出品地区
	play_rating_t rating;		//剧目等级
	int duration; 				//剧目时长,以分钟为单位
	user_date_t start_date;		//开始放映时间
	user_date_t end_date;		//结束放映时间
	int price;					//票价
} play_t;

//剧目链表节点定义
typedef struct play_node {
	play_t data;							//剧目实体数据类型
	struct play_node *next, *prev;			//后向和前向指针
} play_node_t, *play_list_t;				

inline int Play_Srv_Add(const play_t *data);

inline int Play_Srv_Modify(const play_t *data);

inline int Play_Srv_DeleteByID(int ID);

inline int Play_Srv_FetchByID(int ID, play_t *buf);

inline int Play_Srv_FetchAll(play_list_t list);

//根据剧目名称载入剧目，返回载入的剧目数量
inline int Play_Srv_FetchByName(play_list_t list, char condt[]);

//根据剧目名称过滤词filter对list进行过滤，返回过滤后剩余的剧目数量
int Play_Srv_FilterByName(play_list_t list, char filter[]);

#endif //PLAY_H_
