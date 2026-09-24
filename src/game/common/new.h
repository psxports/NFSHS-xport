/* game/common/new.h — reconstructed from game/common/new.cpp (4 fns) */
#ifndef _GAME_COMMON_NEW_H_
#define _GAME_COMMON_NEW_H_
#include "../../nfs4_types.h"

void *__builtin_new(unsigned int size);     /* :16 */
void *__builtin_vec_new(unsigned int size); /* :31 */
void __builtin_delete(void *deleteMe);      /* :46 */
void __builtin_vec_delete(void *deleteMe);  /* :51 */

#endif /* _GAME_COMMON_NEW_H_ */
