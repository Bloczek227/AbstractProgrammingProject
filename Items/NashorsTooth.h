#ifndef PA_PROJ_NASHORSTOOTH_H
#define PA_PROJ_NASHORSTOOTH_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class NashorsToothPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return ChampionSkill::onHit*(15+0.2*OffensiveChamp::TotalAP());}
};

class NashorsTooth: public Item{
public:
    constexpr static double cost=3000;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=NashorsToothPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double NashorsTooth::StatValue<AP>(){return 90;}
template<> double NashorsTooth::StatValue<AttackSpeed>(){return 50;}

#endif //PA_PROJ_NASHORSTOOTH_H
