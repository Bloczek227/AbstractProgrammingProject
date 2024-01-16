#ifndef PA_PROJ_ITEM_H
#define PA_PROJ_ITEM_H

#include "stats.h"
#include "concepts.h"
#include "skill.h"

class Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChampion>
    using WaitTick = ZeroSkill<OffensiveChampion>;
};

#endif //PA_PROJ_ITEM_H
