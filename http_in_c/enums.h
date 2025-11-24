#ifndef ENUMS_H
#define ENUMS_H


#define AMOUNT_OF_ERROR_MESSAGES 5
#define MAXIMUM_LENGHT_OF_ERROR_MESSAGE 50

typedef enum
{
  ERROR_MEMORY_ALLOCATION = -1,
} ErrorCodes;

typedef enum
{
  SUCCESS = 0,
  FAILED = -1,
} ReturnStatus;


#endif