/*
 * FreeModbus Libary: lwIP Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- lwIP ---------------------------------------------*/
#include "lwip/api.h"
#include "lwip/sys.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_POLL_CYCLETIME       100     /* Poll cycle time is 100ms */
#define SYS_MBOX_NUM          ( 16 )

/* ----------------------- Static variables ---------------------------------*/
static sys_mbox_t xMailBox = SYS_MBOX_NULL;
static eMBEventType eMailBoxEvent;


/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortEventInit( void )
{
	err_t error;
	
    eMailBoxEvent = EV_READY;
	if(xMailBox == SYS_MBOX_NULL)
	{
		xMailBox = xQueueCreate(SYS_MBOX_NUM, sizeof(eMailBoxEvent));
	}   
	
	return xMailBox != SYS_MBOX_NULL ? TRUE : FALSE;
}

void
vMBPortEventClose( void )
{
    if( xMailBox != SYS_MBOX_NULL )
    {
        vQueueDelete( xMailBox );
    }
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
    eMailBoxEvent = eEvent;

	xQueueSend(xMailBox, &eEvent, portMAX_DELAY);	
	
    return TRUE;
}

BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
    eMBEventType    mailBoxEvent;
    BOOL            xEventHappend = FALSE;
    u32_t           uiTimeSpent;


	if(pdTRUE == xQueueReceive(xMailBox, &mailBoxEvent, MB_POLL_CYCLETIME))
	{
        *eEvent = mailBoxEvent;
        eMailBoxEvent = EV_READY;
        xEventHappend = TRUE;	
	}

    return xEventHappend;
}

