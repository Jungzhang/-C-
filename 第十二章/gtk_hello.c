/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-19 02:27
 * Filename	 : gtk_hello.c
 * Description	 : GTK实验  hello world
 * *****************************************************************************/
#include <gtk/gtk.h>

//定义回调函数
void hello(GtkWidget *widget, gpointer *data)
{
	g_print("button clicked and data = %s\n", (char *)data);
}

//定义销毁函数
void destroy(GtkWidget *widget, gpointer *data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	//窗口和按钮指针
	GtkWidget *window;
	GtkWidget *button;

	//初始化窗口
	gtk_init(&argc, &argv);

	//创建新的窗口，并设置当窗口关闭时要调用的回调函数
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(destroy), NULL);

	//设置窗口属性
	gtk_container_border_width(GTK_CONTAINER(window), 400);

	//创建新的按钮，并上位置单击时要执行的回调函数
	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(hello), "I am from button");

	//将按钮加入到新创建的窗口中
	gtk_container_add(GTK_CONTAINER(window), button);

	//显示窗口和按钮
	gtk_widget_show(button);
	gtk_widget_show(window);
	
	//进入消息循环
	gtk_main();

	return 0;
}
