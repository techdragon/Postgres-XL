/*-------------------------------------------------------------------------
 *
 * pgxc.h
 *		Postgres-XC flags and connection control information
 *
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Portions Copyright (c) 2012-2014, TransLattice, Inc.
 * Portions Copyright (c) 1996-2011  PostgreSQL Global Development Group
 * Portions Copyright (c) 2010-2012 Postgres-XC Development Group
 *
 * src/include/pgxc/pgxc.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef PGXC_H
#define PGXC_H

#include "storage/lwlock.h"
#include "postgres.h"

extern bool isPGXCCoordinator;
extern bool isPGXCDataNode;
extern bool isRestoreMode;
#ifdef XCP
extern char *parentPGXCNode;
extern int	parentPGXCNodeId;
extern char	parentPGXCNodeType;
#endif

typedef enum
{
	REMOTE_CONN_APP,
	REMOTE_CONN_COORD,
	REMOTE_CONN_DATANODE,
	REMOTE_CONN_GTM,
	REMOTE_CONN_GTM_PROXY
} RemoteConnTypes;

/* Determine remote connection type for a PGXC backend */
extern int		remoteConnType;

/* Local node name and numer */
extern char	*PGXCNodeName;
extern int	PGXCNodeId;
extern uint32	PGXCNodeIdentifier;

extern Datum xc_lockForBackupKey1;
extern Datum xc_lockForBackupKey2;

#define IS_PGXC_COORDINATOR isPGXCCoordinator
#define IS_PGXC_DATANODE isPGXCDataNode

#define IS_PGXC_LOCAL_COORDINATOR	\
	(IS_PGXC_COORDINATOR && !IsConnFromCoord())
#define IS_PGXC_REMOTE_COORDINATOR	\
	(IS_PGXC_COORDINATOR && IsConnFromCoord())

#ifdef XCP
#define PGXC_PARENT_NODE parentPGXCNode
#define PGXC_PARENT_NODE_ID	parentPGXCNodeId
#define PGXC_PARENT_NODE_TYPE	parentPGXCNodeType
#endif
#define REMOTE_CONN_TYPE remoteConnType

#define IsConnFromApp() (remoteConnType == REMOTE_CONN_APP)
#define IsConnFromCoord() (remoteConnType == REMOTE_CONN_COORD)
#define IsConnFromDatanode() (remoteConnType == REMOTE_CONN_DATANODE)
#define IsConnFromGtm() (remoteConnType == REMOTE_CONN_GTM)
#define IsConnFromGtmProxy() (remoteConnType == REMOTE_CONN_GTM_PROXY)

/* key pair to be used as object id while using advisory lock for backup */
#define XC_LOCK_FOR_BACKUP_KEY_1      0xFFFF
#define XC_LOCK_FOR_BACKUP_KEY_2      0xFFFF

#endif   /* PGXC */
