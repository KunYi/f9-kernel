/* Copyright (c) 2013 The F9 Microkernel Project. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <platform/link.h>
#include <user_runtime.h>
#include <l4/ipc.h>
#include <l4/utcb.h>
#include <l4io.h>

#define STACK_SIZE 256


static L4_ThreadId_t threads __USER_DATA;

static L4_Word_t last_thread __USER_DATA;
static L4_Word_t free_mem __USER_DATA;

__USER_TEXT
void hello_thread(void)
{
	while (1)
	{
		printf("hello world!\r\n");
		L4_Sleep(L4_TimePeriod(10*1000));
	}
}

__USER_TEXT
static void start_thread(L4_ThreadId_t t, L4_Word_t ip,
		L4_Word_t sp, L4_Word_t stack_size)
{
	L4_Msg_t msg;

	L4_MsgClear(&msg);
	L4_MsgAppendWord(&msg, ip);
	L4_MsgAppendWord(&msg, sp);
	L4_MsgAppendWord(&msg, stack_size);
	L4_MsgLoad(&msg);

	L4_Send(t);
}

__USER_TEXT
static L4_ThreadId_t create_thread(user_struct *user, void (*func)(void))
{
	L4_ThreadId_t myself = L4_MyGlobalId();
	L4_ThreadId_t child;

	child.raw = myself.raw + (++last_thread << 14);

	L4_ThreadControl(child, myself, L4_nilthread, myself, (void *) free_mem);
	free_mem += UTCB_SIZE + STACK_SIZE;

	start_thread(child, (L4_Word_t)func, free_mem, STACK_SIZE);

	return child;
}

__USER_TEXT 
static void *main(void *user)
{
	printf("\n create my hello_thread \n");
	free_mem = ((user_struct*)user)->fpages[0].base;

	threads = create_thread(user, hello_thread);

	return NULL;
}

DECLARE_USER(
	128,
	hello,
	main,
	DECLARE_FPAGE(0x0, 2 * (UTCB_SIZE + STACK_SIZE))
);
