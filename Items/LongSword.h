#ifndef PA_PROJ_LONGSWORD_H
#define PA_PROJ_LONGSWORD_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class LongSword: public Item{
public:
    constexpr static double cost=350;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double LongSword::StatValue<AD>(){return 10;}

#endif //PA_PROJ_LONGSWORD_H
