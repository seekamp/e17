#include "auth.h"

pam_handle_t *pamh;

static int elogin_pam_conv (int num_msg, const struct pam_message **msg,
      struct pam_response **resp, void *appdata_ptr)
{
   int replies = 0;
   struct pam_response *reply = NULL;

   reply = malloc(sizeof(struct pam_response));

   if (!reply)
      return PAM_CONV_ERR;

   for (replies = 0; replies < num_msg; replies++)
   {
      switch (msg[replies]->msg_style)
      {
	 case PAM_PROMPT_ECHO_ON:
	    reply[replies].resp_retcode = PAM_SUCCESS;
	    reply[replies].resp = (char *) strdup(appdata_ptr);
	    break;
	 case PAM_PROMPT_ECHO_OFF:
	    reply[replies].resp_retcode = PAM_SUCCESS;
	    reply[replies].resp = (char *) strdup(appdata_ptr);
	    break;
	 case PAM_ERROR_MSG:
	 case PAM_TEXT_INFO:
	    elogin_greeter_msg((char *)msg[replies]->msg);
	    reply[replies].resp_retcode = PAM_SUCCESS;
	    reply[replies].resp = NULL;
	    break;
	 default:
	    free(reply);
	    return (PAM_CONV_ERR);
      }
   }

   *resp = reply;
   return (PAM_SUCCESS);
}

static struct pam_conv pamc = { &elogin_pam_conv, NULL };

int elogin_auth_user(char *user, char *passwd)
{
   int pamerr;

   pamc.appdata_ptr = (char *) strdup(passwd);

   if ((pamerr = pam_start("elogin", user, &pamc, &pamh)) != PAM_SUCCESS)
   {
      printf("Cannot find /etc/pam.d/elogin !! Did you do a 'make install' ??\n");
      goto pamerr;
   }
   if ((pamerr = pam_set_item(pamh, PAM_TTY, e_display_get())) != PAM_SUCCESS)
   {
      printf("Couldn't set PAM_TTY=%s\n", e_display_get());
      goto pamerr;
   }
   if ((pamerr = pam_authenticate(pamh, 0)) != PAM_SUCCESS)
   {
      printf("Couldn't authenticate %s\n", user);
      goto pamerr;
   }

   pamerr = pam_acct_mgmt(pamh, 0);
   if (pamerr == PAM_NEW_AUTHTOK_REQD)
   {
      pamerr = pam_chauthtok(pamh, PAM_CHANGE_EXPIRED_AUTHTOK);
   }

   if (pamerr != PAM_SUCCESS)
   {
      printf("Couldn't set acct. mgmt for %s\n", user);
      goto pamerr;
   }

   if (pamerr == PAM_SUCCESS)
      printf("WHOO! it worked!!!\n");

   return SUCCESS;

pamerr:
   printf("Authentication failed.\n");
   pam_end(pamh, pamerr);
   pamh = NULL;

   return FAIL;
}

void elogin_auth_cleanup(void)
{
   if (pamh)
   {
      pam_close_session(pamh, 0);
      pam_end(pamh, PAM_SUCCESS);
      pamh = NULL;
   }
}
int elogin_start_client(Userinfo *info)
{
   uid_t uid = 1000;
   int status;

   e_sync();
   XCloseDisplay(e_display_get());
   status = setuid(uid);
   if (status == -1)
      printf("Error attempting to set uid to %d\n", uid);
     {
	char env[4096];
	
	sprintf(env, "DISPLAY=%s", ":0.0");
	putenv(env);
     }
   execl("/bin/sh", "/bin/sh", "-c", "/usr/bin/X11/xterm", NULL);

   return SUCCESS;
}


