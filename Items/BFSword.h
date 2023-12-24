#ifndef PA_PROJ_BFSWORD_H
#define PA_PROJ_BFSWORD_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class BFSword: public Item{
public:
    constexpr static double cost=1300;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double BFSword::StatValue<AD>(){return 40;}

#endif //PA_PROJ_BFSWORD_H
