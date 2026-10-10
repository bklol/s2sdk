//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Ownership id for a shared object cache
//
//=============================================================================

#ifndef SOID_H
#define SOID_H

#ifdef _WIN32
#pragma once
#endif

#include "tier0/platform.h"

namespace GCSDK
{

// SOID_t::m_type of a player's own caches, the one a SteamID owns
const uint32 k_SOID_Type_SteamID = 1;

//----------------------------------------------------------------------------
// Purpose: Owner of a shared object cache, CMsgSOIDOwner on the wire
//----------------------------------------------------------------------------
struct SOID_t
{
	bool operator==( const SOID_t &rhs ) const { return m_type == rhs.m_type && m_id == rhs.m_id; }
	bool operator!=( const SOID_t &rhs ) const { return !( *this == rhs ); }
	// The order the GC client's cache map is sorted in
	bool operator<( const SOID_t &rhs ) const { return m_type != rhs.m_type ? m_type < rhs.m_type : m_id < rhs.m_id; }

	uint64 m_id;
	uint32 m_type;
};

} // namespace GCSDK

#endif // SOID_H
