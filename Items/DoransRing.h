#ifndef PA_PROJ_DORANSRING_H
#define PA_PROJ_DORANSRING_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class DoransRing: public Item{
public:
    constexpr static double cost=400;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double DoransRing::StatValue<AP>(){return 18;}
template<> double DoransRing::StatValue<HP>(){return 90;}

#endif //PA_PROJ_DORANSRING_H
