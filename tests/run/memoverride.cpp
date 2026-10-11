#include <new>
#include <stdio.h>
#include <string.h>

static int s_nDestroyed = 0;

struct Counted
{

	~Counted() { ++s_nDestroyed; }
};

int main()
{
	// Explicit calls exercise both sized entry points even when a compiler
	// chooses unsized deletion for a delete expression.
	const size_t sizes[] = { 1, 17, 4096, 65536 };
	for ( size_t size : sizes )
	{
		void *scalar = ::operator new( size );
		memset( scalar, 0x5a, size );
		::operator delete( scalar, size );

		void *array = ::operator new[]( size );
		memset( array, 0xa5, size );
		::operator delete[]( array, size );
	}
	::operator delete( nullptr, size_t( 0 ) );
	::operator delete[]( nullptr, size_t( 0 ) );

	Counted *scalar = new Counted;
	delete scalar;
	Counted *array = new Counted[7];
	delete[] array;
	if ( s_nDestroyed != 8 )
	{
		printf( "Expected 8 destructors, got %d\n", s_nDestroyed );
		return 1;
	}

	printf( "Sized scalar/array deletion and object destruction passed\n" );
	return 0;
}
