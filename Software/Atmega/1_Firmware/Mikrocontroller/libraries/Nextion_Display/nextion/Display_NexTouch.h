
#ifndef __NEXTOUCH_H__
#define __NEXTOUCH_H__

#include "Display_NexConfig.h"
#include "Display_NexObject.h"
#include <string.h>
#include "../util/Display_Utilities.h"

#define NEX_EVENT_PUSH (0x01)
#define NEX_EVENT_POP (0x00)

void NexTouch_iterate(struct NexObject **list, uint8_t pid, uint8_t cid, int32_t event);

void NexTouch_attachPush(struct NexObject *touch, NexTouchEventCb push, void *ptr);

void NexTouch_detachPush(struct NexObject *touch);

void NexTouch_attachPop(struct NexObject *touch, NexTouchEventCb pop, void *ptr);

void NexTouch_detachPop(struct NexObject *touch);

void NexTouch_push(struct NexObject *touch);
void NexTouch_pop(struct NexObject *touch);

#endif