#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#define _XOPEN_SOURCE 600 //for powl() function


void on_num0_clicked(void);
void on_num1_clicked(void);
void on_num2_clicked(void);
void on_num3_clicked(void);
void on_num4_clicked(void);
void on_num5_clicked(void);
void on_num6_clicked(void);
void on_num7_clicked(void);
void on_num8_clicked(void);
void on_num9_clicked(void);
void on_add_clicked(void);
void on_subtract_clicked(void);
void on_multiply_clicked(void);
void on_divide_clicked(void);
void on_exp_clicked(void);
void on_decimal_clicked(void);
void on_clear_clicked(void);
void on_equals_clicked(void);
void on_delete_clicked(void);


GdkPixbuf *create_pixbuf(const gchar *filename);
void print_result(void);
GtkWidget *resultLine;
char *expression;
int expLen = 0;
int num1Len = 0;
int num2Len = 0;
int curNum = 1;
bool operatorEnabled;
bool num1DecimalSet;
bool num2DecimalSet;
bool equalsSet;


int main(int argc, char *argv[])
{
	expression = calloc(100, sizeof(char));
	operatorEnabled = false;
	num1DecimalSet = false;
	num2DecimalSet = false;
	equalsSet = false;
    GtkBuilder *builder; 
    GtkWidget *window;
    GdkPixbuf *icon;
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "/etc/simpleCalc/window_main.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    resultLine = GTK_WIDGET(gtk_builder_get_object(builder, "resultLine"));
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
    gtk_builder_connect_signals(builder, NULL);
    icon = create_pixbuf("/usr/share/pixmaps/calc.ico");
    gtk_window_set_icon(GTK_WINDOW(window), icon);
	g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}


GdkPixbuf *create_pixbuf(const gchar *filename)
{    
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if (!pixbuf) {
        fprintf(stderr, "%s\n", error -> message);
        g_error_free(error);
    }
    return pixbuf;
}


void on_window_main_destroy(void)
{
    gtk_main_quit();
}


gboolean on_window_main_key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer data) //function for keyboard interrupts
{
	if (event -> keyval == GDK_KEY_0 || event -> keyval == GDK_KEY_KP_0) { //0 or numpad 0 pressed
    	on_num0_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_1 || event -> keyval == GDK_KEY_KP_1) { //1 or numpad 1 pressed etc
    	on_num1_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_2 || event -> keyval == GDK_KEY_KP_2) {
    	on_num2_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_3 || event -> keyval == GDK_KEY_KP_3) {
    	on_num3_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_4 || event -> keyval == GDK_KEY_KP_4) {
    	on_num4_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_5 || event -> keyval == GDK_KEY_KP_5) {
    	on_num5_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_6 || event -> keyval == GDK_KEY_KP_6) {
    	on_num6_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_7 || event -> keyval == GDK_KEY_KP_7) {
    	on_num7_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_8 || event -> keyval == GDK_KEY_KP_8) {
    	on_num8_clicked();
        return TRUE;
    }
    else if (event -> keyval == GDK_KEY_9 || event -> keyval == GDK_KEY_KP_9) {
    	on_num9_clicked();
	    return TRUE;
    }
    else if (event -> keyval == GDK_KEY_plus || event -> keyval == GDK_KEY_KP_Add) {
    	on_add_clicked();
    	return TRUE;
    }
    else if (event -> keyval == GDK_KEY_minus || event -> keyval == GDK_KEY_KP_Subtract) {
    	on_subtract_clicked();
    	return TRUE;
	}
	else if (event -> keyval == GDK_KEY_asterisk || event -> keyval == GDK_KEY_KP_Multiply) {
		on_multiply_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_slash || event -> keyval == GDK_KEY_KP_Divide) {
		on_divide_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_asciicircum) { 
		on_exp_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_period || event -> keyval == GDK_KEY_KP_Decimal) {
		on_decimal_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_equal || event -> keyval == GDK_KEY_KP_Equal || event -> keyval == GDK_KEY_KP_Enter || event -> keyval == GDK_KEY_Return) {
		on_equals_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_Delete) {
		on_clear_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_BackSpace) {
		on_delete_clicked();
		return TRUE;
	}
	else if (event -> keyval == GDK_KEY_Escape)
		gtk_main_quit();
    return FALSE;
}


void on_num0_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		if (num1Len != 0) {
			expression[expLen] = '0';
			expLen++;
			num1Len++;
			print_result();
		}
	}
	else if (curNum == 2 && equalsSet != true) {
		if (num2Len != 0) {
			expression[expLen] = '0';
			expLen++;
			num2Len++;
			print_result();
		}
	}
}


void on_num1_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '1';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '1';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num2_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '2';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '2';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num3_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '3';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '3';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num4_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '4';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '4';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num5_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '5';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '5';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num6_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '6';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '6';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num7_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '7';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '7';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num8_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '8';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '8';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_num9_clicked(void)
{
	if (curNum == 2 && equalsSet == true) {
		gtk_label_set_text(GTK_LABEL(resultLine), "");
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		equalsSet = false;
		num1DecimalSet = false;
		curNum = 1;
	}
	if (curNum == 1) {
		expression[expLen] = '9';
		expLen++;
		num1Len++;
		print_result();
	}
	else if (curNum == 2 && equalsSet != true) {
		expression[expLen] = '9';
		expLen++;
		num2Len++;
		print_result();
	}
}


void on_add_clicked(void)
{
	equalsSet = false;
	if (expLen > 0) {
		if (operatorEnabled == false) {
			expression[expLen] = '+';
			expLen++;
			operatorEnabled = true;
			curNum = 2;
			print_result();
		}
	}
}


void on_subtract_clicked(void)
{
	equalsSet = false;
	if (expLen > 0) {
		if (operatorEnabled == false) {
			expression[expLen] = '-';
			expLen++;
			operatorEnabled = true;
			curNum = 2;
			print_result();
		}
	}
	else if (curNum == 1) {
		if (num1Len == 0) {
			expression[expLen] = '-'; //negative num set
			expLen++;
			num1Len++;
			print_result();
		}
	}
	else {
		if (num2Len == 0) {
			expression[expLen] = '-'; //negative num set
			expLen++;
			num2Len++;
			print_result();
		}
	}
}


void on_multiply_clicked(void)
{
	equalsSet = false;
	if (expLen > 0) {
		if (operatorEnabled == false) {
			expression[expLen] = 'X';
			expLen++;
			operatorEnabled = true;
			curNum = 2;
			print_result();
		}
	}
}


void on_divide_clicked(void)
{
	equalsSet = false;
	if (expLen > 0) {
		if (operatorEnabled == false) {
			expression[expLen] = '/';
			expLen++;
			operatorEnabled = true;
			curNum = 2;
			print_result();
		}
	}
}


void on_exp_clicked(void)
{
	equalsSet = false;
	if (expLen > 0) {
		if (operatorEnabled == false) {
			expression[expLen] = '^';
			expLen++;
			operatorEnabled = true;
			curNum = 2;
			print_result();
		}
	}
}


void on_decimal_clicked(void)
{
	if (curNum == 1) {
		expression[expLen] = '.';
		expLen++;
		num1Len++;
		num1DecimalSet = true;
		print_result();
	}
	else if (curNum == 2 && num2DecimalSet == false) {
		expression[expLen] = '.';
		expLen++;
		num2Len++;
		num2DecimalSet = true;
		print_result();
	}
}


void on_clear_clicked(void)
{
	expression = calloc(100, sizeof(char));
	expLen = 0;
	operatorEnabled = false;
	curNum = 1;
	num1Len = 0;
	num2Len = 0;
	num1DecimalSet = false;
	num2DecimalSet = false;
	gtk_label_set_text(GTK_LABEL(resultLine), "0");
}


void on_equals_clicked(void)
{
	if (operatorEnabled == false || num2Len == 0) //operator not entered and/or num2 not entered
		return;
	char *leftExp = malloc(50);
	assert(leftExp);
	char *rightExp = malloc(50);
	assert(rightExp);
	int decToInt = 0;
	int counter = 0;
	for (int i = 0; i < num1Len; i++)
		leftExp[i] = expression[i];
	leftExp[num1Len] = '\0';
	for (int i = num1Len + 1; i <= expLen; i++) {
		rightExp[counter] = expression[i];
		counter++;
	}
	rightExp[expLen - num1Len - 1] = '\0';
	int num1IsFloat = 0;
	char out[100] = {0};
	if (operatorEnabled == true && num2Len > 0 && num1DecimalSet == false && num2DecimalSet == false) { //only ints entered in line
		int lside = atoi(leftExp);
		int rside = atoi(rightExp);
		if (expression[num1Len] == '+') {
			long sum = lside + rside;
			sprintf(out, "%ld", sum);
		}
		else if (expression[num1Len] == '-') {
			long sum = lside - rside;
			sprintf(out, "%ld", sum);
		}
		else if (expression[num1Len] == 'X') {
			long sum = lside * rside;
			sprintf(out, "%ld", sum);
		}
		else if (expression[num1Len] == '^') {
			long sum = powl(lside, rside);
			sprintf(out, "%ld", sum);
		}
		else {
			double sum = (float)lside / (float)rside;
			sprintf(out, "%lf", sum);
			for (int i = 8; i >= 0; i--) { //truncate trailing zeros
				if (out[i - 1] == '.' && out[i] == '0') { 
					decToInt = 1; //float has a form of (int).0, ie 30.0 or 1.0 - convert to int
					break;
				}
				else if (out[i - 1] == '.') //float with form (int).(int), ie 1.5 (don't truncate to int)
					break;
				else {
					if (out[i] == '0')
						out[i] = '\0';
				}
			}
			if (decToInt == 1) {
				char *charSum = malloc(20);
				assert(charSum);
				for (int i = 0; i < 10; i++) {
					if (out[i] == '.')
						break;
					else 
						charSum[i] = out[i];
				}
				int intSum = atoi(charSum);
				memset(&out[0], 0, sizeof(out));
				sprintf(out, "%d", intSum);
				free(charSum);
			}
			else
				num1IsFloat = 1;
		}
		gtk_label_set_text(GTK_LABEL(resultLine), out);
	}
	else if (operatorEnabled == true && num2Len > 0 && (num1DecimalSet == true || num2DecimalSet == true)) { //mix of ints/floats or both floats
		double lside = atof(leftExp);
		double rside = atof(rightExp);
		if (expression[num1Len] == '+') {
			double sum = lside + rside;
			sprintf(out, "%lf", sum);
		}
		else if (expression[num1Len] == '-') {
			double sum = lside - rside;
			sprintf(out, "%lf", sum);
		}
		else if (expression[num1Len] == 'X') {
			double sum = lside * rside;
			sprintf(out, "%lf", sum);
		}
		else if (expression[num1Len] == '^') {
			double sum = pow(lside, rside);
			sprintf(out, "%lf", sum);
		}
		else {
			double sum = lside / rside;
			sprintf(out, "%lf", sum);
		}
		for (int i = 8; i >= 0; i--) { //truncate trailing zeros
			if (out[i - 1] == '.' && out[i] == '0') {
				decToInt = 1;
				break;
			}
			else if (out[i - 1] == '.')
				break;
			else {
				if (out[i] == '0')
					out[i] = '\0';
			}
		}
		if (decToInt == 1) {
			char *charSum = malloc(20);
			assert(charSum);
			for (int i = 0; i < 10; i++) {
				if (out[i] == '.')
					break;
				else 
					charSum[i] = out[i];
			}
			int intSum = atoi(charSum);
			memset(&out[0], 0, sizeof(out));
			sprintf(out, "%d", intSum);
			free(charSum);
		}
		else
			num1IsFloat = 1;
		gtk_label_set_text(GTK_LABEL(resultLine), out);
	}
	expression = calloc(100, sizeof(char));
	for (int i = 0; i < strlen(out); i++) {
		expression[i] = out[i];
	}
	expLen = strlen(out);
	operatorEnabled = false;
	curNum = 1;
	num1Len = strlen(out);
	num2Len = 0;
	if (num1IsFloat == 0)
		num1DecimalSet = false;
	else
		num1DecimalSet = true;
	num2DecimalSet = false;
	equalsSet = true;
	free(leftExp);
	free(rightExp);
}


void on_delete_clicked(void)
{
	if (curNum == 1 && expLen == 0) //nohing entered, do nothing
		return;
	if (curNum == 1 && equalsSet == true) { //answer from previous calculation entered
		equalsSet = false;
		num1DecimalSet = false;
		num2DecimalSet = false;
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		gtk_label_set_text(GTK_LABEL(resultLine), "0");
		return;
	}
	if (curNum == 1 && expLen == 1) { //only 1 number entered
		expression = calloc(100, sizeof(char));
		expLen = 0;
		num1Len = 0;
		gtk_label_set_text(GTK_LABEL(resultLine), "0");
		return;
	}
	if (curNum == 1 && expression[expLen - 1] == '.') { //decimal entered on num1 last entry
		char tmp[100] = {0};
		expLen--;
		num1Len--;
		for (int i = 0; i < expLen; i++)
			tmp[i] = expression[i];
		expression = calloc(100, sizeof(char));
		for (int i = 0; i < expLen; i++)
			expression[i] = tmp[i];
		num1DecimalSet = false;
		print_result();
		return;
	}
	if (expression[expLen - 1] == '+' || expression[expLen - 1] == '-' || expression[expLen - 1] == 'X' || expression[expLen - 1] == '/' || expression[expLen - 1] == '^') { //operator
		char tmp[100] = {0};
		expLen--;
		for (int i = 0; i < expLen; i++)
			tmp[i] = expression[i];
		expression = calloc(100, sizeof(char));
		for (int i = 0; i < expLen; i++)
			expression[i] = tmp[i];
		operatorEnabled = false;
		print_result();
		return;
	}
	if (curNum == 2 && expression[expLen - 1] == '.') {
		char tmp[100] = {0};
		expLen--;
		num2Len--;
		for (int i = 0; i < expLen; i++)
			tmp[i] = expression[i];
		expression = calloc(100, sizeof(char));
		for (int i = 0; i < expLen; i++)
			expression[i] = tmp[i];
		num2DecimalSet = false;
		print_result();
		return;
	}
	else { //handle all other operations with nums
		if (curNum == 1) {
			char tmp[100] = {0};
			expLen--;
			num1Len--;
			for (int i = 0; i < expLen; i++)
				tmp[i] = expression[i];
			expression = calloc(100, sizeof(char));
			for (int i = 0; i < expLen; i++)
				expression[i] = tmp[i];
			print_result();
		}
		else {
			char tmp[100] = {0};
			expLen--;
			num2Len--;
			for (int i = 0; i < expLen; i++)
				tmp[i] = expression[i];
			expression = calloc(100, sizeof(char));
			for (int i = 0; i < expLen; i++)
				expression[i] = tmp[i];
			print_result();
		}
	}
} 


void print_result(void)
{
	gtk_label_set_text(GTK_LABEL(resultLine), expression);
}
