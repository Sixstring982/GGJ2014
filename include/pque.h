#ifndef PQUE_H
#define PQUE_H

#include "itype.h"
#include "command.h"

#define PQUE_MAX_SIZE 1024

typedef struct s_pque
{
  u32 capacity;
  u32 size;
  Command* queue[PQUE_MAX_SIZE];
}PQue;

extern void PQue_Init(PQue* queue);

extern void PQue_Insert(PQue* queue, Command* command);

#endif /*PQUE_H*/
