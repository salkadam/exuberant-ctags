/*
*   $Id: parrot.c 571 2011-04-15 14:17:48Z lateau $
*
*   Copyright (c) 2011, Daehyub Kim <lateau@gmail.com>
*
*   This source code is released for free distribution under the terms of the
*   GNU General Public License.
*
*   This module contains functions for generating tags for Parrot files.
*/

/*
*   INCLUDE FILES
*/
#include "general.h"  /* must always come first */
#include "parse.h"

/*
*   DATA DEFINITIONS
*/
typedef enum {
    K_NONE = -1,
    K_SUBROUTINE,
    K_RULE,
    K_TOKEN
} parrotKind;

static kindOption ParrotKinds [] = {
	{TRUE, 's', "subroutine", "subroutines"},
	{TRUE, 'r', "rule", "rules"},
	{TRUE, 't', "token", "tokens"}
};

#define ALNUM "a-zA-Z0-9_"

/*
 * Bellow regular expression is not clearly to read and not complete.
 */
static void installParrotRegex (const langType language)
{
    addTagRegex (language, "^\\.sub[ \t]*'([" ALNUM "]+)'([ \t]*:[" ALNUM "]+(\\((('[" ALNUM "]+')*[ \t,_]*)*\\))*)*",
            "\\1", "s,subroutine,subroutines", NULL);
    addTagRegex (language, "rule[ \t]*([" ALNUM "]+)[ \t]*(:\"*[" ALNUM "+-/%^<>=]+\"*)*", "\\1", "r,rule,rules", NULL);
    addTagRegex (language, "token[ \t]*([" ALNUM "]+)[ \t]*(:\"*[" ALNUM "+-/%^<>=]+\"*)*", "\\1", "t,token,tokens", NULL);
}

extern parserDefinition* ParrotParser (void)
{
	 static const char *const extensions [] = { "pir", "pg", "pasm", "nqp", NULL };
	 parserDefinition* def = parserNew ("Parrot");
     def->extensions = extensions;
     def->initialize = installParrotRegex;
     def->regex      = TRUE;
	 return def;
}

/* vi:set tabstop=4 shiftwidth=4: */
