#ifndef __RPG_ITEM__
#define __RPG_ITEM__
#include "mapobj.h"
typedef struct Item_t
{
	char_t character;
	char name[16];
	
	int amount;
	
	//do we subtract one on use?
	bool removeOnUse;

	void (*useFunc)(struct mapobj_t* user, struct Item_t* item);
	void (*equipFunc)(struct mapobj_t* user);

}Item_t;

#endif