#include "tier0/generichash.h"

#include <stdio.h>
#include <string.h>

static int g_nFailures = 0;

#define CHECK( expr ) \
	do \
	{ \
		if ( !( expr ) ) \
		{ \
			printf( "%s:%d: CHECK( %s ) failed\n", __FILE__, __LINE__, #expr ); \
			++g_nFailures; \
		} \
	} while ( 0 )

static void TestMurmurHash64()
{
	// Golden hashes for lengths 0 through 32, covering every block and tail size.
	const uint64 expected[] =
	{
		0xe6ef48f9d052b463ULL,
		0x89322d5cd1b4b8cdULL,
		0x442d6ee91c026503ULL,
		0x6a468753ec44f4b1ULL,
		0x56f2cfc098bdcdb5ULL,
		0xb92d7e50da65fa83ULL,
		0x527dfce3eaf0290cULL,
		0x409478f2f1477d3eULL,
		0xb3e9d0453bc8beceULL,
		0x6d09fe364f16d65cULL,
		0x6f3411da652814ccULL,
		0xfbb84a49e5bc4bffULL,
		0x6740cc147cdeea92ULL,
		0x9a98cd711a1ffbb4ULL,
		0x3b5f91093eb03819ULL,
		0x870efa80892fb36ULL,
		0x4cf4fc25d3161557ULL,
		0x52823ff29a75972aULL,
		0x29ccef64aee2f3ccULL,
		0xeed40448d200e4e5ULL,
		0x3a7bfbd1f46764b7ULL,
		0xc2ed5ad26fd8dca1ULL,
		0x7d062c440830ccd5ULL,
		0x1a07fad2b9fe1e4bULL,
		0xb462e4ec364f70a1ULL,
		0x743432cfe271725aULL,
		0x48507a68b9fc1210ULL,
		0xb8fcd3984a8f39d9ULL,
		0x88f828b12fe23822ULL,
		0xe2cb7960b1d4dffaULL,
		0x402c5297a9e8e24aULL,
		0x267eccdfba179182ULL,
		0x52daa964e93d7fe8ULL,
	};

	for ( int offset = 0; offset < 8; ++offset )
	{
		alignas(8) uint8 storage[40] = {};
		uint8 *data = storage + offset;
		for ( int i = 0; i < 32; ++i )
			data[i] = static_cast<uint8>( i * 73 + 19 );
		for ( int length = 0; length <= 32; ++length )
			CHECK( MurmurHash64( data, length, 0xEDABCDEF ) == expected[length] );
	}
}

static void TestFixedHashes()
{
	const uint32 expected[][4] =
	{
		{ 33628, 30312, 3610, 34404 },
		{ 8272, 62615, 63886, 7735 },
		{ 23264, 19847, 5203, 38784 },
		{ 37506, 12686, 34996, 51352 },
	};
	for ( int pattern = 0; pattern < 4; ++pattern )
	{
		for ( int offset = 0; offset < 8; ++offset )
		{
			alignas(8) uint8 storage[24] = {};
			uint8 *data = storage + offset;
			for ( int i = 0; i < 16; ++i )
				data[i] = static_cast<uint8>( pattern == 0 ? 0 : pattern == 1 ? 255 : pattern == 2 ? i : i * 73 + 19 );
			CHECK( Hash4( data ) == expected[pattern][0] );
			CHECK( Hash8( data ) == expected[pattern][1] );
			CHECK( Hash12( data ) == expected[pattern][2] );
			CHECK( Hash16( data ) == expected[pattern][3] );
		}
	}
}

int main()
{
	TestMurmurHash64();
	TestFixedHashes();
	if ( g_nFailures )
	{
		printf( "%d checks failed\n", g_nFailures );
		return 1;
	}
	printf( "All checks passed\n" );
	return 0;
}
