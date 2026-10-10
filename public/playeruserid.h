#ifndef PLAYERUSERID_H
#define PLAYERUSERID_H

#if _WIN32
#pragma once
#endif

class CPlayerUserId
{
public:
	CPlayerUserId( int index )
	{
		_index = index;
	}

	int Get() const
	{
		return _index;
	}

	bool operator==( const CPlayerUserId &other ) const { return other._index == _index; }
	bool operator!=( const CPlayerUserId &other ) const { return other._index != _index; }

private:
	unsigned short _index;
};

static_assert( sizeof( CPlayerUserId ) == 0x2 );

#endif // PLAYERUSERID_H
