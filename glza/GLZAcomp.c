/***********************************************************************

Copyright 2014-2016 Kennon Conrad

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

***********************************************************************/

// GLZAcomp.c
//


#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GLZAformat.h"
#include "GLZAcompress.h"
#include "GLZAencode.h"


uint8_t GLZAcomp(size_t insize, uint8_t * inbuf, size_t * outsize_ptr, uint8_t *outbuf, FILE * fd)
{
  uint8_t status;
  uint8_t * temp2buf = 0;
  uint8_t * tempbuf = (uint8_t *)malloc(insize);
  if (tempbuf == 0) return(0);
  memcpy(tempbuf, inbuf, insize);
  status = GLZAformat(insize, (uint8_t *)tempbuf, outsize_ptr, &temp2buf);
  free(tempbuf);
  if (status == 0)
    return(0);
  insize = *outsize_ptr;
  status = GLZAcompress(insize, (uint8_t *)temp2buf, outsize_ptr, &tempbuf);
  free(temp2buf);
  if (status == 0)
    return(0);
  inbuf = tempbuf;
  insize = *outsize_ptr;
  status = GLZAencode(insize, inbuf, outsize_ptr, outbuf, (FILE *)fd);
  free(inbuf);
  if (status == 0)
    return(0);
  return(1);
}