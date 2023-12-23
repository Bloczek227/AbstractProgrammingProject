#ifndef PA_PROJ_RECURVEBOW_H
#define PA_PROJ_RECURVEBOW_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class RecurveBowPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return ChampionSkill::onHit*15;}
};

class RecurveBow: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=RecurveBowPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double RecurveBow::StatValue<AttackSpeed>(){return 15;}

#endif //PA_PROJ_RECURVEBOW_H
