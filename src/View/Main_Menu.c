#include <stdio.h>

#include "Main_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "Queries_Menu.h"
#include "Account_UI.h"
#include "Sale_UI.h"
#include "SalesAnalysis_UI.h"
#include "Welcome.h"
#include "GoodBye.h"

void Main_Menu(void) {
	char choice;
	Welcome();
	sleep(3);
	do {
		system("clear");
		printf("\n\n\n\n\n\t\t\t==================================================================\n");
		printf("\t\t\t***************** 剧 院 票 务 信 息 管 理 系 统 ******************\n");
		printf("\n\t\t\t------------------------------------------------------------------\n");
		printf("\t\t\t\t\t\t[S]演出厅管理.\n");
		printf("\t\t\t\t\t\t[P]剧目管理.\n");
		printf("\t\t\t\t\t\t[T]售票管理.\n");
		printf("\t\t\t\t\t\t[R]退票管理.\n");
		printf("\t\t\t\t\t\t[Q]查询菜单\n");
		//printf("Ra[n]king and Statistics.\n");
		printf("\t\t\t\t\t\t[A]账号管理.\n");
		printf("\t\t\t\t\t\t[E]退出系统.\n");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t请选择:");
		setbuf(stdin,NULL);
		choice = getchar();
		setbuf(stdin,NULL);
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(0);
			break;
		case 'Q':
		case 'q':
			Queries_Menu();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
			Sale_UI_ReturnTicket();
			break;
		//case 'N':
		//case 'n':
		//	SalesAanalysis_UI_MgtEntry();
		//	break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry();
			break;
		}
	} while ('E' != choice && 'e' != choice);
	GoodBye();
	sleep(1);
}

