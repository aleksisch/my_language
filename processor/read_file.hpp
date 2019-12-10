//@file
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <time.h>

#include "onegin.h"

/*!
@brief This program have two ways to sort input text,\n starting with first char of line or last char of line
*/


void work_file(int *size, struct pointer_on_line** lineptr, char** text, const char* input, int* countline)
{
    assert(size);
    assert(lineptr);
    assert(input);
    assert(countline);

    *text = readFile (input, size); // without *

    *countline = get_line (*text, *size);

    *lineptr = (struct pointer_on_line*) calloc (*countline, sizeof(struct pointer_on_line));

    get_ptr(*text, *lineptr, *size);
}



/*!
Read input file to text
\param[in] str filename
\param[out] size size of file
\return text
*/
char *readFile (const char* str, int *size, const char* chmod)
{
    assert (size);
    assert (str);
    FILE *fp = NULL;

    if ((fp = fopen(str, chmod)) == NULL)
    {
        printf("Cannot find text\n");
        exit(0);
    }

    fseek (fp, 0L, SEEK_END);

    *size = (int) ftell(fp);

    char *text = (char *) calloc(*size + 1, sizeof(char));

    fseek (fp, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);

    text[*size] = '\0';

    fclose (fp);

    return text;
}
/*!
\param[in] str1 first cheking string
\param[in] str2 second cheking string
\return true or false
*/
int get_line (char* text, int size)
{
    assert (text);
    int countline = 0;
    for (int i = 0; i < size; i++)
    {
        if ((text[i]   == '\n' || text[i]   == '\0') &&
            (text[i+1] != '\n' && text[i+1] != '\0'))
        {
            countline++;
            text[i] = '\0';
        }
    }
    countline++;
    text[size-1] = '\0';
    return countline;
}
/*!
Get pointers to the beginning of line
\param[in] text input text
\param[out] lineptr array of pointers on string
\param[in] size length input text
*/
void get_ptr (char* text, struct pointer_on_line* lineptr, int size)
{
    assert (text);
    assert (lineptr);
    int l = 0, i = 1;
    lineptr[0].start = text;
    for (; i < size-1; i++)
    {
        if (text[i] == '\0' && text[i - 1] != '\0')
            lineptr[l++].end = text + i - 1;
        if (text[i] == '\0' && text[i + 1] != '\0')
            lineptr[l].start = text + i + 1;
    }
 //   lineptr[l].end = text + i;
}

