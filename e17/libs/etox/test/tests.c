#include "Etox_test.h"

Evas_List *basic_tests()
{
	Evas_List *l = NULL;

	l = evas_list_append(l, test_basic_init);
	l = evas_list_append(l, test_basic_get);
	l = evas_list_append(l, test_basic_set);
	l = evas_list_append(l, test_basic_append);
	l = evas_list_append(l, test_basic_prepend);

	return l;
}

void test_basic_init()
{
	char msg[] =
	    "This series of tests will exercise the most basic\n"
	    "functions of etox, reading and displaying text with\n"
	    "basic formatting.\n"
	    "\n"
	    "In addition, prepending, appending and inserting text\n"
	    "in an existing etox will be tested.\n"
	    "\n" "Click Next to begin the tests.";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");

	return;
}

void test_basic_get()
{
	char msg[] =
	    "The sample text shown below was retrieved from\n"
	    "the text in this message etox.\n"
	    "\n" "The function used was etox_get_text.";

	char *string;

	/* Change message */
	etox_set_text(e_msg, msg);

	/* Set test text and show test etox */
	string = etox_get_text(e_msg);
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

void test_basic_set()
{
	char msg[] =
	    "The text in an etox can be changed on the fly.\n"
	    "The sample paragraph shown below replaced the\n"
	    "text shown in the previous test.\n"
	    "\n" "The function used was etox_set_text.";

	char string[] =
	    "\n"
	    "A file that big?\n"
	    "It might be very useful.\n" "But now it is gone.\n" "\n";

	/* Change message */
	etox_set_text(e_msg, msg);

	/* Change test etox */
	etox_set_text(e_test, string);

	return;
}

void test_basic_append()
{
	char msg[] =
	    "Text can be appended to the text already existent\n"
	    "in the etox.\n"
	    "\n"
	    "The second paragraph shown below was appended\n"
	    "at the end of the etox through etox_append_text.\n";

	char string[] =
	    "The Tao that is seen\n"
	    "Is not the true Tao\n" "Until you bring fresh toner.\n" "\n";

	/* Change message */
	etox_set_text(e_msg, msg);

	/* Change test etox */
	etox_append_text(e_test, string);

	return;
}

void test_basic_prepend()
{
	char msg[] =
	    "Text can be appended to the text already existent\n"
	    "in the etox.\n"
	    "\n"
	    "The second paragraph shown below was appended\n"
	    "at the end of the etox through etox_append_text.\n";

	char string[] =
	    "The Tao that is seen\n"
	    "Is not the true Tao\n" "Until you bring fresh toner.\n" "\n";

	/* Change message */
	etox_set_text(e_msg, msg);

	/* Change test etox */
	etox_prepend_text(e_test, string);

	return;
}

Evas_List *style_tests()
{
	Evas_List *l = NULL;

	l = evas_list_append(l, test_style_init);
	l = evas_list_append(l, test_style_bold);
	l = evas_list_append(l, test_style_outline);
	l = evas_list_append(l, test_style_raised);
	l = evas_list_append(l, test_style_shadow);

	return l;
}

void test_style_init()
{
	char msg[] =
	    "The text can be applied to the etox with a\n"
	    "stylized effect.\n"
	    "\n"
	    "Click the Next button to cycle through the available\n"
	    "text styles.\n"
	    "\n" "A style-less sample paragraph is shown below.\n";

	char string[] =
	    "Chaos reigns within.\n"
	    "Stop, reflect, and reboot.\n" "Order shall return.\n";


	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");
	etox_context_set_style(e_test, "plain");
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

void test_style_bold()
{
	char msg[] = "\"Bold\" style.\n";

	char string[] =
	    "Chaos reigns within.\n"
	    "Stop, reflect, and reboot.\n" "Order shall return.\n";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");
	etox_context_set_style(e_test, "bold");
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

void test_style_outline()
{
	char msg[] = "\"Outline\" style.\n";

	char string[] =
	    "Chaos reigns within.\n"
	    "Stop, reflect, and reboot.\n" "Order shall return.\n";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");
	etox_context_set_style(e_test, "outline");
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

void test_style_raised()
{
	char msg[] = "\"Raised\" style.\n";

	char string[] =
	    "Chaos reigns within.\n"
	    "Stop, reflect, and reboot.\n" "Order shall return.\n";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");
	etox_context_set_style(e_test, "raised");
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

void test_style_shadow()
{
	char msg[] = "\"Shadow\" style.\n";

	char string[] =
	    "Chaos reigns within.\n"
	    "Stop, reflect, and reboot.\n" "Order shall return.\n";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");
	etox_context_set_style(e_test, "shadow");
	etox_set_text(e_test, string);
	etox_show(e_test);

	return;
}

Evas_List *callback_tests()
{
	Evas_List *l = NULL;

	l = evas_list_append(l, test_callback_init);
	/* l = evas_list_append(l, test_callback_add); */

	return l;
}

void test_callback_init()
{
	char msg[] = "Not implemented yet.";

	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");

	return;
}

void test_callback_add()
{
	char msg[] = "Not implemented yet.";
	etox_set_text(e_msg, msg);

	etox_set_text(e_test, "");

	return;
}
