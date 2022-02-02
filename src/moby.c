#include "moby.h"

//--------------------------------------------------------
#define SPAWN_MOBY_FUNC                         (0x004F7200)
#define BEGIN_MOBY_PTR                          ((Moby**)0x00222794)
#define END_MOBY_PTR                            ((Moby**)0x002227B0)
#define MOBY_UPDATE_FUNC                        (0x004FE720)
#define MOBY_DESTROY_FUNC                       (0x004F76A0)

/*
 * Returns pointer to the start of the moby list.
 */
Moby * mobyListGetStart(void)
{
    return *BEGIN_MOBY_PTR;
}

/*
 * Returns pointer to the end of the moby list.
 */
Moby * mobyListGetEnd(void)
{
    return *END_MOBY_PTR;
}


/*
 * Returns non-zero if the given moby is destroyed.
 */
int mobyIsDestroyed(Moby* moby)
{
    return moby && moby->State <= -2;
}

/*
 * 
 */
int mobyGetNumSpawnableMobys(void)
{
    return *(int*)0x00222790;
}

/*
 * Returns a pointer to the next living moby of the given oclass.
 * Returns NULL if none found.
 */
Moby* mobyFindNextByOClass(Moby* start, int oClass)
{
    Moby* mEnd = mobyListGetEnd();
    
	// find
	if (oClass > 0 && start) {
		while (start < mEnd && (start->OClass != oClass || mobyIsDestroyed(start)))
			++start;
	}

    // found
    if (start < mEnd)
        return start;
    
    // couldn't find
    return NULL;
}
