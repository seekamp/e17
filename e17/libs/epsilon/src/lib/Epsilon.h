#ifndef EPSILON_H
#define EPSILON_H
#include<stdlib.h>

#define EPSILON_FAIL 0
#define EPSILON_OK 1

typedef void Epsilon_Exif_Info;

struct _Epsilon
{
  char *hash;
  char *src;
  char *thumb;
};
typedef struct _Epsilon Epsilon;

struct _Epsilon_Info
{
  char *uri;
  unsigned long long int mtime;
  int w, h;
  char *mimetype;
  Epsilon_Exif_Info *eei;
};
typedef struct _Epsilon_Info Epsilon_Info;


void epsilon_init (void);

/* construct destruct */
void epsilon_free (Epsilon * e);
Epsilon *epsilon_new (const char *file);

/*
 * the source filename
 */
const char *epsilon_file_get (Epsilon * e);
/*
 * the thumbnail filename
 */
const char *epsilon_thumb_file_get (Epsilon * e);
/* 
 * returns EPSILON_FAIL if no thumbnail exists, EPSILON_OK if it does
 */
int epsilon_exists (Epsilon * e);
/* 
 * returns EPSILON_FAIL if no errors, EPSILON_OK if write goes ok
 */
int epsilon_generate (Epsilon * e);

/*
 * get the meta information associated with the epsilon
 */
Epsilon_Info *epsilon_info_get (Epsilon * e);

int epsilon_exif_info_props_as_int_get (Epsilon_Info * ei, long prop);
const char *epsilon_exif_info_props_as_str_get (Epsilon_Info * ei, long prop);
void epsilon_exif_info_props_print (Epsilon_Info * ei);
int epsilon_info_has_exif_get (Epsilon_Info * ei);

#endif
