#include <gtk/gtk.h>

void hello(GtkWidget *widget, gpointer data)
{
	g_print("Hello World!\n");
}

gint delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occurred\n");

	return TRUE;
}

void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	//定义控件指针
	GtkWidget *window;
	GtkWidget *button;

	//初始化控件
	gtk_init(&argc, &argv);

	//创建一个新窗口
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	//将控件和消息处理函数建立联系
	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);

	//将控件和消息处理函数建立联系
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

	//设置窗口边框的高度
	gtk_container_set_border_width(GTK_CONTAINER(window), 100);

	//创建一个标签为“hello world”的按钮
	button = gtk_button_new_with_label("Hello World");

	//将按钮分别和hello和destroy回调函数建立联系
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL);
	g_signal_connect_swapped(G_OBJECT(button), "clicked", G_CALLBACK(gtk_widget_destroy), window);
	
	//将按钮加入到窗口中
	gtk_container_add (GTK_CONTAINER (window), button);

	//显示控件
	gtk_widget_show (window);
	gtk_widget_show (button);

	//事件循环
	gtk_main ();

	return 0;
}
