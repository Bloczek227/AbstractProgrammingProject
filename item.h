#ifndef PA_PROJ_ITEM_H
#define PA_PROJ_ITEM_H

#include "stats.h"
#include "concepts.h"

class Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
};


#endif //PA_PROJ_ITEM_H
