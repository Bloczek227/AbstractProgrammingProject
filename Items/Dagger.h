#ifndef PA_PROJ_DAGGER_H
#define PA_PROJ_DAGGER_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

class Dagger: public Item{
public:
    constexpr static double cost=300;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double Dagger::StatValue<AttackSpeed>(){return 12;}

#endif //PA_PROJ_DAGGER_H
